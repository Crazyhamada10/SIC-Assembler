/*
 * SymTable.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: crazyhamada10
 */

#include "SymTable.h"
#include "OpTable.h"
#include <cstdlib>

SymTable* SymTable::instance = NULL;

SymTable::SymTable() {

}

SymTable::~SymTable() {

}

SymTable* SymTable::Instance() {
	if (instance == NULL) {
		instance = new SymTable();
	}
	return instance;
}

void SymTable::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}

bool SymTable::canBeAdded(string key) {
	if (!this->contain(key)
		&& !OpTable::Instance()->contain(key)
		&& !OpTable::Instance()->isMenomic(key)) {
		return true;
	}
	return false;
}

bool SymTable::contain(string key) {
	if (this->symTable.find(key) == this->symTable.end()) return false;
	return true;
}

string SymTable::getAddress(string key) {
	return this->symTable[key];
}

void SymTable::add(Label* label) {
	this->symTable[label->getSymbol()] = label->getAddress();
}
