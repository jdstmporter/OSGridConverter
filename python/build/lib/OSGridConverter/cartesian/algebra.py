'''
Created on 27 Jul 2017

@author: julianporter
'''

from math import sqrt
from ..base import OSGridError, areNumbers

def dot(a1,a2):
    zipped=zip(a1,a2)
    mixed=map(lambda p : p[0]*p[1],zipped)
    return sum(mixed)



class Vector(object):
    
    @classmethod
    def zero(cls,n=3):
        return Vector([0]*n,n=n)
        
    def __init__(self,args,n=3):
        self.n=n
        if len(args)!=n : raise OSGridError('Constructor of Vector takes {} arguments'.format(n))
        if isinstance(args,Vector):
            self.array=args.array
        elif areNumbers(args):
            self.array=args
        else:
            raise OSGridError('Constructor of Vector rerquires Vector or [numeric] arguments')
    
    def __len__(self):
        return self.n
       
    def __iter__(self):
        return iter(self.array)
    
    def __getitem__(self,key):
        return self.array[key]

    def _i(self,array):
        return Vector(array,n=self.n)
    
    def __add__(self,other):
        return self._i([x+y for (x,y) in zip(self,other)])
    
    def __sub__(self,other):
        return self._i([x-y for (x,y) in zip(self,other)])
    
    def __neg__(self):
        return self._i([- x for x in self.array])
    
    def __mul__(self,other):
        return self._i([x*other for x in self.array])
    
    def __rmul__(self,other):
        return self._i([x*other for x in self.array])
    
    def __or__(self,other):
        return sum([x*y for (x,y) in zip(self,other)])
    
    def __eq__(self,other):
        return all([x==y for (x,y) in zip(self,other)])
    
    def __str__(self):
        return str(self.array)
    
    
class Vector3(Vector):
    
    def __init__(self,args):
        super(Vector3,self).__init__(args,n=3)
        self.x, self.y, self.z = self.array
        
    @property
    def p(self):
        return sqrt(self.x*self.x + self.y*self.y)
    
    @property
    def R(self):
        return self.p*self.p+self.z*self.z
            
class Matrix(object):
    
    @classmethod
    def outerProduct(cls,left,right=None,n=3):
        r= right or left
        if len(left)!=n or len(r)!=n:
            raise OSGridError('Outer product requires two vectors of length {}'.format(n))
        rows=[r*rv for rv in left]
        return Matrix(rows,n)
    
    @classmethod
    def identity(cls,n=3):
        rows=[]
        for i in range(n):
            r=[0]*n
            r[i]=1
            rows.append(r)
        return Matrix(rows,n=n)
        
    
    def __init__(self,rows,n=3):
        self.n=n
        if len(rows)!=n or any([len(r)!=3 for r in rows]):
            raise OSGridError('Constructor of Matrix takes {} rows of {} numeric arguments'.format(n,n))
            
        self.rows=[Vector(row,n=self.n) for row in rows]
        self.columns=[Vector([row[index] for row in self.rows],n=self.n) for index in range(self.n)]
            
    def row(self,index):
        return self.rows[index]
    
    def column(self,index):
        return self.columns[index]
    
    def __getitem__(self,index):
        return self.rows[index]
    
    def __len__(self):
        return self.n
    
    def __abs__(self):
        return sum([x*x for x in self])
    
    def __add__(self,other):
        if len(self)!=len(other):
            raise OSGridError('Sum requires elements of same size')
        rows=[x+y for (x,y) in zip(self.rows,other.rows)]
        return Matrix(rows)

    def __matmul__(self,other):
        if len(self)!=len(other):
            raise OSGridError('Product requires elements of same size')
        
        if isinstance(other,Vector):
            row=[row|other for row in self.rows]
            return Vector(row,n=self.n)
        elif isinstance(other,Matrix):
            rows=[self @ column for column in other.columns]
            return Matrix(rows,n=self.n)
        else:
            raise OSGridError('Product requires Vector or Matrix')
        
    def __mul__(self,other):
        return Matrix([r*other for r in self.rows],n=3)
    
    def __rmul__(self,other):
        return Matrix([other*r for r in self.rows],n=3)
        
    def __str__(self):
        return '[{}]'.format(','.join([str(row) for row in self.rows]))
    
    def __eq__(self,other):
        return all([self.row[i]==other.row[i] for i in range(self.n)])
                
                
            
    
    