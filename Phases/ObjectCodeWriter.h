/*
 * ObjectCodeWriter.h
 *
 *  Created on: May 4, 2017
 *      Author: crazyhamada10
 */

#ifndef OBJECTCODEWRITER_H_
#define OBJECTCODEWRITER_H_

#include <string>
#include <fstream>
#include <vector>
using namespace std;

class ObjectCodeWriter {

	static ObjectCodeWriter* instance;

public:
	static ObjectCodeWriter* Instance();
	static void Release();
	void run(ofstream& output, string progName, int progLen, int startAddress, vector<pair<string, string> >& addressObj);

private:
	ObjectCodeWriter();
	virtual ~ObjectCodeWriter();
};

#endif /* OBJECTCODEWRITER_H_ */
