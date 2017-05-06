/*
 * OpTable.cpp
 *
 *  Created on: Apr 25, 2017
 *      Author: crazyhamada10
 */

#include "OpTable.h"
#include "../Errors.h"
#include "StringHandling.h"
#include "AdvancedString.h"
#include <cstdlib>
#include <fstream>
#include <vector>

OpTable* OpTable::instance = NULL;

OpTable::OpTable() {
    this->opTable.clear();
	this->readTable();
}

OpTable::~OpTable() {

}

OpTable* OpTable::Instance() {
	if (instance == NULL) {
		instance = new OpTable();
	}
	return instance;
}

void OpTable::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}


string getHex(string op) {
	int temp = StringHandling::Instance()->convertStringTOInt(op);
	return StringHandling::Instance()->convertTOHex(temp, 2);
}

void OpTable::readTable() {
	ifstream stream("Attachments/SIC_OPCODE");
	if (!stream.is_open()) {
		Errors::fileReadingError();
	} else {
		string temp;
		vector<string> strings;
		while (getline(stream, temp, '\n')) {
			for (int i=0; i<(int)temp.size(); i++) {
				int pos = i;
				while (i < (int)temp.size() && temp.at(i) != ' ' && temp.at(i) != '\t') {
					i++;
				}
				if (i > pos) {
					strings.push_back(temp.substr(pos, i-pos));
				}
			}
			AdvancedString::Instance()->toUpperCase(strings[0]);
			this->opTable[strings[0]] = make_pair(getHex(strings[1]),
                                        StringHandling::Instance()->convertStringTOInt(strings[2]));
			strings.clear();
		}
	}
}

bool OpTable::contain(string key) {
	if (this->opTable.find(key) == this->opTable.end()) return false;
	return true;
}

string OpTable::getValue(string key) {
	return this->opTable[key].first;
}

int OpTable::getNumber(string key) {
	return this->opTable[key].second;
}

bool OpTable::isMenomic(string key) {
	if (key == "START" || key == "END"
		|| key == "WORD" || key == "RESW"
		|| key == "BYTE" || key == "RESB"
		|| key == "ORG" || key == "EQU") {
		return true;
	}
	return false;
}

