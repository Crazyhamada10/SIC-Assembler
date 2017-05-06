/*
 * main.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#include "Assembler.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	try {
        if (Assembler::Instance()->run("/home/crazyhamada10/Desktop/testing/", "test12")) {
        	cout << "Done";
        } else cout << "Error";
	} catch (string& msg) {
		cout << msg ;
	} catch (...) {
		cout << "Exception";
	}
	return 0;
}


/*
SIC
SIC2
SIC-Example-spaces
SIC-Example-true3
SIC-Example-true-again3
SIC-test3'abii
SIC-test23'ba
SIC-test23'ba2
test12
*/
