/*
 * Operation.h
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#ifndef OPERATION_H_
#define OPERATION_H_

#include <string>
using namespace std;

class Operation {

	string operation;

public:
	Operation(string operation);
	virtual ~Operation();
	bool isStart();
	bool isEnd();
	bool opTable();
	bool noOperand();
	bool isWord();
	bool reservedWord();
	bool isByte();
	bool reservedByte();
	bool isORG();
	bool isEQU();
	string getString();
	string getObjectCode();
};

#endif /* OPERATION_H_ */
