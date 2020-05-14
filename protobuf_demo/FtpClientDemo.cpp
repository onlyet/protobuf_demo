
//#include "stdafx.h"
#include "stdio.h"
#include "Winsock2.h"
#include "conio.h"
#include "stdlib.h"
#include <iostream>
#include "SocketManager.h"
#include "define.h"
#include "person.pb.h"
#include "User.pb.h"
#include "ShopBuy.pb.h"

#include <string>
#include <assert.h>
#include <stdint.h>

using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libprotobuf.lib")

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/coded_stream.h> 
#include <google/protobuf/stubs/common.h>
using namespace::google::protobuf::io;
#define BUFFER_SIZE 1024
int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;  
	WSADATA wsaData;  
	int err;  
	wVersionRequested = MAKEWORD(1,1);  

	err = WSAStartup( wVersionRequested, &wsaData);  
	if ( err != 0)  
	{  
		return 0;  
	}  
	if ( LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion != 1))  
	{  
		WSACleanup();  
		return 0;  
	}  

	SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);  

	SOCKADDR_IN addrSrv;  
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  
	// addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.0.128");
	addrSrv.sin_family = AF_INET;  
	addrSrv.sin_port = htons(9998);  

	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));  
	printf("Connect Successful...\n");  

	netty::User_Net net;
	net.set_userid("124");
	net.set_username("fadf");
	net.set_phone("124456");
	
	net.add_sex(1);
	net.add_sex(2);
	
	int len = net.ByteSize()+4;
	char *buffer = new char[len];
	google::protobuf::io::ArrayOutputStream arrayOut(buffer, len);
	google::protobuf::io::CodedOutputStream codedOut(&arrayOut);
	codedOut.WriteVarint32(net.ByteSize());
	net.SerializeToCodedStream(&codedOut);
	
	if(send(sockClient,buffer,len,0)<0)
	{
		printf("Send Failed\n");
		return -1;
	}
	
	printf("Send Successful...\n");  

	while(1)
	{
		char buf[BUFFER_SIZE+1];
		int bytes;
		if ((bytes = recv(sockClient, buf, BUFFER_SIZE, 0))==SOCKET_ERROR)
		{
			printf("data error");
			exit(-1);
		}
		
		netty::User_Net us;

		google::protobuf::io::ArrayInputStream array_in(buf, bytes);
		google::protobuf::io::CodedInputStream coded_in(&array_in);
		google::protobuf::uint32 size;
		coded_in.ReadVarint32(&size);
		google::protobuf::io::CodedInputStream::Limit msg_limit = coded_in.PushLimit( size );
		us.ParseFromCodedStream( &coded_in );
		coded_in.PopLimit(msg_limit);

		cout<<us.userid()<<endl;
		cout<<us.username()<<endl;
		cout<<us.phone()<<endl;
		cout<<us.sex(0)<<endl;
		cout<<us.sex(1)<<endl;
	}

	closesocket(sockClient);  
	WSACleanup();  

	system("pause");  
	return 0;  
}