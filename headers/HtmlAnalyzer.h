#pragma once
#include<cstring>
#include<string>
#include<queue>
#include"core\StringMatcher.h"
using namespace std;
queue<string> *temp1;
string temp2;
queue<string> *getBlogURL(string &page, string pat) {
	//解析搜索引擎结果页
	temp1 = new queue<string>;
	temp2 = "";
	string pattern = pat;
	int pos;
	while ((pos = match(page, pattern)) != -1) {
		int scout = pos;
		while (page[scout] != 34) { scout++; }
		temp2 = page.substr(pos, scout - pos);
		temp1->push(temp2);
		page = page.substr(scout + 5);
	}
	return temp1;
}

#include"core\Socket.h"
#define page code
int stack = 0;
void ReplaceSpecialCharacters(string &Page,char Code[0x7ffffff]) {
	int resLen = 0;
	for (int i = 0; i < Page.length() - 1; i++) {//big loop
	HTMLC:;
		if (i + 1 >= Page.length())break;
		if (Page[i] == '<')
			if (Page[i + 1] == '/')
				if (Page[i + 2] == 't' || Page[i + 2] == 'p')
					if (Page[i + 3] == 'e' || Page[i + 3] == 'r')
						if (Page[i + 4] == 't' || Page[i + 4] == 'e')
							break;
		if(Page[i]=='/')
			switch (Page[i + 1]) {
			case '/':
				while (Page[i] != '\n') {
					i++;
					if (i >= Page.length())return;
				}
				break;
			case '*':
				SC:;
					i++;
					while (Page[i] != '*') {
						i++;
						if (i >= Page.length())return;
					}
					if (Page[i + 1] != '/')goto SC;
					else i += 2;
				break;
			case 'n':
				Code[resLen++] = '\\';
				Code[resLen++] = 'n';
				i += 2;
				break;
			}
		if (Page[i] == '<') {
			stack++;
			while (stack != 0) {
				i++;
				if (i + 1 >= Page.length())break;
				if (Page[i] == '<')stack++;
				if (Page[i] == '>')stack--;
			}
			i++;
			goto HTMLC;
		}
		if (Page[i] == '&') {
			switch (Page[i + 1]) {
			case 'a':
				if (Page[i + 2] == 'm'&&Page[i + 3] == 'p')
					if (Page[i + 4] == ';') {
						Code[resLen++] = '&';
						i += 5;
						goto HTMLC;
					}
			case 'q':
				if (Page[i + 2] == 'u'&&Page[i + 3] == 'o')
					if (Page[i + 4] == 't'&&Page[i + 5] == ';') {
						Code[resLen++] = '"';
						i += 6;
						goto HTMLC;
					}
			case 'l':
				if (Page[i + 2] == 't'&&Page[i + 3] == ';') {
					Code[resLen++] = '<';
					i += 4;
					goto HTMLC;
				}
			case 'g':
				if (Page[i + 2] == 't'&&Page[i + 3] == ';') {
					Code[resLen++] = '>';
					i += 4;
					goto HTMLC;
				}
			case 'n':
				if (Page[i + 2] == 'b'&&Page[i + 3] == 's')
					if (Page[i + 4] == 'p'&&Page[i + 5] == ';') {
						Code[resLen++] = ' ';
						i += 6;
						goto HTMLC;
					}
			case '#':
				if (Page[i + 2] == '4'&&Page[i + 3] == '3'&&Page[i + 4] == ';') {
					Code[resLen++] = '+';
					i += 5;
					goto HTMLC;
				}
				else if (Page[i + 2] == '3'&&Page[i + 3] == '9'&&Page[i + 4] == ';') {
					Code[resLen++] = '\'';
					i += 5;
					goto HTMLC;
				}
			}
		}
		else Code[resLen++] = Page[i];//default
	}//big loop end
	//Page = Page.substr(0, resLen);
}
class CodeFetcher {
	queue<string> *jobs;
	string *code;
	string host, detail;
	string PlainURL;
	char CodeBuffer[0x7ffffff];
	bool split(string &URL) {
		host = ""; detail = "";

		int scout = 0;
		while (URL[scout] != '/')scout++;

		detail = URL.substr(scout);
		host = URL.substr(0, scout);
		return true;
	}
	void getCodePage() {
		PlainURL = "";
		PlainURL = jobs->front();
		split(PlainURL);
		page = getPage(host, detail);
	}
	bool ExtractFromPage() {
		int pos = match(*page, (string)"#include");
		if (pos >= page->length())return false;
		*page = page->substr(pos);
		ReplaceSpecialCharacters(*page,CodeBuffer);
		return true;
	}
public:
	CodeFetcher(queue<string> *init) {
		jobs = init;
	}
	bool empty() { return jobs->empty(); }
	char *front() {
		memset(CodeBuffer, 0, sizeof(CodeBuffer));

	repop:;
		if (jobs->empty())return "none";
		code = new string;
		getCodePage();
		if (!ExtractFromPage()) {
			jobs->pop();
			goto repop;
		}
		return CodeBuffer;
	}
	void pop() {
		if(!jobs->empty())jobs->pop();
	}
};