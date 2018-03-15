#!/usr/bin/python3
'''
Created on 14 Mar 2018

@author: julianporter
'''

from OSGridConverter.cartesian import Matrix

if __name__ == '__main__':
    
    m=Matrix.rotation('X',0.1)
    n=Matrix.rotation('Y',0.1)
    o=Matrix.rotation('Z',0.1)
    print(m)
    print(n)
    print(o)
    
    