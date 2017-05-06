/*
 * Label.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#include "Label.h"
#include "../Needs/SymTable.h"
#include "../Needs/StringHandling.h"
#include "../Errors.h"

Label::Label(string label) {
	this->symbol = label;
	this->address = 0;
}

Label::Label(string label, string address) {
	this->symbol = label;
	this->address = StringHandling::Instance()->convertHexTOInt(address);
}

Label::~Label() {

}

void Label::setAddress(int locCounter) {
	this->address = locCounter;
}

bool Label::isEmpty() {
	for (int i=0; i<(int)this->symbol.size(); i++) {
		if (this->symbol[i] != ' ' && this->symbol[i] != '\t') return false;
	}
	return true;
}

string Label::getSymbol() {
	return this->symbol;
}

string Label::getAddress() {
	if (this->address < StringHandling::Instance()->convertHexTOInt("7FFF"))
		return StringHandling::Instance()->convertTOHex(this->address, 4);
	return Errors::memoryOut();
}

bool Label::save() {
	if (SymTable::Instance()->canBeAdded(this->symbol)) {
		SymTable::Instance()->add(this);
        return true;
	}
	return false;
}
