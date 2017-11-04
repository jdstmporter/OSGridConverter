
check_PROGRAMS = tester0 tester1 tester2
tester0_LDADD = ../src/libgeoconv.a
tester0_CXXFLAGS = -std=c++14 -O0  -g3 -Wall -fmessage-length=0 -I ../src -D'TEST_INDEX=0'
tester0_SOURCES = main.cpp Tests.cpp TestBase.cpp Suite.cpp Generator.cpp


tester2_LDADD = ../src/libgeoconv.a
tester2_CXXFLAGS = -std=c++14 -O0  -g3 -Wall -fmessage-length=0 -I ../src -D'TEST_INDEX=2'
tester2_SOURCES = main.cpp Tests.cpp TestBase.cpp Suite.cpp Generator.cpp


tester1_LDADD = ../src/libgeoconv.a
tester1_CXXFLAGS = -std=c++14 -O0  -g3 -Wall -fmessage-length=0 -I ../src -D'TEST_INDEX=1'
tester1_SOURCES = main.cpp Tests.cpp TestBase.cpp Suite.cpp Generator.cpp

TESTS = tester0 tester1 tester2
