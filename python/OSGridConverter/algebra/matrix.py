'''
Created on 17 Mar 2018

@author: julianporter
'''
from OSGridConverter.base import OSGridError
from .vector import Vector
from .core import isList, allLists,allNumbers



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
        return Matrix(rows)
    
 

        
    
    def __init__(self,arg):
        if isinstance(arg,Matrix):
            self.rows=[row[:] for row in arg.rows]
        else:
            try:
                check=all([allNumbers(row) for row in arg])
                if not check: raise Exception()
                self.rows=[row[:] for row in arg] 
            except:
                raise OSGridError('Constructor requires Matrix or [[numeric]]')
        
        self.nRows=len(self.rows)
        if self.nRows==0:
            self.nColumns=0
        else:
            self.nColumns=len(self.rows[0])
            for row in self.rows:
                if len(row)!=self.nColumns:
                    raise OSGridError("All rows in array must have same length")
            
    def row(self,index):
        return self.rows[index]
    
    def column(self,index):
        return [r[index] for r in self.rows]
    
    @property
    def columns(self):
        return [self.column(i) for i in range(0,self.nColumns)]
    
    @property
    def size(self):
        return (self.nRows,self.nColumns)
    
    def __add__(self,other):
        if self.size != other.size:
            raise OSGridError('Sum requires elements of same size')
        rows=[x+y for (x,y) in zip(self.rows,other.rows)]
        return Matrix(rows)

    def __matmul__(self,other):
        if self.nColumns!=other.nRows:
            raise OSGridError('Product requires elements with compatible sizes')
        
        col=other.columns
        if len(col)==1:
            c=col[0]
            return Vector([row|c for row in self.rows])
        else:
            return Matrix([[row|c for c in col] for row in self.rows] )

        
    def __mul__(self,other):
        return Matrix([r*other for r in self.rows])
    
    def __rmul__(self,other):
        return Matrix([other*r for r in self.rows])
        
    def __str__(self):
        return '[{}]'.format(','.join([str(row) for row in self.rows]))
    
    def __eq__(self,other):
        return all([self.row[i]==other.row[i] for i in range(self.nRows)])
                
                