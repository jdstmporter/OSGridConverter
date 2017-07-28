'''
Created on 26 Jul 2017

@author: julianporter
'''

import unittest
import traceback
from OSGridConverter import OSGridReference, LatLong
import random
from math import pi,sqrt
from pip._vendor.requests.packages.chardet.constants import eError

class TestSet(object):
    def __init__(self,nTests,error,tag='OSGB36'):
        self.nTests=nTests
        self.error=error
        self.tag=tag
        self.exceptions=0
        self.count=0
        self.good=0
        print('Ntest = {} error = {}'.format(self.nTests,self.error))
    
    def makeLatLong(self):
        latitude  = random.uniform(50.0,59.0)
        longitude = random.uniform(-5.0,2.0)
        return LatLong(latitude,longitude,tag=self.tag)
    
    def makeGrid(self):
        ll=self.makeLatLong()
        return OSGridReference(ll)

    
    def test(self):
        print('')
        for _ in range(self.nTests):
            try:
                good, count = self.action()
                self.good+=good
                self.count+=count
            except Exception as e:
                self.exceptions+=1
                print(str(e))
                traceback.print_exc()
    def action(self):
        return (0,0)
    
    def successRate(self):
        return 100.0*self.good/self.count
       
    def crashRate(self):
        return 100.0*self.exceptions/self.nTests
    
    

class GridToLatLongAndBack(TestSet):
 
        
    def action(self):
        grid1=self.makeGrid()
        if len(str(grid1))>0:
            ll=grid1.toLatLong(tag=self.tag, viaString=True)
            grid2=OSGridReference(ll)
            parts1=[x[:3] for x in str(grid1).split(' ')]
            parts2=[x[:3] for x in str(grid2).split(' ')]
            er=all([parts1[i]==parts2[i] for i in range(3)])
            error=max([abs(x) for x in (grid1.E-grid2.E,grid1.N-grid2.N)])
            print('{} - {} - {} - {} : {} {}'.format(grid1,grid2,grid1.eastNorth(),grid2.eastNorth(),error,er))
            if error<self.error: return(1,1)
            else: return(0,1)
        else:
            return (0,0)

                
   

class LatLongToGridAndBack (TestSet):
            
    def action(self):
        ll1=self.makeLatLong()
        grid=OSGridReference(ll1)
        ll2=grid.toLatLong(tag=self.tag)
        g2=OSGridReference(ll2)
        error=(ll1.latitude-ll2.latitude,ll1.longitude-ll2.longitude)
        er=max([abs(e) for e in error]) < self.error
        print('{} - {} - {} - {} : {} {}'.format(ll1,grid,ll2,g2,error,er))
        
        if er: return (1,1)
        else: return (0,1)
        
    
         
                           
class TestConversion(unittest.TestCase):
    
    N_TESTS=100
    EARTH_RADIUS=6.371e6
    GRID_SQUARE=1.0e5
    
    @classmethod
    def accuracy(cls):
        circumference=cls.EARTH_RADIUS*2.0*pi
        angle=360.0*cls.GRID_SQUARE/circumference
        return angle*2.0
    
    def test_latlong_accuracy(self):
        tester=LatLongToGridAndBack(self.N_TESTS,self.accuracy()) 
        tester.test()
        print('Percentage latlong match in bounds is {}'.format(tester.successRate()))
        
        self.assertTrue(tester.successRate()>=95.0) 
        
    def test_grid_accuracy(self):
        tester=GridToLatLongAndBack(self.N_TESTS,300) 
        tester.test()
        print('Percentage grid match is {}'.format(tester.successRate()))
        
        self.assertTrue(tester.successRate()>=95.0) 
        
    def test_failure(self):
        tester=LatLongToGridAndBack(self.N_TESTS,self.accuracy()) 
        tester.test()
        print('Percentage crashed {}'.format(tester.crashRate()))
        
        self.assertEqual(tester.exceptions,0)          

if __name__ == '__main__':
    print('Running 100 lat/long -> National Grid -> lat / long conversions')
    unittest.main()
