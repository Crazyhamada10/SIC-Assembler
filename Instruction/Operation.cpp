/*
 * Operation.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#include "Operation.h"
#include "../Needs/OpTable.h"

Operation::Operation(string operation) {
	this->operation = operation;
}

Operation::~Operation() {

}

string Operation::getString() {
	return this->operation;
}

bool Operation::isStart() {
	if (this->operation == "START") return true;
	return false;
}

bool Operation::isEnd() {
	if (this->operation == "END") return true;
	return false;
}

bool Operation::opTable() {
	if (OpTable::Instance()->contain(this->operation)) return true;
	return false;
}

bool Operation::noOperand() {
	if (!OpTable::Instance()->getNumber(this->operation)) return true;
	return false;
}

bool Operation::isWord() {
	if (this->operation == "WORD") return true;
	return false;
}

bool Operation::reservedWord() {
	if (this->operation == "RESW") return true;
	return false;
}

bool Operation::isByte() {
	if (this->operation == "BYTE") return true;
	return false;
}

bool Operation::reservedByte() {
	if (this->operation == "RESB") return true;
	return false;
}

bool Operation::isORG() {
	if (this->operation == "ORG") return true;
	return false;
}

bool Operation::isEQU() {
	if (this->operation == "EQU") return true;
	return false;
}

string Operation::getObjectCode() {
	if (this->opTable()) {
		return OpTable::Instance()->getValue(this->operation);
	} return "";
}
