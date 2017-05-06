/*
 * StringHandling.h
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#ifndef STRINGHANDLING_H_
#define STRINGHANDLING_H_

#include <string>
using namespace std;

class StringHandling {

	static StringHandling* instance;

public:
	static StringHandling* Instance();
	static void Release();
	string convertTOHex(int x, int length);
	bool isHex(string x);
	bool isNumber(string x);
	int convertHexTOInt(string x);
	int convertStringTOInt(string x);
	string convertIntTOString(int x);
	string appendZeros(string x, int length);

private:
	StringHandling();
	virtual ~StringHandling();
};

#endif /* STRINGHANDLING_H_ */
