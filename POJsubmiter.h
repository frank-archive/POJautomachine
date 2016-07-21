#include<string>
#include"Socket.h"
#include"base64.h"
#include"StringMatcher.h"
using namespace std;
// private property
//lab function
string JSESSIONID="F9482E32A6ECEAC2EA1867E91464BBE9";//clearly= =
extern string username, password;
string *Scanner;//used for Scanning JSESSIONID
void login() {
	PostDataWithJSESSIONID(JSESSIONID,"user_id1="+username+"&password1="+password+"&B1=login&url=%2F",(string)"/login",(string)"poj.org");
}
void SubmitOnPOJ(string &code,string &pID) {
	login();
}