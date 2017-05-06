/*
 * ObjectCodeWriter.cpp
 *
 *  Created on: May 4, 2017
 *      Author: crazyhamada10
 */

#include "ObjectCodeWriter.h"
#include "../Errors.h"
#include "../Needs/StringHandling.h"
#include <cstdlib>

ObjectCodeWriter* ObjectCodeWriter::instance = NULL;

ObjectCodeWriter::ObjectCodeWriter() {

}

ObjectCodeWriter::~ObjectCodeWriter() {

}

ObjectCodeWriter* ObjectCodeWriter::Instance() {
	if (instance == NULL) {
		instance = new ObjectCodeWriter();
	}
	return instance;
}

void ObjectCodeWriter::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}

string getSeparator() {
	return "^";
}

string getHeader(string progName, int progLen, int startAddress) {
    progName = progName.substr(0, 7);
	return 'H' + getSeparator()
			+ progName.append(7 - progName.size(), ' ') + getSeparator()
			+ StringHandling::Instance()->convertTOHex(startAddress, 6) + getSeparator()
			+ StringHandling::Instance()->convertTOHex(progLen, 6) + '\n';
}

string getEnd(int startAddress) {
	return 'E' + getSeparator()
			+ StringHandling::Instance()->convertTOHex(startAddress, 6) + '\n';
}


string getAddress(int& ind, bool& writing, vector<pair<string, string> >& addressObj) {
	while (ind < (int)addressObj.size() && addressObj[ind].second == "") {
		ind ++;
	}
	if (ind == (int)addressObj.size()) {
		writing = false;
		return "";
	} else return StringHandling::Instance()->appendZeros(addressObj[ind].first, 6);
}

string getLength(int ind, int& rep, vector<pair<string, string> >& addressObj) {
	int length = addressObj[ind++].second.size(); rep++;
	while (ind < (int)addressObj.size() &&  addressObj[ind].second != "" && (length + addressObj[ind].second.size()) <= 60) {
		length += addressObj[ind].second.size();
		rep ++;
		ind ++;
	}
	return StringHandling::Instance()->convertTOHex(length/2, 2);
}

string getObj(int& ind, int rep, vector<pair<string, string> >& addressObj) {
	string ret = "";
	while (rep > 0) {
		ret += getSeparator() + addressObj[ind].second;
		ind ++;
		rep--;
	}
	return ret;
}

string getNextText(int& ind, bool& writing, vector<pair<string, string> >& addressObj) {
	int rep = 0;
	string ret = 'T' + getSeparator();
	ret += getAddress(ind, writing, addressObj) + getSeparator();
	if (writing) {
		ret += getLength(ind, rep, addressObj);
		ret += getObj(ind, rep, addressObj) + '\n';
		return ret;
	} return "";
}

void ObjectCodeWriter::run(ofstream& output, string progName, int progLen, int startAddress, vector<pair<string, string> >& addressObj) {
	output << getHeader(progName, progLen, startAddress);
	int ind = 0; bool writing = true;
	string temp = getNextText(ind, writing, addressObj);
	while (writing) {
		output << temp;
		temp = getNextText(ind, writing, addressObj);
	}
	output << getEnd(startAddress);
}
