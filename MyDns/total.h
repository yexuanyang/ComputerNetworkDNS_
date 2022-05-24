//����ͷ�ļ��͵����
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <time.h>
#include <fstream>
#include <stdbool.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

//��������
#define ID_TRANS_SIZE 32 /* The max size of ID_TRANS_TABLE*/
#define DNS_PORT 53
#define DNameMaxLen 129

//�궨��
#define BUFSIZE 1024

//�ṹ�嶨��
typedef struct {
	unsigned id : 16;      /* query identification number */
	unsigned qr : 1;       /* response flag */
	unsigned opcode : 4;   /* purpose of message */
	unsigned aa : 1;       /* authoritive answer */
	unsigned tc : 1;       /* truncated message */
	unsigned rd : 1;       /* recursion desired */
	unsigned rcode : 4;    /* response code */
	unsigned z : 3;        /* unused bits, must be ZERO */
	unsigned ra : 1;       /* recursion available */
	unsigned qdcount : 16; /* number of question entries */
	unsigned ancount : 16; /* number of answer entries */
	unsigned nscount : 16; /* number of authority entries */
	unsigned arcount : 16; /* number of resource entries */
} HEADER;

//�����ֶ�
typedef struct {
	char qname[DNameMaxLen]; //��ѯ����
	unsigned qtype : 16;  //��ѯ����
	unsigned qclass : 16; //��ѯ��
} QUESTION;
//
typedef struct {
	char name[DNameMaxLen]; //����
	unsigned RRtype : 16;  //����
	unsigned RRclass : 16; //��
	unsigned TTL : 32;     //����ʱ��
	unsigned dataLen : 16; //���ݳ���
	char *Rdata;
} RR;

typedef struct {
	HEADER header;       //DNS��ͷ
	QUESTION *questions; //����
	RR *AN;              //�ش�
	RR *NS;              //��Ȩ���ַ�����
	RR *AR;              //������Դ
} DNS_PACKET;

typedef struct DNIPList { //������и���
	char ip[16]; //IP��ַ �������޸� ip��ַ�ĸ�ʽ xxx.xxx.xxx.xxx 16���ֽ�Ӧ�ÿ���ʹ��
	char dn[DNameMaxLen]; //����
	int expire_time;   //����ʱ��
	DNIPList *nextPtr; //ָ����һ����ָ��
	int length;
} DNIPList;                //��׼��������Ҫ�в���ֵ��ͷ�ڵ�

typedef struct {
	unsigned short last_ID; /* The old id*/
	BOOL done;          /*Mark whether the request was analysed completely*/
	SOCKADDR_IN client; /*Requestor socket address*/
	char url[DNameMaxLen]; /*URL*/
	int expire_time;    /*The time to die*/
} ID_TRANS_CELL;

//��������

/// <summary>
/// ����������Ӧ��IP��ַ�������ַ�����ʽIP��ַ���������ʾ��Ϣ
/// ����ʧ�ܣ�����failed�ַ���
/// �����������������������ں������С�
/// </summary>
/// <param name="Local_DNIPList">	����IP-�������ձ������ͷ		</param>
/// <param name="Temp_DNIPList">	���绺�����ɵ���ʱIP-�������ձ�����ͷ	</param>
/// <param name="url">	Ҫ��ѯ������	</param>
/// <returns>	�ַ�����ʽIP��ַ		</returns>
char *Ip_str(DNIPList **Local_DNIPList, DNIPList **Temp_DNIPList, char *url);

/// <summary>
/// ����level���DNS������Ϣ
/// </summary>
/// <param name="packet">Ҫ��ʾ��DNS����</param>
/// <param name="level">���Եȼ�</param>
void Show_DNSPacket(DNS_PACKET packet, char *buf);

///��ȡ���ص�dns���ձ����ѿյ�������ձ����ӵ����ص�dns��֮��
void Read_scheurl(DNIPList **local_dniplist, DNIPList **extern_dniplist);

/// <summary>
/// ���ֽ�����,����DNS����,�õ�����֮��������ַ���
/// </summary>
/// <param name="packet">�����DNS����</param>
/// <param name="dest">���������������ַ���</param>
void Get_TLD(char *buf, char *dest,unsigned long long offset);

/// <summary>
/// ��ȡDNS���ģ�����DNS���Ľṹ��
/// </summary>
/// <param name="buf">����ӿͻ��˻�ȡ���ַ�����</param>
DNS_PACKET receiveDNS(char *buf);

/// <summary>
/// ��ȡ�������ֽڳ���
/// </summary>
int Get_TLDLength(char *p);

unsigned short generate_new_id(unsigned short id, sockaddr_in cli, int ttl,
			       char *url);

void print_team_msg();

void getLevel(int argc, char *argv[]);

void PrintTime();