'''
Created on 17 Mar 2018

@author: julianporter
'''

from OSGridConverter.algebra import Vector3
from OSGridConverter.mapping import Datum
from math import radians,degrees,sin,cos,sqrt,atan2,isnan


class Cartesian (Vector3):
    def __init__(self,arg):
        try:
            phi=radians(arg.latitude)
            l  =radians(arg.longitude)

            s=sin(phi)
            c=cos(phi)
        
            e=arg.ellipsoid.eccentricity(1)
            nu=arg.ellipsoid.a/sqrt(1.0-e*s*s)
                
            super(Cartesian,self).__init__([nu*c*cos(l),nu*c*sin(l),nu*(1-e)*s])  
        except:
            super(Cartesian,self).__init__(arg) 
     
    def transform(self,oldTag,newTag):
        if newTag==oldTag: return self
        t1=Datum.get(oldTag).transform.inverse
        t2=Datum.get(newTag).transform
        return Cartesian(t2(t1(self)))  
    
    def toLatLong(self,ellipsoid):
        try:
            t=(1+ellipsoid.eb/self.normSquared)
            s=t/sqrt(1+t*t)
            c=s/t
            if isnan(c): raise Exception()
            phi=atan2(self.z+ellipsoid.eb*s*s*s,sqrt(self.x*self.x + self.y*self.y)-ellipsoid.ea*c*c*c)
        except: 
            phi=0
        l=atan2(self.y,self.x)
        return(degrees(phi),degrees(l)) 
    
    def __str__(self):
        return '({},{},{})'.format(self.x,self.y,self.z)
          
         
def transformation(oldTag,newTag,vector):
    if newTag==oldTag: return vector
    t1=Datum.get(oldTag).transform.inverse
    t2=Datum.get(newTag).transform
    return Cartesian(t2(t1(vector)))   