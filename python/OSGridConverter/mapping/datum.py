'''
Created on 17 Mar 2018

@author: julianporter
'''
from math import radians,sin, log10
from OSGridConverter.algebra import Helmert,Vector
from .meta import LoggerMetaclass
from .ellipsoids import Ellipsoid


        
        

class Datum (object,metaclass=LoggerMetaclass):
    def __init__(self,name="",ellipsoid=None,origin=Vector.zero(3),angles=Vector.zero(3),scale=0):
        self.name=name
        self.ellipsoid=ellipsoid
        self.transform=Helmert(origin,angles,scale)
        
        
    def errorRatio(self,latitude,longitude):
        phi=radians(latitude)
        l  =radians(longitude)
        
        s2p=pow(sin(phi),2)
        s2l=pow(sin(l),2)
        
        dl=1-self.ellipsoid.eccentricity(1)*(1-s2p*s2l)
        dp=(1-s2l)*(1-self.ellipsoid.eccentricity(1)*s2p)
        
        return (dp,dl)
    
    def logErrorRatio(self,latitude,longitude):
        dp,dl=self.errorRatio(latitude, longitude)
        r=abs(dl-dp)
        if r<=0: return 1000
        else: return -log10(r)
        
    @classmethod
    def get(cls,name):
        return cls._registry[name]
    
    @classmethod
    def enum(cls):
        return list(cls._registry.keys())
        
       

e=Ellipsoid.get
WGS84      =  Datum(name='WGS84',e('WGS84'),[0.0,0.0,0.0],[0.0,0.0,0.0],0.0),
NTF        =  Datum(name='NTF',e('Clarke1880'),[168,60,-320],[0.0,0.0,0.0],0.0),
NAD83      =  Datum(name='NAD83',e('GRS80'),[1.004,-1.910,-0.515],[0.0267,0.00034,0.011],-0.0015),
OSGB36     =  Datum(name='OSGB36',e('Airy1830'),[-446.448,125.157,-542.060],[-0.1502,-0.2470,-0.8421],20.4894),
ED50       =  Datum(name='ED50',e('Intl1924'),[89.5,93.8,123.1],[0.0,0.0,0.156],-1.2),
Irl1975    =  Datum(name='Irl1975',e('AiryModified'),[-482.530,130.596,-564.557],[-1.042,-0.214,-0.631],-8.150),
TokyoJapan =  Datum(name='TokyoJapan',e('Bessel1841'),[148,-507,-685],[0,0,0],0)
       



