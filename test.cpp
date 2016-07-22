//#include<iostream>
//#include<Windows.h>
//using namespace std;
//int main() {
//	char color = '0'; char font = '0';
//	system("mode con cols=9001 lines=177");
//	while (1) {
//		string a = (string)"color " +color+++font;
//		system(a.c_str());
//		if (color>'9')color = '0';
//		Sleep(200);
//	}
//}
#import "C:/Program Files/Common Files/System/ado/msado15.dll"\no_namespace rename("EOF", "EndOfFile")
#include <iostream>
#include <iomanip>//for setw()
using namespace std;
class STU
{
public:
	char snum[10]; //学号 
	char sname[10]; //姓名 
	char ssex[2]; //姓别 
	long sage; //年龄 
	char smajor[20]; //专业 
public:
	STU() {}
	~STU() {}
};

int main()
{
	STU student;
	::CoInitialize(NULL); // 初始化OLE/COM库环境 ，为访问ADO接口做准备

	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");

	_bstr_t bstrSQL("select * from stu_info"); //查询语句 
	char * query_cmd = "DELETE FROM stu_info WHERE sname = '本拉登'";

	try
	{
		// 创建Connection对象
		m_pConnection.CreateInstance("ADODB.Connection");
		// 设置连接字符串，必须是BSTR型或者_bstr_t类型
		_bstr_t strConnect = "Provider=SQLOLEDB;Server=(local);Database=student; uid=sa; pwd=123;";
		//若数据库在网络上则Server为形如(192.168.1.5,3340)
		//用户sa和密码123只是针对我的库 
		m_pConnection ->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
			cerr<<"Lind data ERROR!\n";
		// 创建记录集对象
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// 取得表中的记录
		m_pRecordset - >Open(bstrSQL, m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText);

		_variant_t vsnum, vsname, vsage, vssex, vsmajor; //对应库中的snum,sname,sage,ssex,smajor
		cout<< "学号 姓名 年龄 姓别 专业";
		cout<< "\n----------------------------------------------------------------\n";

		while (!m_pRecordset ->EndOfFile)
		{
			vsnum = m_pRecordset ->GetCollect(_variant_t((long)0));//这儿给字段编号和字段名都可以 
			vsname = m_pRecordset ->GetCollect("sname");
			vsage = m_pRecordset ->GetCollect("sage");
			vssex = m_pRecordset ->GetCollect("ssex");
			vsmajor = m_pRecordset ->GetCollect("smajor");
			if (vsnum.vt != VT_NULL && vsname.vt != VT_NULL && vsage.vt != VT_NULL
				&& vssex.vt != VT_NULL && vsmajor.vt != VT_NULL)
			{
				cout.setf(ios::left);
				cout << setw(14)<<(char*)(_bstr_t)vsnum;
				cout << setw(14)<<(char*)(_bstr_t)vsname;
				cout << setw(8)<< vsage.lVal;
				cout << setw(8)<<(char*)(_bstr_t)vssex;
				cout<<setw(20)<<(char*)(_bstr_t)vsmajor;
				cout.unsetf(ios::left);
				cout<< endl;
			}
			m_pRecordset - >MoveNext(); ///移到下一条记录
		}
		cout << "\n----------------------------------------------------------------\n";
		cout << "\n请输入你要添加的学生信息\n";
		cout << "学号:";
		cin >> student.snum;
		cout<< "\n姓名:";
		cin >> student.sname;
		cout<< "\n年龄:";
		cin >> student.sage;
		cout<< "\n姓别:";
		cin >> student.ssex;
		cout<< "\n专业:";
		cin >> student.smajor;
		m_pRecordset - >MoveFirst(); //移动到第一条记录
		m_pRecordset - >AddNew(); ///添加新记录
		m_pRecordset - >PutCollect("snum", _variant_t(student.snum));
		m_pRecordset - >PutCollect("sname", _variant_t(student.sname));
		m_pRecordset - >PutCollect("sage", _variant_t(student.sage));
		m_pRecordset - >PutCollect("ssex", _variant_t(student.ssex));
		m_pRecordset - >PutCollect("smajor", _variant_t(student.smajor));
		m_pRecordset - >Update();

		m_pConnection - >Execute(query_cmd, NULL, 1); //用Execute执行sql语句来删除
		m_pRecordset - >Close(); // 关闭记录集
	}

	// 捕捉异常
	catch (_com_error e)
	{
		// 显示错误信息
		cerr<< "\nERROR:"<<(char*)e.Description();//抛出异常
	}
	if (m_pConnection - >State)
		m_pConnection - >Close();

	::CoUninitialize();

	return 0;
}