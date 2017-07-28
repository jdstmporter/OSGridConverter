'''
Created on 26 Jul 2017

@author: julianporter
'''
from math import sin,cos,tan, pow, sqrt, radians
from .ellipsoids import Airy1830

class OSDefaultGrid (object):
    F0   = 0.9996012717
    phi0 = radians(49)
    l0   = radians(-2)
    N0   = -100000
    E0   =  400000
    ellipsoid = Airy1830
    
    def __init__(self,phi,E):
        self.phi=phi
        self.E=E
        
        _c=cos(phi)
        _s=sin(phi)
        _t=tan(phi)
        e2=self.ellipsoid.e1
        v   = 1.0-e2*pow(_s,2)
        _nu = self.aF0()/sqrt(v)
        rho = self.aF0()*(1-e2)*pow(v,-1.5)
        eta1= _nu/rho
        eta2= eta1 - 1.0
        
        def ncs(cpower=1,spower=0):
            if spower==0:
                return _nu*pow(_c,cpower)
            else: 
                return _nu*pow(_c,cpower)*pow(_s,spower)
            
        def t(power):
            return pow(_t,power)
        
        def nu(power):
            return pow(_nu,power)
    
        def rhoNu(power):
            return rho*pow(_nu,power)

        self.transforms=dict()
        M=self.meridional(self.phi)
        sc=1.0/_c
        self.transforms['I']     = M + self.N0
        self.transforms['II']    = ncs(1,1)/2.0
        self.transforms['III']   = ncs(3,1)*(5-t(2)+9*self.n(2))/24.0
        self.transforms['IIIA']  = ncs(5,1)*(61-58*t(2)+t(4))/720.0
        self.transforms['IV']    = ncs(1,0)
        self.transforms['V']     = ncs(3,0)*(eta1-t(2))/6.0
        self.transforms['VI']    = ncs(5,0)*(5 - 18*t(2) + t(4) + 14*eta2 - 58*t(2)*eta2)/120.0
        self.transforms['VII']   = t(1)/(2*rhoNu(1))
        self.transforms['VIII']  = t(1)/(24*rhoNu(3))*(5+3*t(2)+eta2-9*t(2)*eta2)
        self.transforms['IX']    = t(1)/(720*rhoNu(5))*(61+90*t(2)+45*t(4))
        self.transforms['X']     = sc/_nu
        self.transforms['XI']    = sc/(6*nu(3)*(eta1+2*t(2)))
        self.transforms['XII']   = sc/(120*nu(5)*(5+28*t(2)+24*t(4)))
        self.transforms['XIIA']  = sc/(5040*nu(7)*(61+662*t(2)+1320*t(4)+720*t(6)))
    
    def __getitem__(self,key):
        return self.transforms[key]
       
    def rhoNu(self,power):
        return self.rho*pow(self.nu,power)
    
    def Nu(self,power):
        return pow(self.nu,power)
    
    def s(self,power):
        return pow(self._s,power)
    
    def c(self,power):
        return pow(self._c,power)
    
    def t(self,power):
        return pow(self._t,power)
    
    @classmethod
    def n(cls,power=1):
        return pow(OSDefaultGrid.ellipsoid.n,power)
    
    def gridToLatLong(self):
        dE = self.E-OSDefaultGrid.E0
        phi = self.phi - self['VII']*pow(dE,2) + self['VIII']*pow(dE,4) - self['IX']*pow(dE,6)
        l = OSDefaultGrid.l0 + self['X']*dE - self['XI']*pow(dE,3) + self['XII']*pow(dE,5) - self['XIIA']*pow(dE,7)
        return (phi,l)
    
    def latLongToGrid(self):
        dl = self.E-OSDefaultGrid.l0
        N = self['I'] + self['II']*pow(dl,2) + self['III']*pow(dl,4) + self['IIIA']*pow(dl,6)
        E = OSDefaultGrid.E0 + self['IV']*dl + self['V']*pow(dl,3) + self['VI']*pow(dl,5)
        return (E,N)
    
    @classmethod
    def meridional(cls,phi):
        return cls.ellipsoid.meridional(phi,cls.phi0)*cls.bF0()
    
    @classmethod
    def aF0(cls):
        return cls.ellipsoid.a*cls.F0
    
    @classmethod
    def bF0(cls):
        return cls.ellipsoid.b*cls.F0
