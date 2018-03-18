'''
Created on 17 Mar 2018

@author: julianporter
'''

class LoggerMetaclass(type):
    
    def __new__(cls,name,bases,namespace):
        if '_registry' not in namespace:
            namespace['_registry']=dict()
            
            def instance(kl,name):
                return kl._registry[name]
            
            namespace['instance']=classmethod(instance)
            
        return super(LoggerMetaclass,cls).__new__(cls,name,bases,namespace)
    
    def __call__(cls,*args,**kwargs):
        print("Metaclass called with {} and {}".format(args,kwargs))
        obj=super(LoggerMetaclass,cls).__call__(*args,**kwargs)
        if 'name' in kwargs:
            cls._registry[kwargs['name']]=obj
        return obj
        
        