BASEDIR := "src"

LIBNAME := "libos.a"
APPNAME := "geo"
ARFLAGS := "cr"
RM := rm -f

cXX := g++
CFLAGS := -O0 -Wall -c -fmessage-length=0
CPPFLAGS := 
LINKERFLAGS := 

objects := $(patsubst %.cpp,%.o,$(shell find $(BASEDIR) -name *.cpp))



#lib : $(objects)
#	$(AR) $(ARFLAGS)  $(LIBNAME) $(objects)
	



default :  $(objects)
	$(CXX) $(LINKERFLAGS) -o $(APPNAME) $(objects) 
	chmod 755 $(APPNAME)
	
clean :
	$(RM) $(objects)
	
list: $(objects)
	@echo objects = $(objects)
	
%.o : %.c
	$(CXX) -c $(CFLAGS) $(CPPFLAGS)  $< -o $@
	

	
	

