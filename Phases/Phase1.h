/*
 * Phase1.h
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#ifndef PHASE1_H_
#define PHASE1_H_

#include <fstream>
#include <string>
using namespace std;

class Phase1 {

	static Phase1* instance;

public:
	static Phase1* Instance();
	static void Release();
	bool run(ifstream& input, ofstream& output, string& progName, int& progLen, int& startAddress);

private:
	Phase1();
	~Phase1();
};

#endif /* PHASE1_H_ */
