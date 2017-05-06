/*
 * Controller.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#include "Controller.h"
#include "Label.h"
#include "Operand.h"
#include "Operation.h"
#include "../Needs/AdvancedString.h"
#include "../Errors.h"
#include <cstdlib>
#include <vector>

Controller* Controller::instance = NULL;

Controller::Controller() {
	this->instruction = NULL;
}

Controller::~Controller() {

}

Controller* Controller::Instance() {
	if (instance == NULL) {
		instance = new Controller();
	}
	return instance;
}

void Controller::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}

void spliter (string& line, string& labelStr, string& operationStr, string& operandStr) {
	vector <string> parts = AdvancedString::Instance()->splitBySpaces(line);
	switch (parts.size()) {
		case 1:
			labelStr = operandStr = "";
			operationStr = parts[0];
			break;
		case 2:
			labelStr = "";
			operationStr = parts[0];
			operandStr = parts[1];
			break;
		case 3:
			labelStr = parts[0];
			operationStr = parts[1];
			operandStr = parts[2];
			break;
		default:
			Errors::unknownLineFormat();
		}
}

void secondSpliter (string& line, string& labelStr, string& operationStr, string& operandStr, string& address) {
	vector <string> parts = AdvancedString::Instance()->splitBySpaces(line);
	switch (parts.size()) {
		case 2:
			labelStr = operandStr = "";
			address = parts[0];
			operationStr = parts[1];
			break;
		case 3:
			labelStr = "";
			address = parts[0];
			operationStr = parts[1];
			operandStr = parts[2];
			break;
		case 4:
			address = parts[0];
			labelStr = parts[1];
			operationStr = parts[2];
			operandStr = parts[3];
			break;
		}
}

Instruction* Controller::getInstruction(string line) {
	this->instruction = NULL;
	AdvancedString* advance = AdvancedString::Instance();
	advance->trim(line);
	if (!advance->isCommentEmpty(line, 0)) {
		advance->toUpperCase(line);
		string labelStr, operationStr, operandStr;
		spliter(line, labelStr, operationStr, operandStr);
		Label* label = new Label(labelStr);
		Operation* operation = new Operation(operationStr);
		Operand* operand = new Operand(operandStr);
		this->instruction = new Instruction(label, operation, operand);
	}
	return this->instruction;
}


Instruction* Controller::reGetInstruction(string line) {
	this->instruction = NULL;
	AdvancedString* advance = AdvancedString::Instance();
	advance->trim(line);
	if (!advance->isCommentEmpty(line, 0)) {
		advance->toUpperCase(line);
		string labelStr, operationStr, operandStr, address;
		secondSpliter(line, labelStr, operationStr, operandStr, address);
		Label* label = new Label(labelStr, address);
		Operation* operation = new Operation(operationStr);
		Operand* operand = new Operand(operandStr);
		this->instruction = new Instruction(label, operation, operand);
	}
	return this->instruction;
}
