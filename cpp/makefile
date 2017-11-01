SRCDIR := src
CXX := g++
CFLAGS := -g3 -Wall -fmessage-length=0
CPPFLAGS := -std=c++14 -O0 -Isrc  
LINKERFLAGS := -lcppunit
CPPINCLUDES := -I"$(SRCDIR)" 
APPNAME := geotest

objects := $(patsubst %.cpp,%.o,$(shell find $(SRCDIR) -name '*.cpp'))


	
app: $(objects)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LINKERFLAGS) $(objects) -o	$(APPNAME)
	chmod 755 $(APPNAME)
	
	

	
.PHONY: clean

clean:
	$(RM) $(objects)
	
	
list:
	@echo $(objects)
	
%.o : %.c
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(CPPINCLUDES) -c $< -o $@

	





