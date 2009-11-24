import code
import subprocess
import sys
import threading
from SimpleXMLRPCServer import SimpleXMLRPCServer
import xmlrpclib
import socket

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
            sys.stdout.write ('\n%s' % text)
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

        t = threading.Thread( target=xmlrpc_server_thread, args=(shared_data,) )
        t.start()
        try:
            i = code.InteractiveConsole()
            code_list = []
            while True:
                code_list +=[ i.raw_input(PS2 if len(code_list) else PS1 ) ]
                
                code_str = '\n'.join(code_list)
                try:
                    res = i.compile(code_str)
                except SyntaxError:
                    res = None

                if res is not None: # this code is complete and without syntax error
                    if code_str:
                        with shared_data.commands_buffer_lock:
                            commands_buffer += [code_str]
                    code_list = []

        finally:
            shared_data.shutdown()
            t.join()
                
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

    def __init__(self, env_dict):
        self._new_process()

        self.exec_env = code.InteractiveConsole(env_dict)
    
    def on_frame(self):
        if self.proxy is not None:
            try:
                commands_buffer = self.proxy.get_buffer()

                for command in commands_buffer:
                    old_stdout = sys.stdout
                    sys.stdout = FakeFile()
                    try:
                        self.exec_env.runsource(command)
                        result = ''.join( sys.stdout.buffer )
                    except Exception, e:
                        result = "Exception: %s" % e
                    finally:
                        sys.stdout = old_stdout

                    self.proxy.write_to_console( result )

            except socket.error:
                self.proxy = None
