'''
Created on 19 Jul 2017

@author: julianporter
'''

from ..cartesian import Cartesian, Transform, dot
from math import sin,cos, pow, radians, log10


class Ellipsoid (object) :
    def __init__(self,a,b,f):
        self.a=a
        self.b=b
        self.f=f
        
        self.e1=2*f-f*f
        self.e2=self.e1/(1.0-self.e1) 
        self.E2=1.0-(b*b)/(a*a)
        n =(a-b)/(a+b)
        nn=pow(n,2.0)
        nnn=pow(n,3.0)
        a=nn+nnn
        
        self.M=[1.0 + n + 5.0*a/4.0,
                3.0*(n+nn)+ 21.0*nnn/8.0,
                15.0*a/8.0,
                35.0*nnn/24.0]
        self.n=n
    
    def meridional(self,phi,phi0):
        pM=phi-phi0
        pP=phi+phi0
        # ll => g   -                 +                      -                 
        angles=[pM,
                -sin(pM) * cos(pP),
                sin(2*pM) * cos(2*pP),
                -sin(3*pM) * cos(3*pP)]
        return dot(self.M,angles)
    
    
    
WGS84 = Ellipsoid(6378137,6356752.31425,1/298.257223563)
GRS80 = Ellipsoid(6378137,6356752.31414,1/298.257222101)
Airy1830 = Ellipsoid(6377563.396,6356256.909,1/299.3249646)
AiryModified = Ellipsoid(6377340.189,6356034.448,1/299.3249646)
Intl1924 = Ellipsoid(6378388,6356911.946,1.0/297.0)
Bessel1841 = Ellipsoid(6377397.155,6356078.963,1/299.152815351)
Clarke1880 = Ellipsoid(6378249.2,6356515,1/293.465)

'''
Need to define matrix class
so I can do this properly,
given that numpy is clearly
screwing up
'''



     

class Datum (object):
    def __init__(self,ellipsoid,transform):
        self.ellipsoid=ellipsoid
        self.transform=transform
        
        
    def errorRatio(self,latitude,longitude):
        phi=radians(latitude)
        l  =radians(longitude)
        
        s2p=pow(sin(phi),2)
        s2l=pow(sin(l),2)
        
        dl=1-self.ellipsoid.e1*(1-s2p*s2l)
        dp=(1-s2l)*(1-self.ellipsoid.e1*s2p)
        
        return (dp,dl)
    
    def logErrorRatio(self,latitude,longitude):
        dp,dl=self.errorRatio(latitude, longitude)
        r=abs(dl-dp)
        if r<=0: return 1000
        else: return -log10(r)
        
        
    
        
    
            
Data = dict(
    WGS84      =  Datum(WGS84,Transform([0.0,0.0,0.0],[0.0,0.0,0.0],0.0)),
    NTF        =  Datum(Clarke1880,Transform([168,60,-320],[0.0,0.0,0.0],0.0)),
    NAD83      =  Datum(GRS80,Transform([1.004,-1.910,-0.515],[0.0267,0.00034,0.011],-0.0015)),
    OSGB36     =  Datum(Airy1830,Transform([-446.448,125.157,-542.060],[-0.1502,-0.2470,-0.8421],20.4894)),
    ED50       =  Datum(Intl1924,Transform([89.5,93.8,123.1],[0.0,0.0,0.156],-1.2)),
    Irl1975    =  Datum(AiryModified,Transform([-482.530,130.596,-564.557],[-1.042,-0.214,-0.631],-8.150)),
    TokyoJapan =  Datum(Bessel1841,Transform([148,-507,-685],[0,0,0],0))
)        


Tags = list(Data.keys())

def transformation(oldTag,newTag,vector):
    if newTag==oldTag: return vector
    t1=Data[oldTag].transform.inverse
    t2=Data[newTag].transform
    return Cartesian(t2(t1(vector)))
    


