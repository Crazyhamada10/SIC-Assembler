/*
 * OpTable.h
 *
 *  Created on: Apr 25, 2017
 *      Author: crazyhamada10
 */

#ifndef OPTABLE_H_
#define OPTABLE_H_

#include<string>
#include <map>
using namespace std;

class OpTable {

static OpTable* instance;
map <string, pair<string, int> > opTable;

public:
	static OpTable* Instance();
	static void Release();
	bool contain(string key);
	bool isMenomic(string key);
	string getValue(string key);
	int getNumber(string key);

private:
	OpTable();
	virtual ~OpTable();
	void readTable();
};

#endif /* OPTABLE_H_ */
