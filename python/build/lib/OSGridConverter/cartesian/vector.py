'''
Created on 27 Jul 2017

@author: julianporter
'''

from math import sqrt, isnan, cos, sin, atan2, degrees, radians
from ..base import OSGridError,log
from .algebra import Vector,Vector3

class Cartesian (Vector3):
    def __init__(self,*args):
        if len(args)==0: raise OSGridError('Initialisation of Cartesian requires at least one argument')
        if isinstance(args[0],Vector):
            super(Cartesian,self).__init__(args[0].array)
        else:
            try:
                latlong=args[0]
                phi = radians(latlong.latitude)
                l   = radians(latlong.longitude)
                
                a=latlong.datum.ellipsoid.a
                f=latlong.datum.ellipsoid.f
                
                s=sin(phi)
                c=cos(phi)
        
                eSq=2*f-f*f
                nu=a/sqrt(1.0-eSq*s*s)
                
                super(Cartesian,self).__init__([nu*c*cos(l),nu*c*sin(l),nu*(1-eSq)*s])
            except:
                super(Cartesian,self).__init__(args)
        
    def LatLong(self,ellipsoid):
        
        a = ellipsoid.a
        b = ellipsoid.b
        f = ellipsoid.f

        e1  = 2*f - f*f
        e2  = e1/(1-e1)
    

        t = (1+e2*b/self.R)*b*self.z/(a*self.p) 
        s = t/sqrt(1+t*t)
        c = s/t
        
        if isnan(c): phi=0
        else: phi=atan2(self.z + e2*b*s*s*s, self.p - e1*a*c*c*c) 
        l = atan2(self.y, self.x)

        return (degrees(phi),degrees(l))
    
    def transform(self,transform):
        transformed=transform(self)
        log.debug('Transform of {} is {}',self,transformed)
        return Cartesian(*transformed.array)
    
    
    

    def __str__(self):
        return '({},{},{})'.format(self.x,self.y,self.z)
     
       
        