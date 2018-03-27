'''
Created on 2 Dec 2017

@author: julianporter
'''
from .findSource import findFiles
from setuptools import Command
import shutil
import os

class Cleaner(Command) :
    
    
    description='Perform a true deep clean, removing distributions, builds and egg-info'
    
    user_options=[]
    
    def __init__(self,dist,**kwargs):
        super(Cleaner,self).__init__(dist,**kwargs)
        
    def initialize_options(self):
        self.directories=[]
        self.files=[]
    
    def finalize_options(self):
        self.directories=['build','dist','geoconv.egg-info']
        self.files=[]
    
    def run(self):
        for directory in self.directories:
            try:
                shutil.rmtree(directory)
                print(f"{directory} deleted")
            except FileNotFoundError:
                print(f"{directory} does not exist, so not deleted...")
            except Exception as e:
                print(f"{e.__class__.__name__} : {e}")
        for file in self.files:
            try:
                os.remove(file)
                print(f"{directory} deleted")
            except FileNotFoundError:
                print(f"{directory} does not exist, so not deleted...")
            except Exception as e:
                print(f"{e.__class__.__name__} : {e}")
            
        objects=findFiles('/opt/git/OSGridConverter/cpp/',pattern=r'^.*\.o$')
        print('Files are:')
        for o in objects: print(f'    {o}')
        
        for o in objects:
            print(f'Removing {o}')
            os.remove(o)
        
        