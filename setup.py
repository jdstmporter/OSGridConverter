#!/usr/bin/python3
'''
Created on 1 Dec 2017

@author: julianporter
'''
from setuptools import setup, Extension
from setuptools.config import read_configuration
import utils
from collections import namedtuple
from sys import exit


checker=utils.CheckCompiler('-std=c++14')
if not checker.run():
    print("Cannot build pcm2mp3 unless compiler supports -std=c++14")
    exit(1)



configuration=read_configuration('setup.cfg')
metadata=configuration['metadata']


src=utils.findFiles('/opt/git/OSGridConverter/cpp',dirs=['src','python'],pattern=r'^.*\.cpp$')
for f in src: print(f)
Version = namedtuple('Version',['major','minor','maintenance'])
def processVersion():
    version=metadata['version']
    parts=version.split('.')
    if len(parts)<3: parts.extend([0,0,0])
    return Version(*(parts[:3]))

def makeExtension(module,src):
    #print("Making {} with {}".format(module,src))
    
    v=processVersion()
    return Extension(module,
                    define_macros = [('MAJOR_VERSION', v.major),
                                     ('MINOR_VERSION', v.minor),
                                     ('MAINTENANCE_VERSION', v.maintenance)],
                    sources = src,
                    language = 'c++',
                    include_dirs=['/usr/include','cpp/src'],
                    library_dirs = ['/usr/lib/x86_64-linux-gnu'])

coder = makeExtension('geoconv',src)

with open('README.md') as readme:
    longDescription = readme.read()

setup (
    cmdclass = {'cleaner' : utils.Cleaner },
    ext_modules = [coder],
    long_description = longDescription 
)
