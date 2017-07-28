'''
Created on 28 Jul 2017

@author: julianporter
'''
import unittest
from .types import Generator
import traceback
VERBOSE=False


class TestFramework(unittest.TestCase):
    
    testName='test'
    
    def setUp(self):
        self.generator=Generator()
        self.nTests=1000
        self.errors=[]
        self.good=0
        self.count=0
        self.crashes=0
        
    def testAction(self):
        for _ in range(self.nTests): 
            try:
                self.good+=self.action()
                self.count+=1
            except:
                traceback.print_exc()
                self.crashes+=1
        if len(self.errors)==0:
            print('{} tests : count={}, good = {}, crashes = {}'.format(self.nTests,self.count,self.good,self.crashes))
        else:
            print('{} tests : count={}, good = {}, minimum log10 error = {}, crashes = {}'.format(self.nTests,self.count,self.good,min(self.errors),self.crashes))
        
        self.assertEqual(self.good,self.count)
     
    def action(self):
        return 1
    
    def push(self,e,threshold=10.0):
        self.errors.append(e)
        if e>threshold : return 1
        else: return 0
           
    def tearDown(self):
        pass