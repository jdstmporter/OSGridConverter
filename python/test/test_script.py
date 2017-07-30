'''
Created on 26 Jul 2017

@author: julianporter
'''

import unittest
from .baseTest import TestFramework
from OSGridConverter import OSGridReference
from .types import gridDiff,latlongDiff


class GridToLatLongAndBack(TestFramework):
    
    testName='grid to lat/long to grid'
    
    def setUp(self):
        super(GridToLatLongAndBack,self).setUp()
        self.tag='WGS84'
    
    def action(self):
        grid1=self.generator.randomGrid(tag=self.tag)
        if len(str(grid1))>0:
            ll=grid1.toLatLong(tag=self.tag, viaString=True)
            grid2=OSGridReference(ll)
            error=gridDiff(grid1,grid2)
            #ratio=ll.logErrorRatio;
            #print('{}  {} -  {}  {}  : {} {}'.format(grid1,grid1.eastNorth(),grid2,grid2.eastNorth(),error,ratio))
            self.push(error,3)
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
        ll1=self.generator.randomLatLong(tag=self.tag)
        grid=OSGridReference(ll1)
        ll2=grid.toLatLong(tag=self.tag)
        #e=(ll1.latitude-ll2.latitude,ll1.longitude-ll2.longitude)
        error=latlongDiff(ll1,ll2)
        #ratio=ll1.errorRatio;
        #lratio=ll1.logErrorRatio;
        #print('{} - {} - {} : {} {} {}'.format(ll1,grid,ll2,e,ratio,lratio))
        return  self.push(error,3)
        
        
        
        
    
 
if __name__ == '__main__':
    print('Running 100 lat/long -> National Grid -> lat / long conversions')
    unittest.main()
