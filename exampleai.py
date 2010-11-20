from pybw_swig import * # import all constants and classes

class ExampleAI(object):
    def onConnect(self):
        self.game = getGame() 

    def onMatchStart(self):
        if self.game.isReplay:
            return
        self.minerals = list(self.game.minerals)
        self.player = self.game.self
        self.race = self.player.race

        self.main_centers = [u for u in self.player.units if u.type == self.race.center]
        if self.main_centers:
            self.main_center = self.main_centers[0]

            self.mineral_queue = []
            for mineral in self.minerals:
                distance_to_center = mineral.position.getDistance( self.main_center.position )
                self.mineral_queue.append(( distance_to_center, mineral ))
            self.mineral_queue.sort()

        else:
            self.main_center = None

    def onMatchFrame(self):
        if self.game.isReplay:
            return
        if self.main_center:
            self.main_center.train( self.race.worker )

            inactive_workers = [u for u in self.game.self.units if u.type.isWorker and u.order == PlayerGuard]

            for worker in inactive_workers:
                mineral = self.mineral_queue.pop(0)
                worker.rightClick( mineral[1] )
                self.mineral_queue.append( mineral ) 

