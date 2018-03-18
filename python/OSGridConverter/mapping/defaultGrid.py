'''
Created on 26 Jul 2017

@author: julianporter
'''
from math import sin,cos,tan, pow, sqrt, radians
from .ellipsoids import Airy1830

class Parts(object):
    def __init__(self,v=0):
        self._v=v
 
        self._powers=[1,self._v]
        
    def __call__(self,n):
        while len(self._powers)<=n:
            self._powers.append(self._v*self._powers[-1])
        return self._powers[n]
    
 

             
   
    

class OSDefaultGrid (object):
    
    F0   = 0.9996012717
    phi0 = radians(49)
    l0   = radians(-2)
    N0   = -100000
    E0   =  400000
    ellipsoid = Airy1830
    
    signs=[1,-1,1,-1]

    @classmethod
    def AF0(cls):
        return cls.ellipsoid.a*cls.F0
    
    def __init__(self,phi,E):
        self.phi=phi
        self.l=E
        
        c=Parts(cos(phi))
        s=Parts(sin(phi))
        t=Parts(tan(phi))
        sc=1.0/self.parts.c(1)
        
        def cs(m,n): return c(m)*s(n)
        
        aF0=self.ellipsoid.a*self.F0
        e1=self.ellipsoid.eccentricity(1)
        nn  = self.ellipsoid.nu*self.ellipsoid.nu
        v   = 1.0-e1*s(2)
        nu = Parts(aF0/sqrt(v))
        
        def ncs(c=1,s=0): return nu(1)*cs(c,s)
        
        rho = aF0*(1-e1)*pow(v,-1.5)
        eta1= nu(1)/rho
        eta2= eta1 - 1.0
        

        self.latlong2gridN=[
            self.meridian(self.phi) + self.N0,
            ncs(1,1)/2.0,
            ncs(3,1)*(5-t(2)+9*nn)/24.0,
            ncs(5,1)*(61-58*t(2)+t(4))/720.0,
        ]
        self.latlong2gridE=[
            ncs(1,0),
            ncs(3,0)*(eta1-t(2))/6.0,
            ncs(5,0)*(5 - 18*t(2) + t(4) + 14*eta2 - 58*t(2)*eta2)/120.0,
            0
        ]
        
        self.grid2latlongP=[
            self.phi,
            t(1)/(2*rho*nu(1)),
            t(1)/(24*rho*nu(3))*(5+3*t(2)+eta2-9*t(2)*eta2),
            t(1)/(720*rho*nu(5))*(61+90*t(2)+45*t(4))
        ]
        
        self.grid2latlongL=[
            sc/nu(1),
            sc/(6*nu(3)*(eta1+2*t(2))),
            sc/(120*nu(5)*(5+28*t(2)+24*t(4))),
            sc/(5040*nu(7)*(61+662*t(2)+1320*t(4)+720*t(6)))
        ]
        
  
    '''
    +0 VIB        +1 X
    -2 VII        -3 XI
    +4 VIII       +5 XII
    -6 IX         -7 XIIA
                  
    +0 I          +1 IV
    +2 II         +3 V
    +4 III        +5 VI
    +6 IIIA       +7 VIA
    
    '''
  
    def gridToLatLong(self):
        dE = self.E-OSDefaultGrid.E0
        phi=sum([self.grid2latlongP[i]*pow(dE,2*i)*self.signs[i] for i in range(0,4)])
        l=sum([self.grid2latlongL[i]*pow(dE,2*i+1)*self.signs[i] for i in range(0,4)])+OSDefaultGrid.l0
        return (phi,l)
        
    
    def latLongToGrid(self):
        dl = self.E-OSDefaultGrid.l0
        N=sum([self.latlong2gridN[i]*pow(dl,2*i) for i in range(0,4)])
        E=sum([self.latlong2gridE[i]*pow(dl,2*i+1) for i in range(0,4)])+OSDefaultGrid.E0
        return (E,N)
    
    @classmethod
    def meridian(cls,phi):
        return cls.ellipsoid(phi,cls.phi0)*cls.ellipsoid.b*cls.F0
    
