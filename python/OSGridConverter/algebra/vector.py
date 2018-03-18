'''
Created on 17 Mar 2018

@author: julianporter
'''
from OSGridConverter.base import OSGridError
from math import sqrt
from .core import allNumbers


class Vector(object):
    
    @classmethod
    def zero(cls,n=3):
        return Vector([0]*n)

    def __init__(self,arg):
        if isinstance(arg,Vector):
            self.array=arg.array[:]
        else:
            try:
                if not allNumbers(arg): raise Exception()
                self.array=arg[:]
            except:
                raise OSGridError('Constructor requires either Vector or [numeric]')
            
        self.nRows=len(self.array)
        self.nColumns=1
            
    def __len__(self):
        return self.nRows
    
    def __iter__(self):
        return iter(self.array)
    
    def __getitem__(self,key):
        if key<0 or key>=len(self):
            raise OSGridError("Index out of range for vector")
        return self.array[key]
    
    def __setitem__(self,key,value):
        if key<0 or key>=len(self):
            raise OSGridError("Index out of range for vector")
        self.array[key]=value
        
    def __add__(self,other):
        return Vector([x+y for (x,y) in zip(self,other)])
    
    def __sub__(self,other):
        return Vector([x-y for (x,y) in zip(self,other)])
    
    def __neg__(self):
        return Vector([- x for x in self.array])
    
    def __mul__(self,other):
        return Vector([x*other for x in self.array])
    
    def __rmul__(self,other):
        return Vector([x*other for x in self.array])
            
    def __or__(self,other):
        return sum([x*y for (x,y) in zip(self,other)])
    
    def __eq__(self,other):
        return all([x==y for (x,y) in zip(self,other)])
    
    def __abs__(self):
        return sum([x*x for x in self])
    
    def __str__(self):
        return str(self.array) 
    
   
    
class Vector3(Vector): 
    
    @property
    def x(self) : return self.array[0] 
    
    @property
    def y(self) : return self.array[1] 
    
    @property
    def z(self) : return self.array[2]  
    
    @property 
    def normSquared(self):
        return self.x*self.x+self.y*self.y*self.z*self.z
    
    @property
    def p(self):
        return sqrt(self.x*self.x + self.y*self.y)
    
    @classmethod
    def axis(cls,axis):
        try:
            axis=axis.upper()
            pos = ['X','Y','Z'].index(axis)
            args=[0,0,0]
            args[pos]=1
            return Vector3(args)
        except ValueError:
            raise OSGridError('Axis must be X, Y or Z')  