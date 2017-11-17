libdir=$(prefix)/lib
lib_LIBRARIES = libgeoconv.a
libgeoconv_a_SOURCES = Vector.cpp Matrix.cpp Datum.cpp Ellipsoid.cpp Helmert.cpp LatitudeLongitude.cpp OSGB36.cpp OSGrid.cpp Parser.cpp
libgeoconv_a_CXXFLAGS = -std=c++14 -O0  -g3 -Wall -fmessage-length=0

includedir=$(prefix)/include
include_HEADERS = geoconv.hpp algebra.hpp Cartesian.hpp Datum.hpp Ellipsoid.hpp Helmert.hpp LatitudeLongitude.hpp OSGB36.hpp OSGrid.hpp Parser.hpp

lib_LTLIBRARIES = libgeoconv.la
libgeoconv_la_SOURCES = Vector.cpp Matrix.cpp Datum.cpp Ellipsoid.cpp Helmert.cpp LatitudeLongitude.cpp OSGB36.cpp OSGrid.cpp Parser.cpp
libgeoconv_la_CXXFLAGS = -std=c++14 -O0  -g3 -Wall -fmessage-length=0
