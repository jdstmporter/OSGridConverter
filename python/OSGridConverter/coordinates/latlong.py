'''
Created on 17 Mar 2018

@author: julianporter
'''
from OSGridConverter.mapping import Datum
from .cartesian import Cartesian
import re
from OSGridConverter.base import areNumbers, OSGridError

class LatitudeLongitude(object):
    
    def __init__(self,arg,tag='WGS84'):
        try:
            self.tag=tag
            self.datum=Datum.get(tag)
            if isinstance(arg,Cartesian):
                self.latitude, self.longitude=arg.toLatLong(self.datum.ellipsoid)
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
            elif isinstance(arg,list) and areNumbers(arg):
                self.latitude, self.longitude=*arg
            else:
                raise Exception()
        except OSGridError as e:
            raise e
        except:
            raise  OSGridError('Arguments to LatLong constructor must be Cartesian or lat,long')
        
    def transform(self,newTag):
        if self.tag==newTag:
            return self
        else:
            oldC = Cartesian(self)      
            newC = oldC.transform(self.tag,newTag)
            return LatitudeLongitude(newC,tag=newTag)
            
    
    @property
    def errorRatio(self):
        return self.datum.errorRatio(self.latitude,self.longitude)
    
    @property
    def logErrorRatio(self):
        return self.datum.logErrorRatio(self.latitude,self.longitude)
    
    def __str__(self):
        return '{:>+.5f}:{:>+.5f}'.format(self.latitude,self.longitude)    