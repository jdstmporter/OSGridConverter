//============================================================================
// Name        : CeoCoordinatesCPP.cpp
// Author      : JP Embedded Solutions Limited
// Version     :
// Copyright   : Copyright  2017 JP Embedded Solutions Limited
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <coordinates/Cartesian.hpp>
using namespace std;

int main() {
	auto c=coordinates::Cartesian(1.0,2.0,3.0);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
