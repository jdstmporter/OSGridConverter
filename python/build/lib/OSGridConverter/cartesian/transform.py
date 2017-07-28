'''
Created on 27 Jul 2017

@author: julianporter
'''

from math import radians
from .algebra import Vector, Matrix
from ..base import OSGridError, areNumbers

def negate(a):
    return [-x for x in a]

class HelmertMatrix(Matrix):
    
    @classmethod
    def rowsFor(cls,r,s):
        return [[ s  , -r[2],  r[1]],
                [ r[2], s   , -r[0]],
                [-r[1], r[0],  s]]
    
    def __init__(self,*args):
        if len(args)==0: raise OSGridError('HelmertMatrix requires at least one argument')
        elif isinstance(args[0],Matrix):
            super(HelmertMatrix,self).__init__(args[0].rows,n=3)
        elif len(args)==2 and isinstance(args[0],Vector) and areNumbers([args[1]]):
            self.r=args[0]
            self.s=1.0+args[1]
            super(HelmertMatrix,self).__init__(self.rowsFor(self.r,self.s),n=3)
        else:
            raise OSGridError('HelmertMatrix requires matrix or vector + scalar')
    
    def determinant(self):
        return self.s*((self.r|self.r)+self.s*self.s)
    
    def inverse(self):
        m=(self.s*Matrix(self.rowsFor(-self.r,self.s),n=3))+Matrix.outerProduct(self.r, n=3)
        return m*(1.0/self.determinant())      
         

class Transform (object) :
    


    @classmethod
    def _normalise(cls,seconds):
        return radians(seconds/3600.0)
    
    def __init__(self,*args):
        if len(args)>=3:
            t, r, s = args
            self.t=Vector(t)
            
            r=Vector([radians(x/3600.0) for x in r])
            s=s/1.0e6
            self.mx=HelmertMatrix(r,s)
        elif len(args)==0:
            self.mx=Matrix.identity(3)
            self.t=Vector.zero(3)
        
    def __call__(self,vector):
        return self.t + (self.mx @ vector)
        
    @property
    def inverse(self):
        inv=Transform()
        inv.mx=self.mx.inverse()
        inv.t =-(inv.mx@self.t)
        return inv
    
    def __str__(self):
        return 'mx = {}, t = {}'.format(self.mx,self.vecT)

    
    
        
