'''
Created on 17 Mar 2018

@author: julianporter
'''

from OSGridConverter.base import OSGridError, log, areNumbers
from OSGridConverter.mapping import OSDefaultGrid, GridReference
from .latlong import LatitudeLongitude
from math import radians, floor, degrees

 
class GridCoordinates(object):
    
    def __init__(self,arg):
        if isinstance(arg,LatitudeLongitude):
            if arg.tag!='OSGB36' : 
                log.debug("Transforming {} to OSGB36",arg)
                arg=arg.transform('OSGB36')
                log.debug("Transformed value is {}",arg)
            phi=radians(arg.latitude)
            l  =radians(arg.longitude)
        
            log.debug("phi = {}, l = {}",phi,l)
            v=OSDefaultGrid(phi,l)
            parsed = v.latLongToGrid()
        elif isinstance(arg,list) and areNumbers(arg):
            parsed=arg[:2]
        elif isinstance(arg,str):
            parsed=GridReference.stringToEN(arg)
        else:
            raise OSGridError('Arguments to OSGridRef constructor must be string, LatLong or E,N') 
        
        log.debug('out is {}',parsed)
        self.E, self.N = [floor(x) for x in parsed] # [round(x,0) for x in parsed]
        log.debug("E = {}, N = {}",self.E,self.N)
           
         
    def toLatLong(self,tag='WGS84',viaString=False) :
        if viaString:
            g=GridCoordinates(GridReference.stringToEN(str(self)))
            return g.toLatLong(tag=tag,viaString=False)
        
        phi=OSDefaultGrid.phi0
        M=0
        
        log.debug('Starting loop with phi = {}',phi)
        dN=self.N-OSDefaultGrid.N0
        while True:
            phi += (dN-M)/(OSDefaultGrid.AF0())
            M=OSDefaultGrid.meridian(phi)
            if dN-M < 1.0e-5: break
        
        log.debug('Ending loop with phi = {}',phi)
        
        v=OSDefaultGrid(phi,self.E)
        phi,l = v.gridToLatLong()
        
        point =  LatitudeLongitude(degrees(phi), degrees(l), tag='OSGB36');
        if (tag != 'OSGB36') : 
            point = point.transform(tag)
        return point
    
    def eastNorth(self):
        return (self.E, self.N)
    
    def __str__(self):
        return GridReference.coordinatesToString(self)
    
