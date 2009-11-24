import sys

class FileFlusher:
    def __init__(self, *args):
        self.f = file(*args)
    def write(self, *args):
        self.f.write(*args)
        self.f.flush()
    def writelines(self, *args):
        self.f.write(*args)
        self.f.flush()

sys.stdout = FileFlusher("c:\\pybw_out.txt",'w')
sys.stderr = FileFlusher("c:\\pybw_err.txt",'w')


print "Importing built-in module (provided by DLL, needed for debugging only)"
import _pybw_swig


print "Importing swig module (python file)"
import pybw_swig


print "Creating a broodwar instance (of Game)"

old_Game = pybw_swig.Game
class Game(old_Game):
    def __init__(self):
        self.this = pybw_swig.getBroodwar()

broodwar = Game()

print "Redirecting output to broodwar console"

class PrintToBroodwar(object):
    def __init__(self, broodwar, prefix, next_stream = None):
        self.broodwar = broodwar
        self.prefix = prefix
        self.next_stream = next_stream
    def write(self, s):
        s = str(s)
        if s.strip():
            self.broodwar.sendText(self.prefix + s )
        if self.next_stream:
            self.next_stream.write(s)
    def writelines(self, l):
        self.write( ('\n'+self.prefix).join(lines))
        if self.next_stream:
            self.next_stream.writelines(l)

    softspace = 0

sys.stdout = PrintToBroodwar(broodwar, '> ', sys.stdout)
sys.stderr = PrintToBroodwar(broodwar, '! ', sys.stderr)


print "Creating event handler"

try:
    import basicai
    event_handler = basicai.EventHandler(broodwar)
except Exception, e:
    print "error", e

def reload():
    global event_handler
    try:
        import basicai
        reload(basicai)
        event_handler = basicai.EventHandler(broodwar)
    except Exception, e:
        print "error", e


print "PyBW module Initialization complete"


