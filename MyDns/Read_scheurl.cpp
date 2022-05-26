#include"total.h"
/// 
/// </summary>
/// <param name="local_dniplist"></param>
/// <param name="net_dniplist"></param>
///
//typedef struct DNIPList{ //������и���
//char ip[16]; //IP��ַ �������޸� ip��ַ�ĸ�ʽ xxx.xxx.xxx.xxx 16���ֽ�Ӧ�ÿ���ʹ��
//char dn[65]; //����
//int expire_time;   //����ʱ��
//DNIPList *nextPtr; //ָ����һ����ָ��
//}
//DNIPList; //��׼��������Ҫ�в���ֵ��ͷ�ڵ�

//ȫ�ֱ�������
extern int level;
extern ID_TRANS_CELL trans_table[ID_TRANS_SIZE]; /*The ID_TRANS_TABLE*/
                     /*The cells of trans_table now*/
extern char fileName[129];


void Read_scheurl(DNIPList **local_dniplist,DNIPList **extern_dniplist)
{
	FILE *fp;
	int count = 0;//���ڼ�¼�ж��ٸ��ڵ�
	DNIPList *last;//ָ��β����ָ��
	fopen_s(&fp,fileName, "r"); //ֻ����ʽ���ļ�
	if (!fp) {
		printf("Read scheduled URL failed.\n"); //��ȡ����
		return;
	}
	char url[129], ip[16];
	*local_dniplist = (DNIPList *)malloc(sizeof(DNIPList));
	//��ʼ��
	if (!*local_dniplist) {//�����ڴ�ʧ��
		return;
	}
	memset((*local_dniplist)->dn, 0, sizeof((*local_dniplist)->dn));
	memset((*local_dniplist)->ip, 0, sizeof((*local_dniplist)->ip)); 
	(*local_dniplist)->expire_time = -1;
	(*local_dniplist)->nextPtr = NULL; 
	(*local_dniplist)->length = 1;//������ͷ�ڵ�ĳ���
	last = *local_dniplist;//��β��ָ�����ڵ�λ��
	while (!feof(fp) ){
		fscanf_s(fp, "%s %s", ip, (unsigned)sizeof ip, url,
			 (unsigned)sizeof url);
		count++;
		DNIPList *temp = (DNIPList *)malloc(sizeof(DNIPList));//�½ڵ�
		if (!temp) {//�����ڴ�ʧ��
			return;
		}
		memset(temp->dn, 0, sizeof(temp->dn));
		memset(temp->ip, 0, sizeof(temp->ip));
		(*local_dniplist)->expire_time = -1;
		temp->nextPtr = NULL;
		if (level >= 1) {
			printf("Read from 'dest.txt'->[URL:%s, IP:%s]\n", url,
			       ip);
			
		}
		memcpy_s(temp->ip,sizeof ip, ip, sizeof ip);//��ֵ
		memcpy_s(temp->dn,sizeof url , url , sizeof url);
		temp->expire_time = INFINITE;
		last->nextPtr = temp;
		last = temp;//����β��
		(*local_dniplist)->length++;
	}
	fclose(fp);
	printf("%d data have been saved\n", count);
	DNIPList *temp = (*local_dniplist)->nextPtr;
	//������صı�
	for (int i = 0; i < count; i++) {
		printf("Data %d, URL:%s -> IP:%s\n", i + 1, temp->dn, temp->ip);
		temp = temp->nextPtr;
	}
	*extern_dniplist = (DNIPList *)malloc(sizeof(DNIPList));
	memset((*extern_dniplist)->dn, 0, sizeof((*extern_dniplist)->dn));
	memset((*extern_dniplist)->ip, 0, sizeof((*extern_dniplist)->ip)); 
	(*extern_dniplist)->expire_time = -1;
	(*extern_dniplist)->nextPtr = NULL; 
	(*extern_dniplist)->length = 1;
	last->nextPtr = *extern_dniplist;
	return;
}

void print_team_msg(){
	printf("*****************************************************************\n");
	printf("* @Course Name: Course Design of Computer Network               *\n");
	printf("* @Name of Team members: Yang Yexuan, Yang Yuheng, Weng Yuechuan*\n");
	printf("* @Teacher: Jiang Yanjun         @Class number: 2020211301      *\n");
	printf("* ------------------------------------------------------------- *\n");
	printf("*               DNS Relay Server - Ver 1.0                      *\n");
	printf("*****************************************************************\n");
	printf("Command syntax : MyDns [-d | -dd] [dns-server-IP-addr]  \n");
}