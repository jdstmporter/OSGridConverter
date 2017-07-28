'''
Created on 27 Jul 2017

@author: julianporter
'''
import traceback
from numbers import Number
import logging

class OSGridError(Exception):
    
    def __init__(self,message,inner=None):
        super(OSGridError,self).__init__()
        self.message='OSGridConverter error: {}'.format(message)
        self.inner=inner
        self.traceback=traceback.format_stack()
        
    def __str__(self):
        return self.message
    
def areNumbers(args):
    return all([isinstance(x,Number) and not isinstance(x,bool) for x in args])

class Log(object):
    
    def __init__(self,level=None):
        self.logger=logging.getLogger()
        if level:
            handler=logging.StreamHandler()
            self.logger.setLevel(level)
        else:
            handler=logging.NullHandler()
        self.logger.addHandler(handler)
        
    def debug(self,*args):
        self.logger.debug(args[0].format(*args[1:]))
        
    def info(self,*args):
        self.logger.info(args[0].format(*args[1:]))
        
    def warning(self,*args):
        self.logger.warning(args[0].format(*args[1:]))
        
    def error(self,*args):
        self.logger.error(args[0].format(*args[1:]))
        
    def exception(self,e):
        self.logger.error('{} {}',e,traceback.format_exc())

log=Log()
    
        