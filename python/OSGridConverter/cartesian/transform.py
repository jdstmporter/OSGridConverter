'''
Created on 27 Jul 2017

@author: julianporter
'''

from math import radians
from .algebra import Vector, Matrix

def negate(a):
    return [-x for x in a]

class Transform (object) :

    @classmethod
    def _normalise(cls,seconds):
        return radians(seconds/3600.0)
    
    def __init__(self,*args,**kwargs):
        if 'mx' in kwargs and 'vecT' in kwargs:
            self.mx=kwargs['mx']
            self.vecT=kwargs['vecT']
        else:
            self.t, self.r, self.s = args
            self.vecT = Vector(*self.t)
        
            tr=list(map(Transform._normalise,self.r))
            ts=1+self.s/1.0e6
            self.mx=Matrix([ts,-tr[2],tr[1]],[tr[2],-ts,tr[0]],[tr[2],-tr[0],ts])
        
    def __call__(self,vector):
        
        mm=self.mx @ vector
        return self.vecT + mm
        
    @property
    def inverse(self):
        return Transform(negate(self.t),negate(self.r),-self.s)
    
    def __str__(self):
        return 'mx = {}, t = {}'.format(self.mx,self.vecT)


    def __matmul__(self,other):
        mx=self.mx @ other.mx
        vecT=other(self.vecT)
        return Transform(mx=mx,vecT=vecT)
    
    
        
