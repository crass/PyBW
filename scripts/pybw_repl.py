import code
import subprocess
import sys
import threading
from SimpleXMLRPCServer import SimpleXMLRPCServer
import xmlrpclib
import socket
import time

PS1 = 'pybw> '
PS2 = 'pybw| '

class ThreadSharedData():
    pass

def xmlrpc_server_thread(shared_data):
    try:
        def get_buffer():
            with shared_data.commands_buffer_lock:
                buffer = list( shared_data.commands_buffer )
                del shared_data.commands_buffer[:]
            return buffer

        def write_to_console(text):
            sys.stdout.write ('%s' % text)
            shared_data.waiting_for_output = 0
            return 0
            
        
        server = SimpleXMLRPCServer(("localhost", 8000), logRequests=False)
        shared_data.shutdown = server.shutdown
        server.register_introspection_functions()
        server.register_function(get_buffer)
        server.register_function(write_to_console)
        server.serve_forever()
    except Exception, e:
        print "Thread Error", e

def main():
    try:
        commands_buffer = []

        shared_data = ThreadSharedData()    # the thread will populate it later
        shared_data.commands_buffer = commands_buffer
        shared_data.commands_buffer_lock = threading.Lock()
        shared_data.waiting_for_output = 0

        t = threading.Thread( target=xmlrpc_server_thread, args=(shared_data,) )
        t.start()
        try:
            i = code.InteractiveConsole()
            code_list = []
            while True:
                while shared_data.waiting_for_output:   # remove this for asynchronous REPL
                    time.sleep(0.01)

                try:
                    input = i.raw_input(PS2 if len(code_list) else PS1 )
                except EOFError:
                    if not code_list:
                        raise
                    code_list = []
                    continue

                code_list +=[ input ]
                
                code_str = '\n'.join(code_list)
                try:
                    res = i.compile(code_str)
                except SyntaxError:
                    res = None

                if res is not None: # this code is complete and without syntax error
                    if code_str:
                        with shared_data.commands_buffer_lock:
                            commands_buffer += [code_str]
                            shared_data.waiting_for_output = 1
                    code_list = []

        finally:
            shared_data.shutdown()
            t.join()

    except EOFError:
        pass                
    except Exception, e:
        print "Error", e
        raw_input()
    

class FakeFile(object):
    def __init__(self):
        self.buffer = []

    def write(self, t):
        self.buffer.append( t )

    def writelines(self, l):
        self.buffer += l

class FakeSys(object):
    pass


class ConsoleClient(object):
    def _new_process(self):
        self.cmd = sys.prefix + '\\python.exe' + ' -c "from pybw_repl import main; main()"'
        self.process = subprocess.Popen(self.cmd, close_fds=True )

        self.proxy = xmlrpclib.ServerProxy('http://localhost:8000')

    def __init__(self):
        self._new_process()

    def start_repl(self, env_dict):
        self.exec_env = code.InteractiveConsole(env_dict)

    def kill_server(self):
        try:
            self.process.kill()
        except AttributeError:
            pass

    def __del__(self):
        self.kill_server()
    
    def on_frame(self):
        if self.proxy is not None:
            try:
                commands_buffer = self.proxy.get_buffer()

                for command in commands_buffer:
                    old_stdout = sys.stdout
                    old_stderr = sys.stderr
                    sys.stdout = FakeFile()
                    sys.stderr = FakeFile()
                    try:
                        self.exec_env.runsource(command)
                        result = ''.join( sys.stdout.buffer ) + ''.join( sys.stderr.buffer )
                    except Exception, e:
                        result = "Exception: %s" % e
                    finally:
                        sys.stdout = old_stdout
                        sys.stderr = old_stderr

                    self.proxy.write_to_console( result )

            except socket.error:
                self.proxy = None
