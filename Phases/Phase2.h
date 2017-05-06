/*
 * Phase2.h
 *
 *  Created on: May 1, 2017
 *      Author: crazyhamada10
 */

#ifndef PHASE2_H_
#define PHASE2_H_

#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Phase2 {

	static Phase2* instance;

public:
	static Phase2* Instance();
	static void Release();
	bool run(ifstream& input, ofstream& output, vector<pair<string, string> >& addressObj);

private:
	Phase2();
	~Phase2();
};




#endif /* PHASE2_H_ */
