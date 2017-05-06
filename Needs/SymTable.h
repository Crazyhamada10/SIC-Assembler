/*
 * SymTable.h
 *
 *  Created on: Apr 28, 2017
 *      Author: crazyhamada10
 */

#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include "../Instruction/Label.h"
#include<string>
#include <map>
using namespace std;

class SymTable {

	static SymTable* instance;
	map <string, string> symTable;

public:
	static SymTable* Instance();
	static void Release();
	bool contain(string key);
	string getAddress(string key);
	void add(Label* label);
	bool canBeAdded(string key);

private:
	SymTable();
	virtual ~SymTable();
};

#endif /* SYMTABLE_H_ */
