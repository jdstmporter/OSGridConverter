'''
Created on 17 Mar 2018

@author: julianporter
'''
from OSGridConverter.base import OSGridError
from math import sin,cos,radians
from .matrix import Matrix
from .vector import Vector

def singleAxis(axis,angle):
        try:
            axis=axis.upper()
            pos = ['X','Y','Z'].index(axis)
            i1=(pos+1)%3
            i2=(pos+2)%3
            sgn=2*(pos%2)-1
            c=cos(angle)
            s=sin(angle)*sgn
            rows=[[1,0,0],[0,1,0],[0,0,1]]
            rows[i1][i1]=c
            rows[i1][i2]=s
            rows[i2][i2]=c
            rows[i2][i1]=-s
            return Matrix(rows)
        except ValueError:
            raise OSGridError('Axis must be X, Y or Z')
        
def RotationMatrix(rx,ry,rz):
    return singleAxis('Z',rz) @ singleAxis('Y',ry) @ singleAxis('X',rx)

def InverseRotationMatrix(rx,ry,rz):
    return singleAxis('X',-rx) @ singleAxis('Y',-ry) @ singleAxis('Z',-rz)
     
     
class Helmert(object):
    
    def __init__(self,*args):
        
        if len(args)>=3:
            t, r, s = args
            self.origin=Vector(t)
            self.angles=[radians(x/3600.0) for x in r].reverse()
            self.scale=1.0+(s*1.0e-6)
            
            self.matrix=self.scale*RotationMatrix(*self.angles)
        else:
            self.origin=Vector.zero(3)
            self.angles=[0,0,0]
            self.scale=1.0
            self.matrix=Matrix.identity(3)
     
    def __call__(self,vector):
        return self.origin+(self.matrix@vector)       
            
    @property
    def inverse(self):
        inv=Helmert()
        inv.scale=1.0/self.scale
        inv.matrix=inv.scale*InverseRotationMatrix(*self.angles)
        inv.origin=-(inv.matrix@self.origin)
        return inv
