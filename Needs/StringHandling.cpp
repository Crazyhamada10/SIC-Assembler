/*
 * StringHandling.cpp
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#include "StringHandling.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>

StringHandling* StringHandling::instance = NULL;

StringHandling::StringHandling() {

}

StringHandling::~StringHandling() {

}

StringHandling* StringHandling::Instance() {
	if (instance == NULL) {
		instance = new StringHandling();
	}
	return instance;
}

void StringHandling::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}

string StringHandling::convertTOHex(int x, int length) {
	stringstream stream;
	stream << uppercase << setfill('0') << setw(length) << hex << (x);
	return stream.str();
}

bool StringHandling::isHex(string x) {
	for (int i=0; i<(int)x.size(); i++) {
		if (!((x[i] >= '0' && x[i] <= '9')
				|| (x[i] >= 'A' && x[i] <= 'F')
				|| (x[i] >= 'a' && x[i] <= 'f')))
			return false;
	}
	return true;
}

bool StringHandling::isNumber(string x) {
	for (int i=0; i<(int)x.size(); i++) {
		if (!(x[i] >= '0' && x[i] <= '9'))
			return false;
	}
	return true;
}

int StringHandling::convertHexTOInt(string x) {
	int ans;
	stringstream stream;
	stream << hex << (x);
	stream >> ans;
	return ans;
}

int StringHandling::convertStringTOInt(string x) {
	int ans;
	stringstream stream;
	stream.str(x);
	stream >> ans;
	return ans;
}

string StringHandling::convertIntTOString(int x) {
	stringstream stream;
	stream << (x);
	return stream.str();
}

string StringHandling::appendZeros(string x, int length) {
	stringstream stream;
	stream << setfill('0') << setw(length) << (x);
	return stream.str();
}
