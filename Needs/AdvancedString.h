/*
 * AdvancedString.h
 *
 *  Created on: Apr 28, 2017
 *      Author: crazyhamada10
 */

#ifndef ADVANCEDSTRING_H_
#define ADVANCEDSTRING_H_

#include <string>
#include <vector>
using namespace std;

class AdvancedString {

	static AdvancedString* instance;

public:
	static AdvancedString* Instance();
	static void Release();
	bool containInvalidChars (string& line);
	void trim(string& party);
	bool isCommentEmpty (string& party, int ind);
	void toLowerCase(string& party);
	void toUpperCase(string& party);
	vector<string> splitBySpaces(string& party);

private:
	AdvancedString();
	virtual ~AdvancedString();
};

#endif /* ADVANCEDSTRING_H_ */
