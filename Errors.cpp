/*
 * Errors.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#include "Errors.h"

bool Errors::flag = false;

string Errors::undefinedSymbol(string label) {
	flag = true;
	return  ("***Error::Unknown Label: (" + label + ")\n");
}

void Errors::fileReadingError() {
    flag = true;
	throw string("***Error::Can't read file\n");
}

void Errors::unknownLineFormat() {
	flag = true;
	throw string("***Error::Unknown Line Format\n");
}

string Errors::LabelDefinition(string label) {
	flag = true;
	return ("***Error::Label Definition: (" + label + ")\n");
}

string Errors::unknownOpcode(string opcode) {
	flag = true;
    return ("***Error::Unknown Opcode: (" + opcode + ")\n");
}

string Errors::unknownOperand () {
	flag = true;
	return ("***Error::Unknown Operand\n");
}

string Errors::memoryOut(){
	flag = true;
	return ("***Error::Pass memory range");
}

bool Errors::getFlag() {
    return Errors::flag;
}
