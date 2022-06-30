#include "total.h"
extern int level;


void LRU(DNIPList** head, DNIPList* destNode,DNIPList* destNodeAhead) {
	time_t now;
	time(&now);
	if (destNode != (*head)->nextPtr) {//LRU destnode
		DNIPList *curHead = (*head)->nextPtr;
		destNodeAhead->nextPtr = destNode->nextPtr;
		destNode->nextPtr = curHead;
		(*head)->nextPtr = destNode;
	}
	for (DNIPList *current = (*head)->nextPtr, *last = (*head); current; ) {//current is the first node , not the head
	// delete the expired node
		if (current->expire_time < now) {
			last->nextPtr = current->nextPtr;
			DNIPList *Temp = current;
			current = current->nextPtr;
			free(Temp);
		} else {
			last = current;
			current = current->nextPtr;
		}
	}
	
	DNIPList *prinTemp = NULL;
	prinTemp = (*head)->nextPtr; // get the first node
	if (level >= 2) {
		printf("========= Cache ========\n");
		for (int i = 0; prinTemp != NULL;
		     prinTemp = prinTemp->nextPtr) {
			printf("#%d Url:%s --> IP: %s\n", i, prinTemp->dn,
			       prinTemp->ip);
			i++;
		}
		printf("======================\n");
	}
	
}

char *Ip_str(DNIPList **Local_DNIPList, DNIPList **Temp_DNIPList, char *url)
{
	char *ip_str = (char *)malloc(sizeof(char)*17);
	time_t now;
	time(&now);
	if (!ip_str) {
		printf(" \n\n申请内存失败\n");
		exit(1);
	}
	char *destName = url;
	DNIPList *cur_Pair_In_Local_List = (*Local_DNIPList)->nextPtr,
		 *cur_Pair_In_Temp_List = (*Temp_DNIPList)->nextPtr;//get the first node
	DNIPList *cur_Pair_In_Temp_List_ahead = *Temp_DNIPList;//the one node ahead of cur_Pair_In_Temp_List node
	while (cur_Pair_In_Local_List != *Temp_DNIPList || cur_Pair_In_Temp_List) {
		if (cur_Pair_In_Local_List != *Temp_DNIPList &&
		    cur_Pair_In_Local_List &&
		    strcmp(cur_Pair_In_Local_List->dn, destName) ==
			    0) { //find in local
			#if _WIN64
				strcpy_s(ip_str, sizeof cur_Pair_In_Local_List->ip,
						cur_Pair_In_Local_List->ip);
			#elif __linux__
				memcpy(ip_str,cur_Pair_In_Local_List->ip,sizeof cur_Pair_In_Local_List->ip);
			#endif
			if (level > 0) {
				printf("从本地对照表获取IP成功\n");
			}
			return ip_str;

		} else if (cur_Pair_In_Temp_List &&
			   strcmp(cur_Pair_In_Temp_List->dn,
				  destName) == 0 && cur_Pair_In_Temp_List->expire_time > now) { //find in temp
			#if _WIN64
				strcpy_s(ip_str, sizeof cur_Pair_In_Temp_List->ip,
						cur_Pair_In_Temp_List->ip);
			#elif __linux__
				memcpy(ip_str,cur_Pair_In_Temp_List->ip,sizeof cur_Pair_In_Temp_List->ip);
			#endif
			if (level > 0) {
				printf("从网络缓存表获取IP成功\n");
			}
			LRU(Temp_DNIPList, cur_Pair_In_Temp_List,
			    cur_Pair_In_Temp_List_ahead);
			return ip_str;
		}
		if (cur_Pair_In_Local_List && cur_Pair_In_Local_List != *Temp_DNIPList) {
			cur_Pair_In_Local_List = cur_Pair_In_Local_List->nextPtr;
		}
		
		if (cur_Pair_In_Temp_List) {
			cur_Pair_In_Temp_List_ahead = cur_Pair_In_Temp_List;
			cur_Pair_In_Temp_List = cur_Pair_In_Temp_List->nextPtr;
		}
	}
	#if _WIN64
		strcpy_s(ip_str, 7, "failed");
	#elif __linux__
		memcpy(ip_str,"failed",7);
	#endif
	return ip_str;
}
