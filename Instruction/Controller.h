/*
 * Controller.h
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Instruction.h"
#include <string>
using namespace std;

class Controller {
	static Controller* instance;
	Instruction* instruction;

public:
	static Controller* Instance();
	static void Release();
	Instruction* getInstruction(string line);
	Instruction* reGetInstruction(string line);

private:
	Controller();
	virtual ~Controller();
};

#endif /* CONTROLLER_H_ */
