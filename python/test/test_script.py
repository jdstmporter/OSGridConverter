'''
Created on 26 Jul 2017

@author: julianporter
'''

import unittest
from .baseTest import TestFramework
from OSGridConverter import OSGridReference, LatLong
from math import log10
import random

def gridDiff(g1,g2):
    e=max([abs(x-y) for (x,y) in zip(g1.eastNorth(),g2.eastNorth())])
    if e==0 : return 1000.0
    return 6-log10(e)

def latlongDiff(l1,l2):
    e=(l1.latitude-l2.latitude,l1.longitude-l2.longitude)
    e=max([abs(x) for x in e])
    if e==0 : return 1000.0
    return 3-log10(e)

def randomLatLong(tag='WGS84'):
    latitude  = random.uniform(50.0,59.0)
    longitude = random.uniform(-5.0,2.0)
    return LatLong(latitude,longitude,tag=tag)
    
def randomGrid(tag='WGS84'):
    ll=randomLatLong(tag=tag)
    return OSGridReference(ll)
    

class GridToLatLongAndBack(TestFramework):
    
    testName='grid to lat/long to grid'
    
    def setUp(self):
        super(GridToLatLongAndBack,self).setUp()
        self.tag='WGS84'
    
    def action(self):
        grid1=randomGrid(tag=self.tag)
        if len(str(grid1)) == 0 : raise Exception('Bad grid')
            
        ll=grid1.toLatLong(tag=self.tag, viaString=True)
        grid2=OSGridReference(ll)
        error=gridDiff(grid1,grid2)
        ratio=ll.logErrorRatio;
        print('{}  {} -  {}  {}  : {} {}'.format(grid1,grid1.eastNorth(),grid2,grid2.eastNorth(),error,ratio))
        self.errors.append(error)
        er=(str(grid1)==str(grid2)) or (error>3.0)
        if er: return 1
        else:
            print('{}  {} -  {}  {}  : {} {}'.format(grid1,grid1.eastNorth(),grid2,grid2.eastNorth(),error,er))
            return 0


                
   

class LatLongToGridAndBack (TestFramework):
    
    testName='lat/long to grid to lat/long'
    
    def setUp(self):
        super(LatLongToGridAndBack,self).setUp()
        self.tag='WGS84'
        self.error=10
            
    def action(self):
        ll1=randomLatLong(tag=self.tag)
        grid=OSGridReference(ll1)
        ll2=grid.toLatLong(tag=self.tag)
        #e=(ll1.latitude-ll2.latitude,ll1.longitude-ll2.longitude)
        error=latlongDiff(ll1,ll2)
        #ratio=ll1.errorRatio;
        #lratio=ll1.logErrorRatio;
        #print('{} - {} - {} : {} {} {}'.format(ll1,grid,ll2,e,ratio,lratio))
        self.errors.append(error)
        if error>3 : return 1 
        else: return 0
        
        
        
        
        
    
 
def runTests():
    suite=unittest.TestSuite()
    suite.addTest(GridToLatLongAndBack('test_action'))
    suite.addTest(LatLongToGridAndBack('test_action'))
    print('Running 100 lat/long -> National Grid -> lat / long conversions')
    runner=unittest.TextTestRunner()
    runner.run(suite)
