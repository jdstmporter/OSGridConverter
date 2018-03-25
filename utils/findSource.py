'''
Created on 24 Mar 2018

@author: julianporter
'''

import os
import re


class FileFinder(object):
    
    def __init__(self,root,dirs=[],pattern=r'^.*$'):
        self.root=root
        self.dirs=[os.path.join(root,d) for d in dirs]
        self.pattern=pattern
        self.out=[]
        
    def _check(self,directory):
        if len(self.dirs)==0: return True
        return any([directory.startswith(d) for d in self.dirs])
    
    def find(self):
        #print(f'Dirs are {self.dirs}')
        self.out=[]
        for d,_,files in os.walk(self.root):
            #print(f'Directory {d}, files {files}')
            if self._check(d):
                matchers=[os.path.join(d,f) for f in files if re.fullmatch(self.pattern,f)]
                self.out.extend(matchers)

def findFiles(root,dirs=[],pattern=r'^.*$'):
    f=FileFinder(root,dirs,pattern)
    f.find()
    return f.out
            
if __name__=='__main__':
    o=findFiles('/opt/git/OSGridConverter/cpp',dirs=['src','python'],pattern=r'^.*\.cpp$')
    for f in o: print(f)     