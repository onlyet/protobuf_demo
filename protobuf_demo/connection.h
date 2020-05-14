//#include <cstdlib>
//#include <winsock2.h>
//#include <string>
//
//#include "conn_exception.h"
//
//using std::string;
//
//#ifndef	INADDR_NONE
//#define	INADDR_NONE	0xffffffff
//#endif
//
//#ifndef SD_RECEIVE
//#define SD_RECEIVE 0x00
//#define SD_SEND 0x01
//#define SD_BOTH 0x02
//#endif
//
//#define CONN_EXCEPTION 1
//
//#define PASSIVE_SOCK 1
//#define CONNECT_SOCK 2
//
//#define DEFAULT_QLEN 50
//
//typedef int SOCKET_TYPE;
//
///********************************************************************
//	created:	2016/02/15
//	created:	15:2:2016   15:35
//	filename: 	D:\tk\FtpClientDemo\FtpClientDemo\connection.h
//	file path:	D:\tk\FtpClientDemo\FtpClientDemo
//	file base:	connection
//	file ext:	h
//	author:		Chengzj
//	
//	purpose:	socket连接服务器
//*********************************************************************/
//
//class Connection
//{
//public:
//	Connection()
//	{
//		sock = INVALID_SOCKET;
//		sock_type = 0;
//		qlen = DEFAULT_QLEN;
//		host = "localhost";
//		service = "service";
//		protocal_type = "tcp";
//		portbase = 0;
//	}
//
//	~Connection()
//	{
//		shutdown(sock, SD_BOTH);
//		closesocket(sock);
//	}
//	
//	bool makeConnect(const string &host, const string &service, const string &protocal);
//	bool makeConnect()
//	{
//		return makeConnect(host, service, protocal_type);
//	}
//	
//	bool makePassive(const string &service, const string &transport, const int qlen);
//	bool makePassive()
//	{
//		return makePassive(service, protocal_type, qlen);
//	}
//	
//	string getProtocal(){ return protocal_type; }
//	
//	SOCKET_TYPE getSocketType(){ return sock_type; }
//	
//	SOCKET getSocket(){	return sock; }
//
//	string getHost(){ return host; }
//	string getService(){ return service; }
//	string getPort(){ return service; }
//	int getQueueLength(){ return qlen; }
//
//protected:
//
//private:
//	SOCKET passivesock(const string &service, const string &transport, const int qlen);
//	SOCKET connectsock(const string &host, const string &service, const string &transport );
//
//private:
//	SOCKET sock;
//	SOCKET_TYPE sock_type;
//	string protocal_type;
//	string host;
//	string service;
//	int qlen;
//	u_short	portbase;
//};
//
//SOCKET Connection::passivesock(const string &serv, const string &tp, const int qlen)
//{
//	this->service=serv;
//	this->protocal_type=tp;
//	this->qlen=qlen;
//
//	const char *service=serv.data();
//	const char *transport=tp.data();
//
//	struct servent	*pse;
//	struct protoent *ppe;
//	struct sockaddr_in sin;
//	SOCKET s;
//	int type;	/* socket 类型 (SOCK_STREAM, SOCK_DGRAM)*/
//
//	memset(&sin, 0, sizeof(sin));
//	sin.sin_family = AF_INET;
//	sin.sin_addr.s_addr = INADDR_ANY;
//	
//	// 映射服务器名称和端口号 
//	if ( pse = getservbyname(service, transport) ) sin.sin_port = htons(ntohs((u_short)pse->s_port) + portbase);
//	else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 ) throw (ConnException(1,"can't get service entry ",GetLastError())); 
//	
//	if ( (ppe = getprotobyname(transport)) == 0) throw (ConnException(1,"can't get protocol entry ",GetLastError())); 
//	
//	if (strcmp(transport, "udp") == 0) type = SOCK_DGRAM;
//	else type = SOCK_STREAM;
//	
//	s = socket(PF_INET, type, ppe->p_proto);
//	if (s == INVALID_SOCKET)
//		throw (ConnException(1,"can't create socket ",GetLastError())); 
//		
//	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
//		throw (ConnException(1,"can't bind to port ",GetLastError())); 
//	if (type == SOCK_STREAM && listen(s, qlen) == SOCKET_ERROR)
//		throw (ConnException(1,"can't listen port ",GetLastError())); 
//	return s;
//}
//
//SOCKET Connection::connectsock(const string &h, const string &serv, const string &tp)
//{
//	this->host=h;
//	this->service=serv;
//	this->protocal_type=tp;
//
//	const char *host=h.data();
//	const char *service=serv.data();
//	const char *transport=tp.data();
//
//	struct hostent	*phe;
//	struct servent	*pse;
//	struct protoent *ppe;
//	struct sockaddr_in sin;
//	SOCKET s;
//	int type;
//
//
//	memset(&sin, 0, sizeof(sin));
//	sin.sin_family = AF_INET;
//	
//	if ( pse = getservbyname(service, transport) )
//		sin.sin_port = pse->s_port;
//	else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 )
//		throw (ConnException(1,"can't get service entry ",GetLastError())); 
//	
//	if ( phe = gethostbyname(host) )
//		memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
//	else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
//		throw (ConnException(1,"can't get host entry",GetLastError()));
//	
//	if ( (ppe = getprotobyname(transport)) == 0)
//		throw (ConnException(1,"can't get protocol entry ",GetLastError())); 
//		
//	if (strcmp(transport, "udp") == 0)
//		type = SOCK_DGRAM;
//	else
//		type = SOCK_STREAM;
//		
//	s = socket(PF_INET, type, ppe->p_proto);
//	if (s == INVALID_SOCKET)
//		throw (ConnException(1,"can't create socket ",GetLastError())); 
//		
//	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
//		throw (ConnException(1,"can't connect to server ",GetLastError())); 
//	return s;
//}
//bool Connection::makePassive(const string &service, const string &transport, const int qlen)
//{
//	try
//	{
//		sock = passivesock(service, transport, qlen);
//	}
//	catch(ConnException e)
//	{
//		if(e.m_nExc) throw e;
//		sock = INVALID_SOCKET;
//		return false;
//	}
//	return true;
//}
//
//bool Connection::makeConnect(const string &host, const string &service, const string &protocal){
//	try
//	{
//		sock = connectsock(host, service, protocal);
//	}
//	catch(ConnException e)
//	{
//		if(e.m_nExc) throw e;
//		sock = INVALID_SOCKET;
//		return false;
//	}
//	return true;
//}