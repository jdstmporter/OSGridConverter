'''
Created on 4 Dec 2017

@author: julianporter
'''

from tempfile import mkdtemp
import os
import shutil
from distutils import ccompiler, sysconfig, errors 
from sys import argv
import traceback

HelloWorld='''
#include<iostream>
int main(int argc, char* argv[])
{
    std::cout << "hello world" << std::endl;
    return 0;
}
'''

class DependencyError(Exception):
    
    def __init__(self,message,inner=None):
        super(DependencyError,self).__init__()
        self.message=message
        self.inner=inner
        
    def __str__(self):
        if not self.inner:
            st="Dependency exception: {}"
            args=[self.message]
        else:
            st="Dependency exception: {}  Inner {} : {}"
            args=[self.message,type(self.inner).__name__,str(self.inner)]
        return st.format(*args)

class CheckDependencies(object):
    
    def __init__(self,prefix):
        self.tmp=mkdtemp(prefix=prefix)
        self.src=os.path.join(self.tmp,'hello.cpp')
        self.exe=os.path.join(self.tmp,'hello')
        try: 
            with open(self.src,'w') as file:
                file.write(HelloWorld)
        except Exception as e:
            traceback.print_exc()
            raise DependencyError('Cannot create source file',inner=e)
        self.results={}
        
 
    
    def preCompilationTest(self,compiler):
        pass
    
    def postCompilationTest(self,compiler,object):
        pass
    
    def test(self):
        try:
            compiler = ccompiler.new_compiler()
            if not isinstance(compiler, ccompiler.CCompiler):
                raise errors.CompileError("Compiler is not valid!")
            sysconfig.customize_compiler(compiler)
            
            self.preCompilationTest(compiler)
            o=compiler.compile([self.src])
            self.postCompilationTest(compiler,o)
            
        except errors.CompileError as e:
            raise DependencyError('Compilation problems',inner=e)
        except Exception as e:
            raise DependencyError('General error',inner=e)
        
    def clean(self):
        try:
            shutil.rmtree(self.tmp)
        except:
            pass
        
    def run(self):
        
        
        try:
            self.test()
        except Exception as e:
            print('Problem: {}'.format(e))
        finally:
            self.clean()
        for key,value in self.results.items():
            if not value:
                print('Test {} failed'.format(key))
                return False
        print('Test passed')
        return True
            



class CheckLibrary(CheckDependencies):
    
    def __init__(self,*libs):
        super(CheckLibrary,self).__init__('_libsearch')
        self.libraries=libs
        
    def postCompilationTest(self,compiler,o):
        for lib in self.libraries:
            try:
                exe=self.exe+"_"+lib
                compiler.link_executable(o,exe,libraries=[lib,'stdc++'])
                self.results[lib]=True
            except Exception as e:
                self.results[lib]=False

class CheckCompiler(CheckDependencies):
    
    def __init__(self,args):
        super(CheckCompiler,self).__init__('_compilersearch')
        self.args=args
        
    def preCompilationTest(self,compiler):
        cflags=os.environ.get('CFLAGS',' ')
        os.environ['CFLAGS']=cflags+self.args
        self.results['c++14']=False
        
    def postCompilationTest(self,compiler,o):
        self.results['c++14']=True
        
    
        
          
    
    
def libs(*args):
    c=CheckLibrary(*args)
    c()
    for lib in c:
        print("{} : {}".format(lib,c[lib]))     
    
            
def gcc(*args):
    c=CheckCompiler(*args)
    c()
    for lib in c:
        print("{} : {}".format(lib,c[lib]))  

    
    
    
            
        

