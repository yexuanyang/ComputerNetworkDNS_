#include "total.h"

/// <summary>
/// ���ֽ�����������DNS���ģ��õ�����֮��������ַ���
/// </summary>
/// <param name="packet">�����DNS����</param>
/// <param name="dest">���������������ַ���</param>
void Get_TLD(char *buf, char *dest)
{
	int i = 0, j = 0,
	    k = 0; //i�Ǳ�������±꣬j�Ǽ����Ǽ���k��Ŀ��λ���±꣬
	while (buf[i] != 0) {
		if (buf[i] > 0 &&
		    buf[i] <=
			    63) //���buf[i]Ϊ�����ֽڣ�����3www5baidu3com�е�3��5��3��
		{
			for (j = buf[i], i++; j > 0; j--, i++, k++)
				dest[k] = buf[i];
		}
		if (buf[i] != 0) //���û��������dest��Ӹ�'.'
		{
			dest[k] = '.';
			k++;
		}
	}
	dest[k] = '\0';
}