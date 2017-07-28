'''
Created on 27 Jul 2017

@author: julianporter
'''

from math import sqrt
from ..base import OSGridError, areNumbers

def dot(a1,a2):
    zipped=zip(a1,a2)
    mixed=map(lambda p : p[0]*p[1],zipped)
    return sum(mixed)



class Vector(object):
    
    def __init__(self,*args):
        if len(args)>=3 and areNumbers(args[:3]):
            self.x, self.y, self.z = args
            self.array=args[:3]
        else:
            raise OSGridError('Constructor of Vector takes three numeric arguments')

    @property
    def p(self):
        return sqrt(self.x*self.x + self.y*self.y)
    
    @property
    def R(self):
        return self.p*self.p+self.z*self.z
    
    @classmethod
    def combine(cls,one,other,mixer = lambda x: x):
        zipped=zip(one,other)
        mixed=map(mixer,zipped)
        return [m for m in mixed]
    
    def combiner(self,other,mixer = lambda x: x):
        return Vector(*Vector.combine(self.array,other.array,mixer))
    
    def __add__(self,other):
        return self.combiner(other,lambda p : p[0]+p[1])
    
    def __sub__(self,other):
        return self.combiner(other,lambda p : p[0]-p[1])
    
    def __mul__(self,other):
        return sum(self.combiner(other,lambda p : p[0]*p[1]))
    
    def __str__(self):
        return str(self.array)
            
class Matrix(object):
    
    def __init__(self,*rows):
        self.rows=rows
        self.columns=[]
        for i in range(3):
            c=[r[i] for r in rows]
            self.columns.append(c) 

    def __matmul__(self,other):
        if isinstance(other,Vector):
            a=other.array
            out=[dot(a,row) for row in self.rows]
            return Vector(*out)
        elif type(other)==Matrix:
            c=other.columns
            out=[[ dot(row,col) for col in c] for row in self.rows]
            return Matrix(*out)
        
    def __str__(self):
        return str(self.rows)
                
                
            
    
    