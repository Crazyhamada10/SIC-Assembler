/*
 * Operand.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: crazyhamada10
 */

#include "Operand.h"
#include "../Needs/AdvancedString.h"
#include "../Needs/StringHandling.h"
#include "../Needs/SymTable.h"

Operand::Operand(string operand) {
	this->operand = operand;
}

Operand::~Operand() {

}

bool Operand::isEmpty() {
    if (this->operand == "") return true;
    return false;
}

string Operand::getValue() {
	return this->operand;
}

bool Operand::checkByte() {
	if (this->operand.size() > 3 && this->operand[1] == '\'' && this->operand[this->operand.size() - 1] == '\'') {
		if (this->operand[0] == 'C' || (this->operand[0] == 'X'
				&& StringHandling::Instance()->isHex(this->operand.substr(2, this->operand.size() - 3))))
			return true;
	}
	return false;
}

int Operand::getLengthByte() {
	if (this->operand[0] == 'X') return (this->operand.size() - 2) / 2;
	return this->operand.size() - 3;
}

bool Operand::checkStart() {
	int st = 0;
	if (this->operand.size() > 2 && this->operand[0] == '0' && this->operand[1] == 'X') st += 2;
	if (StringHandling::Instance()->isHex(this->operand.substr(st)))
			return true;
	return false;
}

int Operand::getStartAddress() {
	return StringHandling::Instance()->convertHexTOInt(this->getHexStartAddress());
}

string Operand::getHexStartAddress() {
	AdvancedString::Instance()->toUpperCase(this->operand);
	int st = 0;
	if (this->operand.size() > 2 && this->operand[0] == '0' && this->operand[1] == 'X') st += 2;
	return this->operand.substr(st);
}

bool Operand::checkNumber() {
	return StringHandling::Instance()->isNumber(this->operand);
}

int Operand::getNumber() {
	return StringHandling::Instance()->convertStringTOInt(this->operand);
}

bool Operand::checkOper() {
    if (!AdvancedString::Instance()->isCommentEmpty(this->operand, 0)) {
        int len = this->operand.size();
        if (this->operand.size() > 2
            && this->operand[this->operand.size()-2] == ','
            && this->operand[this->operand.size()-1] == 'X') len -= 2;
        string temp = this->operand.substr(0, len);
        if (!AdvancedString::Instance()->containInvalidChars(temp)) {
            return true;
        }
	}
	return false;
}

bool Operand::checkOperPass2() {
	if (this->isEmpty()) return true;
    int len = this->operand.size();
    if (this->operand.size() > 2
        && this->operand[this->operand.size()-2] == ','
        && this->operand[this->operand.size()-1] == 'X') len -= 2;
    string temp = this->operand.substr(0, len);
    if (SymTable::Instance()->contain(temp)) return true;
	return false;
}

bool Operand::isIndexed() {
    if (this->operand.size() > 2
        && this->operand[this->operand.size()-2] == ','
        && this->operand[this->operand.size()-1] == 'X') return true;
    return false;
}

string Operand::getLabelAddress() {
	if (this->isEmpty()) return StringHandling::Instance()->convertTOHex(0, 4);
	if (!this->isIndexed()) return SymTable::Instance()->getAddress(this->operand);
	string ret = SymTable::Instance()->getAddress(this->operand.substr(0, this->operand.size() - 2));
	int add = StringHandling::Instance()->convertHexTOInt(ret);
	add += StringHandling::Instance()->convertHexTOInt("8000");
	return StringHandling::Instance()->convertTOHex(add , 4);
}

string Operand::getWord() {
	return StringHandling::Instance()->convertTOHex(this->getNumber(), 6);
}

string Operand::getByte() {
	if (this->operand[0] == 'X') return this->operand.substr(2, this->operand.size() - 3);
	string ans = "";
	for (int i = 2; i < (int)this->operand.size() - 1; i ++) {
		ans += StringHandling::Instance()->convertTOHex((int)this->operand[i], 2);
	}
	return ans;
}
