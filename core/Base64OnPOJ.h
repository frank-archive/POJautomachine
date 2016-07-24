#pragma once
#include<string>
#include<float.h>
using namespace std;
char _keyStr[66] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
string UrlUTF8(const char * str){
	string tt = str;
	string dd;

	size_t len = tt.length();
	for (size_t i = 0; i<len; i++){
		if (isalnum((unsigned char)tt[i])){
			char tempbuff[2] = { 0 };
			sprintf(tempbuff, "%c", (unsigned char)tt[i]);
			dd.append(tempbuff);
		}
		else if (isspace((unsigned char)tt[i])){
			dd.append("+");
		}
		else{
			char tempbuff[4];
			sprintf(tempbuff, "%%%X%X", ((unsigned char)tt[i]) >> 4, ((unsigned char)tt[i]) % 16);
			dd.append(tempbuff);
		}

	}
	return dd;
}
string encode(string input) {
	string output = "";
	char chr1, chr2, chr3;int enc1, enc2, enc3, enc4;
	int i = 0;
	while (i < input.length()) {
		chr1 = input[i++];
		if (i < input.length())chr2 = input[i++]; else chr2 = 0;
		if (i < input.length())chr3 = input[i++]; else chr3 = 0;
		enc1 = chr1 >> 2;
		enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
		enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
		enc4 = chr3 & 63;
		if (_isnan(chr2)) {
			enc4 = 64; enc3 = 64;
		}
		else if (_isnan(chr3))
			enc4 = 64;
		output += _keyStr[enc1]; output += _keyStr[enc2]; output += _keyStr[enc3];output += _keyStr[enc4];
	}
	output = UrlUTF8(output.c_str());
	return output;
}