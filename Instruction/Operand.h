/*
 * Operand.h
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#ifndef OPERAND_H_
#define OPERAND_H_

#include <string>
using namespace std;

class Operand {

	string operand;

public:
	Operand(string operand);
	virtual ~Operand();
	bool isEmpty();
	int getNumber();
	int getLengthByte();
	string getValue();
	bool checkByte();
	bool checkStart();
	int getStartAddress();
	string getHexStartAddress();
	bool checkNumber();
	bool checkOper();
	bool isIndexed();
	bool checkOperPass2();
	string getLabelAddress();
	string getWord();
	string getByte();
};

#endif /* OPERAND_H_ */
