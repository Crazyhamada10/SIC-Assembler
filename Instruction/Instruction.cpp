/*
 * Instruction.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#include "Instruction.h"
#include "../Needs/StringHandling.h"

Instruction::Instruction(Label* label, Operation* operation, Operand* operand) {
	this->label = label;
	this->operation = operation;
	this->operand = operand;
}

Instruction::~Instruction() {
	delete this->label;
	delete this->operand;
	delete this->operation;
}

bool Instruction::hasLabel() {
	return !this->label->isEmpty();
}

bool Instruction::hasOperand() {
	return !this->operand->isEmpty();
}

Label* Instruction::getLabel() {
	return this->label;
}

Operation* Instruction::getOperation() {
	return this->operation;
}

Operand* Instruction::getOperand() {
	return this->operand;
}

void Instruction::setAddress(int locCounter) {
	this->label->setAddress(locCounter);
}

bool Instruction::saveLabel() {
	return this->label->save();
}

string Instruction::getOutputLine() {
	string ret =  this->label->getAddress() + '\t';
	ret += this->label->getSymbol() + '\t';
	ret += this->operation->getString() + '\t';
	ret += this->operand->getValue() + '\n';
	return ret;
}

string Instruction::generateOpcode() {
	if (this->operation->opTable()) {
		if (this->operand->checkOperPass2()) {
			return (this->operation->getObjectCode() + this->operand->getLabelAddress());
		} return (this->operation->getObjectCode() + StringHandling::Instance()->convertTOHex(0, 4));
	} else if (this->operation->isWord()) {
		return this->operand->getWord();
	} else if (this->operation->isByte()) {
		return this->operand->getByte();
	} return "";
}

string Instruction::getObjectOutputLine() {
	string ret =  this->label->getAddress() + '\t';
	ret += this->label->getSymbol() + '\t';
	ret += this->operation->getString() + '\t';
	ret += this->operand->getValue() + "\t\t";
	ret += this->generateOpcode() + '\n';
	return ret;
}
