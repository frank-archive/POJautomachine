#pragma once
#include<time.h>
#include<string>
int CalenderTime;
char t[20];
using namespace std;
string CurrentTime() {
	time_t x = time(NULL);
	tm *b = localtime(&x);
	sprintf(t, "%d:%d:%d", b->tm_hour, b->tm_min, b->tm_sec);
	return t;
}