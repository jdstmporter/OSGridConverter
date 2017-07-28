'''
Created on 28 Jul 2017

@author: julianporter
'''

import random
import numpy as np
from OSGridConverter.cartesian import Vector, Matrix
from OSGridConverter import LatLong, OSGridReference
from math import log10

def equalVectors(np,v):
    if len(np)!=len(v): return False
    return all([np[i]==v[i] for i in range(len(v))])

def equalMatrices(np,v):
    if len(np)!=len(v): return False
    return all([equalVectors(np[i],v[i]) for i in range(len(v))])

def vectorError(np,v):
    return sum([abs(np[i]-v[i]) for i in range(len(v))])

def vectorDiff(np,v):
    e=vectorError(np,v)
    if e==0 : return 1000.0
    return -log10(e)

def matrixDiff(np,v):
    e=sum([vectorError(np[i],v[i]) for i in range(len(v))])
    if e==0 : return 1000.0
    return -log10(e)

def gridDiff(g1,g2):
    e=max([abs(x-y) for (x,y) in zip(g1.eastNorth(),g2.eastNorth())])
    if e==0 : return 1000.0
    return 6-log10(e)

def latlongDiff(l1,l2):
    e=(l1.latitude-l2.latitude,l1.longitude-l2.longitude)
    e=max([abs(x) for x in e])
    if e==0 : return 1000.0
    return 3-log10(e)

class Generator(object):
    
    def __init__(self,lo=-100.0,hi=100.0,n=3):
        self.lo=lo
        self.hi=hi
        self.n=n
        
    def randomScalar(self):
        return random.uniform(self.lo,self.hi)
        
    def randomList(self):
        return [random.uniform(self.lo,self.hi) for _ in range(self.n)]
    
    def randomListOfLists(self):
        return [self.randomList() for _ in range(self.n)]
    
    def randomNPVector(self):
        return np.array(self.randomList())
    
    def randomNPMatrix(self):
        return np.array(self.randomListOfLists())
    
    def randomVector(self):
        return Vector(self.randomList(),n=self.n)
    
    def randomMatrix(self):
        return Matrix(self.randomListOfLists(),n=self.n)
    
    def randomVectorPair(self):
        a=self.randomList()
        return (np.array(a), Vector(a,n=self.n))
    
    def randomMatrixPair(self):
        a=self.randomListOfLists()
        return (np.array(a), Matrix(a,n=self.n))
    
    def randomLatLong(self,tag='WGS84'):
        latitude  = random.uniform(50.0,59.0)
        longitude = random.uniform(-5.0,2.0)
        return LatLong(latitude,longitude,tag=tag)
    
    def randomGrid(self,tag='WGS84'):
        ll=self.randomLatLong(tag=tag)
        return OSGridReference(ll)
    

