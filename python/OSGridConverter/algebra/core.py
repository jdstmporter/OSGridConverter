'''
Created on 17 Mar 2018

@author: julianporter
'''

from numbers import Number

def dot(v1,v2):
    return sum([x*y for (x,y) in zip(v1,v2)])

def allLists(args):
    return all([isinstance(x,list) for x in args])

def isList(x):
    return isinstance(x,list)
def allNumbers(args):
    return all([isinstance(x,Number) and not isinstance(x,bool) for x in args])