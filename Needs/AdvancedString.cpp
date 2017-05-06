/*
 * AdvancedString.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: crazyhamada10
 */

#include "AdvancedString.h"
#include <cstdlib>

AdvancedString* AdvancedString::instance = NULL;

AdvancedString::AdvancedString() {
}

AdvancedString::~AdvancedString() {

}

AdvancedString* AdvancedString::Instance() {
	if (instance == NULL) {
		instance = new AdvancedString();
	}
	return instance;
}

void AdvancedString::Release() {
    if (instance) {
        delete instance;
    }
    instance = NULL;
}

bool AdvancedString::containInvalidChars (string& line) {
    for (int i=0; i<(int)line.size(); i++) {
        if (!((line[i] >= '0' && line[i] <= '9')
            || (line[i] >= 'a' && line[i] <= 'z')
            || (line[i] >= 'A' && line[i] <= 'Z'))) return true;
    }
    return false;
}

void AdvancedString::trim(string& line) {
    int i = line.size();
    while (i > 0 && (line[i-1] == ' ' || line[i] == '\t')) {
        i--;
    }
    if (i > 0) {
    	line = line.substr(0, i);
    }
}

bool AdvancedString::isCommentEmpty (string& line, int ind) {
    while (ind < (int)line.size() && (line[ind] == ' ' || line[ind] == '\t')) {
        ind++;
    }
    if (ind == (int)line.size() || line[ind] == '.') return true;
    return false;
}

void AdvancedString::toLowerCase(string& line) {
	for (int i=0; i < (int)line.size(); i++) {
		if (line[i] >= 'A' && line [i] <= 'Z') {
			line[i] = (char)((int)line[i] - (int)'A' + (int)'a');
		}
	}
}

void AdvancedString::toUpperCase(string& line) {
	for (int i=0; i < (int)line.size(); i++) {
		if (line[i] >= 'a' && line [i] <= 'z') {
			line[i] = (char)((int)line[i] - (int)'a' + (int)'A');
		}
	}
}

vector<string> AdvancedString::splitBySpaces(string& line) {
	vector <string> parts;
	for (int i=0; i < (int) line.size(); i++) {
		int pos = i;
	    while (i < (int) line.size() && !(line[i] == ' ' || line[i] == '\t')) {
	        i++;
	    }
	    if (pos < i) {
	    	parts.push_back(line.substr(pos, i-pos));
	    }
	}
	int num = parts.size() - 1;
	while (num > 0) {
		if (parts[num][0] != '.')
			break;
		num --;
	}
	vector <string> temp;
	for (int i=0; i<= num; i++) {
		temp.push_back(parts[i]);
	}
	parts.clear();
	return temp;
}
