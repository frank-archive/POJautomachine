#pragma once
#include<cstring>
#include"core\StringMatcher.h"
using namespace std;
class Counter {
	int count;
public:
	Counter() {
		count = 0;
	}
	void push() { count++; }
	void pop() { count--; }
	bool empty() { return !count; }
};
bool examine(string &code){//true for good code
	Counter count–°¿®∫≈, count¥Û¿®∫≈;
	for (int i = 0; i < code.length(); i++) {
		switch (code[i]) {
		case '(':
			count–°¿®∫≈.push();
			break;
		case ')':
			count–°¿®∫≈.pop();
			break;
		case '{':
			count¥Û¿®∫≈.push();
			break;
		case '}':
			count¥Û¿®∫≈.pop();
			break;
		}
	}
	if (!count¥Û¿®∫≈.empty())return false;
	if (!count–°¿®∫≈.empty())return false;
	return true;
}