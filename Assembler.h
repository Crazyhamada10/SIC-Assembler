/*
 * Assembler.h
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <string>
#include <vector>
using namespace std;

class Assembler {

	static Assembler* instance;
	static string extensions [];

public:
	bool run(string inputFolderPath, string fileName);
	static Assembler* Instance();
	static void Release();

private:
	Assembler();
	virtual ~Assembler();
	bool pass1(string inputFolderPath, string fileName, string& progName, int& progLen, int& startAddress);
	bool pass2(string inputFolderPath, string fileName, vector<pair<string, string> >& addressObj);
	void objectCodeWriter(string inputFolderPath, string fileName, string progName, int progLen, int startAddress, vector<pair<string, string> >& addressObj);
};

#endif /* ASSEMBLER_H_ */
