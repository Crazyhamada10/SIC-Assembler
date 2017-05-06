/*
 * Errors.h
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#ifndef ERRORS_H_
#define ERRORS_H_

#include <string>
using namespace std;


class Errors {
    static bool flag;
public:
	static void fileReadingError();
	static string LabelDefinition(string label);
	static string unknownOpcode(string opcode);
	static string undefinedSymbol(string label);
	static void unknownLineFormat();
	static string unknownOperand();
	static bool getFlag();
	static string memoryOut();
private:
	Errors();
	virtual ~Errors();
};

#endif /* ERRORS_H_ */
