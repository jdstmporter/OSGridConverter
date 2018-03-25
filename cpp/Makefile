SRCDIR := src
TESTDIR := tests
CXX := g++
CFLAGS := -g3 -Wall -fmessage-length=0
CPPFLAGS := -std=c++14 -O3 -Isrc  
LINKERFLAGS := -lcppunit
CPPINCLUDES := -I"$(SRCDIR)" 
APPNAME := geotest
LIBNAME := libosgridconv.a


hpp := $(shell find $(SRCDIR) -name '*.hpp')
headerDirs :=  $(sort $(dir $(patsubst src%,include%,$(hpp))))
lib_objects := $(patsubst %.cpp,%.o,$(shell find $(SRCDIR) -name '*.cpp'))
test_objects := $(patsubst %.cpp,%.o,$(shell find $(TESTDIR) -name '*.cpp'))
all_objects := $(lib_objects) $(test_objects)
	
test: $(all_objects)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LINKERFLAGS) $(all_objects) -o	$(APPNAME)
	chmod 755 $(APPNAME)

.PHONY: all
all: $(LIBNAME)

$(LIBNAME): $(lib_objects)
	ar r $@ $^
	ranlib $@	


.PHONY: includes

includes:
	mkdir -p "include"
	$(foreach d,$(headerDirs),$(shell mkdir -p $(d)))
	$(foreach hdr,$(hpp),$(shell cp $(hdr) $(patsubst src%,include%,$(hdr))))



	
.PHONY: clean

clean:
	$(RM) $(lib_objects)
	$(RM) $(test_objects)
	$(RM) *.a
	$(RM) $(APPNAME)
	$(RM) -fr include
	
	
	
list:
	@echo $(lib_objects)
	@echo $(test_objects)
	@echo $(headerDirs)
	
%.o : %.c
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(CPPINCLUDES) -c $< -o $@







