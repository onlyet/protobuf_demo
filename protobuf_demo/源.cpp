#include <iostream>
#include <fstream>
#include <string>
#include "person.pb.h"

using namespace std;
using namespace tutorial;

int main(int argc, char* argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Person person;

	//将数据写到person.pb文件
	person.set_id(123456);
	person.set_name("Mark");
	person.set_email("mark@example.com");

	fstream out("person.pb", ios::out | ios::binary | ios::trunc);
	person.SerializeToOstream(&out);
	out.close();


	//从person.pb文件读取数据

	Person person_out;
	fstream in("person.pb", ios::in | ios::binary);
	if (!person_out.ParseFromIstream(&in)) {
		cerr << "Failed to parse person.pb." << endl;
		exit(1);
	}

	//cout << "ID: " << person_out.id() << endl;
	//cout << "name: " << person_out.name() << endl;
	//if (person_out.has_email()) {
	//	cout << "e-mail: " << person_out.email() << endl;
	//}


	PcbtEndExam endExam;
	endExam.set_ordernum(24);
	endExam.set_useridstring("abc9527");

	PcbtMsg pcbtMsg;
	string data = endExam.SerializeAsString();

	pcbtMsg.set_type("STUDENT_ENDEXAM");
	pcbtMsg.set_data(data);
	
	string req_msg = pcbtMsg.SerializeAsString();

	PcbtMsg pcbtMsg2;
	pcbtMsg2.ParseFromString(req_msg);
	cout << "type: " << pcbtMsg2.type() << endl;
	string data2 = pcbtMsg2.data();
	PcbtEndExam endExam2;
	endExam2.ParseFromString(data2);
	cout << "order: " << endExam2.ordernum() << ", id: " << endExam2.useridstring() << endl;
	//cout << "data: "


	ControlMsg cm;
	cm.set_type("STUDENT_ENDEXAM 2");
	PcbtEndExam* pee = cm.mutable_endexam();
	pee->set_ordernum(1);
	pee->set_useridstring("qwer");
	
	string newdata = cm.SerializeAsString();

	ControlMsg cm2;
	cm2.ParseFromString(newdata);
	cout << "type2: " << cm2.type() << endl;
	PcbtEndExam pee2 = cm2.endexam();
	cout << "order2: " << pee2.ordernum() << ", id2: " << pee2.useridstring() << endl;


	getchar();
	return 0;
}