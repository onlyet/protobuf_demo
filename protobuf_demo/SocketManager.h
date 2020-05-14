//
//#include <winsock2.h>
//
//#include <iostream>
//#include <string>
//#include "connection.h"
//
//using namespace std;
//
//#ifndef INVALID_SOCKET
//#define INVALID_SOCKET (SOCKET)(~0)
//#endif
//#ifndef SOCKET_ERROR
//#define SOCKET_ERROR -1
//#endif
//#ifndef SD_RECEIVE
//#define SD_RECEIVE 0x00
//#define SD_SEND 0x01
//#define SD_BOTH 0x02
//#endif
//
////user pre-compile identifiers
//#define WSVERS MAKEWORD(2, 0)	 //winsock version 2.0
//
//
//// Connection把Socket通信封装
//// 
///********************************************************************
//	created:	2016/02/15
//	created:	15:2:2016   16:34
//	author:		Chengzj
//	
//	purpose:	这个类负责发送和接受
//*********************************************************************/
//class SocketManager
//{
//private:
//	WSADATA m_wsadata;
//	string m_server;
//	string m_sPort;
//	SOCKET m_socket;
//	Connection m_conn;
//
//public:
//	SocketManager(string server, string port)
//	{
//		this->m_server = server;
//		this->m_sPort = port;
//		m_socket = INVALID_SOCKET;
//	}
//
//	~SocketManager()
//	{
//		try
//		{
//			shutdown(m_socket, SD_BOTH);
//			closesocket(m_socket);
//			WSACleanup();                            /* 卸载DLL */ 
//		}
//		catch(ConnException e)
//		{
//			cout<<e.m_sMsg<<" 错误号 "<<e.m_dErr<<endl;
//		}
//	}
//
//	// 发送数据
//	bool sendMessage(const char* message, const string& sServer);
//	bool sendMessage(const char* message, const string& sServer, int nMsg);
//	// 接收数据，在buf数据结尾自动加上/0，注意buf的大小要比len大1以上
//	int receive(char * buf, int len);
//};
//
//bool SocketManager::sendMessage(const char* message, const string& sServer)
//{
//	try
//	{
//		// 启动DLL 
//		if(WSAStartup(WSVERS, &m_wsadata) != 0)
//		{
//			return false;
//		}
//		m_conn.makeConnect(m_server, m_sPort, sServer);
//		m_socket = m_conn.getSocket();
//		
//		if(send(m_socket, message, strlen(message), 0)==SOCKET_ERROR)
//		{
//			return false;
//		}
//		return true;
//	}
//	catch(ConnException e)
//	{
//		cout<<e.m_sMsg<<" 错误号 "<<e.m_dErr<<endl;
//		return false;
//	}
//}
//
//bool SocketManager::sendMessage( const char* message, const string& sServer, int nMsg )
//{
//	try
//	{
//		// 启动DLL 
//		if(WSAStartup(WSVERS, &m_wsadata) != 0)
//		{
//			return false;
//		}
//		m_conn.makeConnect(m_server, m_sPort, sServer);
//		m_socket = m_conn.getSocket();
///*
//		if(send(m_socket, message, strlen(message), 0)==SOCKET_ERROR)
//		{
//			return false;
//		}*/
//		int pos = 0;
//		while(pos < nMsg)
//		{
//				int len=send(m_socket, message+pos, strlen(message),0);
//				if(len <= 0)
//				{
//					//perror("ERRPR");
//					 break;
//				}
//				pos+=4;
//				//pos+=len;
//				Sleep(5000);
//		}
//
//		return true;
//	}
//	catch(ConnException e)
//	{
//		cout<<e.m_sMsg<<" 错误号 "<<e.m_dErr<<endl;
//		return false;
//	}
//}
//
//
//int SocketManager::receive(char* buf, int len)
//{
//	try
//	{
//		int	charCount;	// 字符长度
//		if(m_socket==INVALID_SOCKET || 
//		   m_socket==SOCKET_ERROR) return -1;
//
//		charCount = recv(m_socket, buf, len, 0);
//		if( charCount!=SOCKET_ERROR && 
//			charCount>0) 
//		{
//			buf[charCount] = '\0';	// 确保字符末位为\0
//		}
//		return charCount;
//	}
//	catch(ConnException e)
//	{
//		cout<<"error in receive.."<<endl;
//		return -1;
//	}
//}