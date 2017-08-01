'''
Created on 19 Jul 2017

@author: julianporter
'''

from .base import OSGridError, areNumbers
from .mapping import Data, transformation
from .cartesian import Cartesian
import re




class LatLong (object):
    def __init__(self,*args,tag='WGS84'):
        
        if len(args)==0: 
            raise OSGridError('Initialisation of LatLong requires at least one argument')
        self.tag=tag
        self.datum=Data[tag]
        arg=args[0]
        if isinstance(arg,Cartesian):
            self.latitude, self.longitude = arg.LatLong(self.datum.ellipsoid)
        elif isinstance(arg,str):
            match1=re.match(r'^\s*([+-]?(?:\d*\.)?\d+)([NnSs])\s*,\s*([+-]?(?:\d*\.)?\d+)([EeWw])\s*$',arg)
            match2=re.match(r'^\s*([+-]?(?:\d*\.)?\d+)\s*,\s*([+-]?(?:\d*\.)?\d+)\s*$',arg)
            if match1:
                lat, ns, long, ew=match1.groups()
                lat=float(lat)
                long=float(long)
                if ns.upper() == 'S': lat=-lat
                if ew.upper() == 'W': long=-long
                self.latitude, self.longitude = lat, long 
            elif match2:     
                self.latitude, self.longitude =[float(x) for x in match2.groups()]
            else:
                raise OSGridError('Cannot parse argument {}'.format(arg))   
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
        
    @property
    def errorRatio(self):
        return self.datum.errorRatio(self.latitude,self.longitude)
    
    @property
    def logErrorRatio(self):
        return self.datum.logErrorRatio(self.latitude,self.longitude)
    
    def __str__(self):
        return '{:>+.5f}:{:>+.5f}'.format(self.latitude,self.longitude)
    
    
        
 
    