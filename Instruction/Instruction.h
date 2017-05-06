/*
 * Instruction.h
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "Label.h"
#include "Operand.h"
#include "Operation.h"
#include <string>
using namespace std;

class Instruction {
public:
	Instruction(Label* label, Operation* operation, Operand* operand);
	virtual ~Instruction();
	bool hasLabel();
	bool hasOperand();
	Label* getLabel();
	Operation* getOperation();
	Operand* getOperand();
	void setAddress(int locCounter);
	bool saveLabel();
	string generateOpcode();
	string getOutputLine();
	string getObjectOutputLine();
private:
	Label* label;
	Operation* operation;
	Operand* operand;
};

#endif /* INSTRUCTION_H_ */
