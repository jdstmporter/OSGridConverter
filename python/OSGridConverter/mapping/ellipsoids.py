'''
Created on 19 Jul 2017

@author: julianporter
'''

from OSGridConverter.algebra import dot
from math import sin,cos
from .meta import LoggerMetaclass


class Ellipsoid (object,metaclass=LoggerMetaclass) :
    
    def __init__(self,a,b,f,name=''):
        self.name=name
        self.a=a
        self.b=b
        self.flattening=f
        
        ff=(1-f)*(1-f)
        self._eccentricity=[1-ff,(1/ff)-1]
        
        self.nu=(a-b)/(a+b)
        nn=self.nu*self.nu
        nnn=self.nu*nn
        t=nn+nnn
        
        self.M=[1.0 + self.nu + 5.0*t/4.0,3.0*(self.nu+nn)+ 21.0*nnn/8.0,15.0*t/8.0,35.0*nnn/24.0]
        
    def eccentricity(self,n=1):
        return self._eccentricity[n-1]
    
    @property
    def ea(self):
        return self.eccentricity(1)*self.a
    
    @property
    def eb(self):
        return self.eccentricity(2)*self.b
    
    def __call__(self,phi,phi0):
        pM=phi-phi0
        pP=phi+phi0
        # ll => g   -                 +                      -                 
        angles=[pM,-sin(pM) * cos(pP),sin(2*pM) * cos(2*pP),-sin(3*pM) * cos(3*pP)]
        return dot(self.M,angles)
    
    @classmethod
    def get(cls,name):
        return cls._registry[name]
    
    @classmethod
    def enum(cls):
        return list(cls._registry.keys())
    
    
WGS84 = Ellipsoid(6378137,6356752.31425,1/298.257223563,name="WGS84")
GRS80 = Ellipsoid(6378137,6356752.31414,1/298.257222101,name="GRS80")
Airy1830 = Ellipsoid(6377563.396,6356256.909,1/299.3249646,name="Airy1830")
AiryModified = Ellipsoid(6377340.189,6356034.448,1/299.3249646,name="AiryModified")
Intl1924 = Ellipsoid(6378388,6356911.946,1.0/297.0,name="Intl1924")
Bessel1841 = Ellipsoid(6377397.155,6356078.963,1/299.152815351,name="Bessel1841")
Clarke1880 = Ellipsoid(6378249.2,6356515,1/293.465,name="Clarke1880")


     


    


