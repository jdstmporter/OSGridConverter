'''
Created on 28 Jul 2017

@author: julianporter
'''
import unittest
from .baseTest import TestFramework
from .types import equalMatrices, equalVectors, vectorDiff, matrixDiff
import numpy as np
from OSGridConverter.cartesian import Transform, Matrix




class TestVectorEquality(TestFramework):
    
    testName='vector creation'
    
    def action(self):
        np, v=self.generator.randomVectorPair()
        if equalVectors(np, v): return 1
        else: return 0

class TestVectorNegation(TestFramework):
    
    testName='vector negation'
        
    def action(self):

        np, v=self.generator.randomVectorPair()
        if equalVectors(-np, -v): return 1
        else: return 0
        
class TestDotProduct(TestFramework):
    
    testName='dot product'
        
    def action(self):
        np1, v1=self.generator.randomVectorPair()
        np2, v2=self.generator.randomVectorPair()
        if np.dot(np1,np2) == v1 | v2 : return 1
        else: return 0
        
class TestVectorSum(TestFramework):
    
    testName='vector sum'
        
    def action(self):
        np1, v1=self.generator.randomVectorPair()
        np2, v2=self.generator.randomVectorPair()
        if equalVectors(np1+np2,v1+v2) : return 1
        else: return 0
        
class TestMatrixSum(TestFramework):
    
    testName='matrix sum'
        
    def action(self):
        np1, v1=self.generator.randomMatrixPair()
        np2, v2=self.generator.randomMatrixPair()
        if equalMatrices(np1+np2,v1+v2) : return 1
        else: return 0
        
class TestMatrixVectorProduct(TestFramework):
    
    testName='matrix vector product'
        
    def action(self):
        np1, v1=self.generator.randomMatrixPair()
        np2, v2=self.generator.randomVectorPair()
        pr1 = np1@np2
        pr2 = v1@v2
        e=vectorDiff(pr1, pr2)
        return self.push(e)
    
class TestMatrixMatrixProduct(TestFramework):
    
    testName='matrix matrix product'
        
    def action(self):
        np1, v1=self.generator.randomMatrixPair()
        np2, v2=self.generator.randomMatrixPair()
        pr1 = np.transpose(np1@np2)
        pr2 = v1@v2
        e=matrixDiff(pr1, pr2)
        return self.push(e)
        
class TestHelmertInversion(unittest.TestCase):
    
    testName='Helmert matrix inversion'
 
    def setUp(self):
        super(TestHelmertInversion,self).setUp()
        self.i3=Matrix.identity(n=3)
        
    def action(self):
        t=self.generator.randomList()
        r=self.generator.randomList()
        s=self.generator.randomScalar()
        h=Transform(t,r,s).mx
        i=h.inverse()
        pr1 = h@i
        e= matrixDiff(pr1, self.i3)
        return self.push(e)
          

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()