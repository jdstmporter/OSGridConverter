'''
Created on 19 Jul 2017

@author: julianporter
'''

from .base import OSGridError, areNumbers
from .mapping import Data, transformation
from .cartesian import Cartesian


class LatLong (object):
    def __init__(self,*args,tag='WGS84'):
        
        if len(args)==0: 
            raise OSGridError('Initialisation of LatLong requires at least one argument')
        self.tag=tag
        self.datum=Data[tag]
        if isinstance(args[0],Cartesian):
            self.latitude, self.longitude = args[0].LatLong(self.datum.ellipsoid)
        elif len(args)>=2 and areNumbers(args[:2]):
            self.latitude, self.longitude = args
        else:
            OSGridError('Arguments to LatLong constructor must be Cartesian or lat,long')
            
    def transform(self,newTag):
        if self.tag==newTag:
            return self
        else:
            oldC = Cartesian(self)      
            newC = transformation(self.tag,newTag,oldC)
            return LatLong(newC,tag=newTag)
    
    def __str__(self):
        return '{:>+.5f}:{:>+.5f}'.format(self.latitude,self.longitude)
    
    