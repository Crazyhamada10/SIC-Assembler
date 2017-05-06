/*
 * Assembler.cpp
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#include "Assembler.h"
#include <cstdlib>
#include <fstream>
#include "Phases/Phase1.h"
#include "Phases/Phase2.h"
#include "Phases/ObjectCodeWriter.h"
#include "Errors.h"

Assembler* Assembler::instance = NULL;
string Assembler::extensions[] = {".asm", "_inter.txt", "_intermediate.txt", ".obj"};

Assembler::Assembler() {

}

Assembler::~Assembler() {

}

Assembler* Assembler::Instance() {
	if (instance == NULL) {
		instance = new Assembler();
	}
	return instance;
}

void Assembler::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}


bool Assembler::run(string inputFolderPath, string fileName) {
	string progName = ""; int progLen = 0, startAddress = 0;
	vector<pair<string, string> > addressObj;
	if (this->pass1(inputFolderPath, fileName, progName, progLen, startAddress)) {
		if (this->pass2(inputFolderPath, fileName, addressObj)) {
			this->objectCodeWriter(inputFolderPath, fileName, progName, progLen, startAddress, addressObj);
			return true;
		}
	}
	return false;
}

bool Assembler::pass1(string inputFolderPath, string fileName,
		string& progName, int& progLen, int& startAddress) {
	bool ans = false;
	ifstream input (inputFolderPath + fileName + extensions[0]);
	if (input.is_open()) {
		ofstream output (inputFolderPath + fileName + extensions[1]);
		ans = Phase1::Instance()->run(input, output, progName, progLen, startAddress);
		output.close();
	} else Errors::fileReadingError();
	input.close();
	return ans;
}


bool Assembler::pass2(string inputFolderPath, string fileName, vector<pair<string, string> >& addressObj) {
	bool ans = false;
	ifstream input (inputFolderPath + fileName + extensions[1]);
	ofstream output (inputFolderPath + fileName + extensions[2]);
	ans = Phase2::Instance()->run(input, output, addressObj);
	output.close();
	input.close();
	return ans;
}

void Assembler::objectCodeWriter(string inputFolderPath, string fileName,
		string progName, int progLen, int startAddress, vector<pair<string, string> >& addressObj) {
	ofstream output (inputFolderPath + fileName + extensions[3]);
	ObjectCodeWriter::Instance()->run(output, progName, progLen, startAddress, addressObj);
	output.close();
}
