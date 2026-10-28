class isrInfo:
    def __init__(self, kind="", prio=0, t=0, event="", constraint=0):
        self.kind = kind
        self.prio = prio
        self.t = t
        self.event = event
        self.constraint = constraint

    def __str__(self):
        print(self.kind)
    def getPrio(self):
        return self.prio
    def getKind(self):
        return self.kind
    def getT(self):
        return self.t
    def getEvent(self):
        return self.event
    def getConstraint(self):
        return self.constraint
