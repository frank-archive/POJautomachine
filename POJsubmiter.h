#include<string>
#include"Socket.h"
#include"base64.h"
using namespace std;
// private property
//lab function

void SubmitOnPOJ(string &code,string &pID) {
	sendForm(base64_encode(code.c_str(),code.length()), pID);
}