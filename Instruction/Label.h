/*
 * Label.h
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#ifndef LABEL_H_
#define LABEL_H_

#include <string>
using namespace std;

class Label {
	string symbol;
	int address;

public:
	Label(string label);
	Label(string label, string address);
	virtual ~Label();
	bool isEmpty();
	void setAddress(int locCounter);
	bool save();
	string getSymbol();
	string getAddress();

};

#endif /* LABEL_H_ */
