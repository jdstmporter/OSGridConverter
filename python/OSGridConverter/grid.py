'''
Created on 19 Jul 2017

@author: julianporter
'''


import re
from math import radians, degrees , pow, floor
from numbers import Number
from .mapping import OSDefaultGrid
from .latlong import LatLong
from .base import OSGridError, areNumbers, log
import traceback

        
    

def areNumbers(args):
    return all([isinstance(x,Number) and not isinstance(x,bool) for x in args])

class OSGridReference (object):
    
    alphabet='ABCDEFGHJKLMNOPQRSTUVWXYZ'
    
 
    def __init__(self,*args):
        if len(args)==0: raise OSGridError('Initialisation of OSGRidReference requires at least one argument')
        arg=args[0]
        
        if isinstance(arg,str):
            log.debug('Parsing {}',arg)
            gridref = arg.strip().upper()

            log.debug('gridref is {}',gridref)
            match = re.match('^(\d+),\s*(\d+)$',gridref)
            if match:
                log.debug('Matched pair of numbers')
                return [int(x) for x in match.groups()]
        

            match = re.match('^([A-Z]{2})\s*([0-9]+)(\s*)([0-9]+)$',gridref)
            if not match:
                log.error("Couldn't match expected format")
                raise OSGridError('Invalid grid reference')
        
            g=match.groups()
            alpha=g[0]
            l1 = ord(alpha[0]) - ord('A')
            l2 = ord(alpha[1]) - ord('A')
       
            if l1 > 7 : l1-=1
            if l2 > 7 : l2-=1
    
            e100km = ((l1-2)%5)*5 +  (l2%5)
            n100km = 19-5*(l1//5) - l2//5
            log.debug("e100k = {}, n100k = {}",e100km,n100km)
            if e100km<0 or e100km>6 or n100km<0 or n100km>12:
                log.error("e100k = {}, n100k = {} - OOR",e100km,n100km)
                raise OSGridError('Invalid grid reference')
    
            if len(g[2])==0 :
                s=g[1]+g[3]
                c=len(s)//2
                en=[s[:c],s[c:]]
            else:
                en=[g[1],g[3]]
    
            if len(en[0]) != len(en[1]):
                log.error('e=*{}* n=*{}* - unequal lengths',*en)
                raise OSGridError('Invalid grid reference')
            
            
            en=[int((x+'00000')[:5]) for x in en ]
            log.debug('EN is {}',en)
            factor=pow(10,5)
            parsed= [en[0]+e100km*factor,en[1]+n100km*factor]

        elif isinstance(arg,LatLong):
            if arg.tag!='OSGB36' : 
                log.debug("Transforming {} to OSGB36",arg)
                arg=arg.transform('OSGB36')
                log.debug("Transformed value is {}",arg)
            phi=radians(arg.latitude)
            l  =radians(arg.longitude)
        
            log.debug("phi = {}, l = {}",phi,l)
            v=OSDefaultGrid(phi,l)
            parsed = v.latLongToGrid()
            
        elif len(args)>=2 and areNumbers(args[:2]):
            parsed=args[:2]
        else:
            raise OSGridError('Arguments to OSGridRef constructor must be string or LatLong or E,N')
        
        log.debug('out is {}',parsed)
        self.E, self.N = [floor(x) for x in parsed] # [round(x,0) for x in parsed]
        log.debug("E = {}, N = {}",self.E,self.N)
    

         
    def toLatLong(self,tag='WGS84',viaString=False) :
        if viaString:
            g=OSGridReference(str(self))
            return g.toLatLong(tag=tag,viaString=False)
        
        phi=OSDefaultGrid.phi0
        M=0
        
        log.debug('Starting loop with phi = {}',phi)
        dN=self.N-OSDefaultGrid.N0
        while True:
            phi += (dN-M)/(OSDefaultGrid.aF0())
            M=OSDefaultGrid.meridional(phi)
            if dN-M < 1.0e-5: break
        
        log.debug('Ending loop with phi = {}',phi)
        
        v=OSDefaultGrid(phi,self.E)
        phi,l = v.gridToLatLong()
        
        point =  LatLong(degrees(phi), degrees(l), tag='OSGB36');
        if (tag != 'OSGB36') : 
            point = point.transform(tag)
        return point
    
    def __str__(self):
        try:
            E=int(self.E)
            N=int(self.N)
            e100k = E//100000
            n100k = N//100000
    
            if e100k<0 or e100k>6 or n100k<0 or n100k>12: 
                log.error("e100k = {}, n100k = {} - OOR",e100k,n100k)
                raise OSGridError('Position out of range')
            
            nf=19-n100k
            ef=10+e100k
            
            l1 = nf - (nf%5) + (ef//5)
            l2 = (5*nf)%25 + (ef%5)
            l = [l1,l2]
            log.debug("l = {}",l)
            rect = ''.join([OSGridReference.alphabet[int(x)] for x in l])
            log.debug("l = {}, rect = {}",l,rect)
            
            e = E%100000
            n = N%100000
            log.debug('e = {}, n = {}',e,n)
            
            return ' '.join([rect,str(e).rjust(5,'0'),str(n).rjust(5,'0')])
        except:
            traceback.print_exc()
            log.debug('{}',traceback.format_exc())
            return ''

    def eastNorth(self):
        return (self.E, self.N)
    
    
 

