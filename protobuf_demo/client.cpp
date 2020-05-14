
#include <iostream>
#include <string>

#include "SocketManager.h"

using namespace std;

//int main(int argc, char *argv[])
//{      
//
//	//string host("localhost");
//	string host("192.168.2.236");
//	string service("8888");
//
//	SocketManager socketManager(host,service);
//	string message("我是郑高强啊");
//	char buf[10000];
//	socketManager.sendMessage(message.data(), "tcp");
//
//	int count = socketManager.receive(buf, 100);
//	if(count>0){
//		string resultString(buf);
//		cout<<count<<endl;
//		cout<<resultString<<endl;
//	}
//	return 0;	/* exit */
//}
