//
//  ��������/������
//
// ��������
//
//   ���ù��������������Ϣͨ�ſ��Դ������ŵ������ʣ�
//   ������Ϣ����ʱ�䣬���ʹ���ɱ������ǣ�
//   ��Ҫ���ڷ��Ͷ�ͨ��һ������ϵͳ�Դ�������Ԥ�ȱ��룬
//   �ڽ��ն˽����������ݽ������루��ԭ����
//   ��Ϊ��������Ϣ�շ�վдһ���������ı�/��������
//
// ���Ҫ��
//
//   �������������������ļ�(*.souce)��ͳ���ļ����ַ����ֵ�Ƶ�ȣ�
//   ������Щ�ַ���Ƶ����ΪȨֵ����������������
//   ���룺�����ѽ����õĹ�����������ø����ַ��Ĺ��������룬
//   �������Ľ��б��룬Ȼ��������������������ļ�(*.code)�С�
//   ���룺�����ѽ����õĹ����������ļ�(*.code)�еĴ���������룬
//   ��������������������ļ�(*.decode)�С�
//   ����λ������ʵ���ļ���ѹ�����ѹ����ѡ����

#define _CRT_SECURE_NO_WARNINGS
//#define N 128
//#define M 2 * N - 1
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

////���������Ľṹ������
//typedef struct
//{
//	int Weight;
//	int Parent, Lchild, Rchild;
//}HTNode, HuffmanTree[M + 1];
//
//// �洢����������
//typedef char * Huffmancode[N + 1];

//���������Ľṹ������
struct HuffmanTree
{
	int Weight;
	char Ch;
	int Parent, Lchild, Rchild;
};

int MeasuringFrequency(int frequency[], char name[]);
void IniHuffmanTree(HuffmanTree ht[], int frequency[], int count);
void CrtHuffmanTree(HuffmanTree ht[], int count);
void CrtHuffmanCode(HuffmanTree ht[], char hc[][128], int count);
void FileCode(HuffmanTree ht[], char hc[][128], char souce_name[]);
void FileDecode(HuffmanTree ht[], int count);

// ͳ�Ƹ����ַ����ֵ�Ƶ��
int MeasuringFrequency(int frequency[], char souce_name[])
{
	int ch;
	int count1 = 0;
	int count2 = 0;
	printf("�������ļ���(��Ҫ�ֶ������׺��.souce): ");
	scanf("%s", souce_name);
	FILE *fp = fopen(souce_name, "r");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��!!!\n");
		return -1;
	}
	while ((ch = fgetc(fp)) != EOF)
	{
		if (frequency[ch] == 0)
		{
			count1++;
		}
		frequency[ch]++;
		count2++;
	}
	printf("�����ַ�Ƶ�ʳɹ��������ַ�%d�������а���Ӣ���ַ�%d��", count2, count1);
	fclose(fp);
	return count1;
}

// ��ʼ����������
void IniHuffmanTree(HuffmanTree ht[], int frequency[], int count)
{
	int i;
	int j = 1;
	for (i = 0; i < 128; i++)
	{
		if (frequency[i] == 0)
		{
			continue;
		}
		ht[j].Weight = frequency[i];
		ht[j].Ch = i;
		ht[j].Parent = 0;
		ht[j].Lchild = 0;
		ht[j].Rchild = 0;
		j++;
	}
	for (; j < 2 * count - 1 + 1; j++)
	{
		ht[j].Ch = 0;
		ht[j].Weight = 0;
		ht[j].Parent = 0;
		ht[j].Lchild = 0;
		ht[j].Rchild = 0;
	}
	//for (i = 1; i < count + 1; i++) //������ʼ�Ľ��(��Ȩֵ)
	//{
	//	ht[i].Weight = frequency[i - 1];
	//	ht[i].Parent = 0;
	//	ht[i].Lchild = 0; 
	//	ht[i].Rchild = 0;
	//}
	//for (i = N + 1; i < 2 * count - 1 + 1; i++) // ����ʣ�µĽ��(û��Ȩֵ)
	//{
		//ht[i].Weight = 0;
		//ht[i].Parent = 0;
		//ht[i].Lchild = 0;
		//ht[i].Rchild = 0;
	//}
}

// ������������
void CrtHuffmanTree(HuffmanTree ht[], int count)
{
	int i;
	int j;
	int min1 = 2147483647; // �����int�����ֵ
	int min2 = 2147483647;
	int min1_i = 1;
	int min2_i = 1;
	for (i = count + 1; i < count * 2 - 1 + 1; i++) // ѭ������Ľ��
	{
		min1 = 2147483647;
		min2 = 2147483647;

		//Ѱ����Сֵ�ʹ�Сֵ
		for (j = 1; j < i; j++)
		{
			if (min1 > ht[j].Weight && ht[j].Parent == 0)
			{
				min2 = min1;
				min2_i = min1_i;
				min1 = ht[j].Weight;
				min1_i = j;
			}
			else if (min2 > ht[j].Weight && ht[j].Parent == 0)
			{
				min2 = ht[j].Weight;
				min2_i = j;
			}
		}

		//���ø�ĸ���ͺ��ӽ���Ȩֵ
		ht[i].Lchild = min1_i;
		ht[i].Rchild = min2_i;
		ht[i].Weight = min1 + min2;
		ht[min1_i].Parent = i;
		ht[min2_i].Parent = i;
	}
}

// ������������
void CrtHuffmanCode(HuffmanTree ht[], char hc[][128], int count)
{
	int i;
	char *cd; // ��ʱ�洢����
	int start;
	int c; //������
	int p;  // ��ĸ���
	cd = (char *)malloc(count * sizeof(char));
	cd[count - 1] = '\0';
	for (i = 1; i <= count; i++)
	{
		start = count - 1;
		c = i;
		p = ht[i].Parent;
		// ���Ŵ洢��������ʱ��cd��
		while (p != 0)
		{
			start--;
			if (ht[p].Lchild == c)
			{
				cd[start] = '0';
			}
			else
			{
				cd[start] = '1';
			}
			c = p;
			p = ht[p].Parent;
		}
		// ����ʱ��cd����hc��
		strcpy(hc[ht[i].Ch], &cd[start]);
	}
	free(cd); // �ͷ���ʱ
}

// �����Ľ��б��룬Ȼ��������������������ļ�(*.code)��
void FileCode(HuffmanTree ht[], char hc[][128], char souce_name[])
{
	int ch;
	char code_name[260];
	int i;
	for (i = 0; i < 260; i++)
	{
		code_name[i] = souce_name[i];
		if (souce_name[i] == '.')
		{
			i++;
			break;
		}
	}
	code_name[i++] = 'c';
	code_name[i++] = 'o';
	code_name[i++] = 'd';
	code_name[i++] = 'e';
	code_name[i++] = '\0';

	FILE *fp_souce = fopen(souce_name, "r");
	FILE *fp_code = fopen(code_name, "wb");
	if (fp_souce == NULL)
	{
		printf("�ļ���ʧ��!!!\n");
		return;
	}
	printf("\n����õĽ��Ϊ:");
	while ((ch = fgetc(fp_souce)) != EOF)
	{
		printf("%s", hc[ch]);
		fputs(hc[ch], fp_code);
	}
	printf("\n����ɹ�!\n");
	fclose(fp_souce);
	fclose(fp_code);
	return;
}


// ���룺�����ѽ����õĹ����������ļ�(*.code)�еĴ���������룬
// ��������������������ļ�(*.decode)�С�
void FileDecode(HuffmanTree ht[], int count)
{
	int ch;
	char code_name[260];
	char decode_name[260];
	printf("��������Ҫ������ļ���(��Ҫ�ֶ������׺��.code): ");
	scanf("%s", code_name);
	int i;
	for (i = 0; i < 260; i++)
	{
		decode_name[i] = code_name[i];
		if (code_name[i] == '.')
		{
			i++;
			break;
		}
	}
	decode_name[i++] = 'd';
	decode_name[i++] = 'e';
	decode_name[i++] = 'c';
	decode_name[i++] = 'o';
	decode_name[i++] = 'd';
	decode_name[i++] = 'e';
	decode_name[i++] = '\0';
	FILE *fp_code = fopen(code_name, "rb");
	FILE *fp_decode = fopen(decode_name, "w");
	if (fp_code == NULL)
	{
		printf("�ļ���ʧ��!!!\n");
		return;
	}
	i = count * 2 - 1 + 1 - 1;
	printf("\n������Ϊ: ");
	while ((ch = fgetc(fp_code)) != EOF)
	{
		if (i > 0 && i < count + 1)
		{
			printf("%c", ht[i].Ch);
			fputc(ht[i].Ch, fp_decode);
			i = count * 2 - 1 + 1 - 1;
		}
		if (ch == '0')
		{
			i = ht[i].Lchild;
		}
		else
		{
			i = ht[i].Rchild;
		}
	}
	if (i > 0 && i < count + 1)
	{
		printf("%c", ht[i].Ch);
		fputc(ht[i].Ch, fp_decode);
		i = count * 2 - 1 + 1 - 1;
	}
	printf("\n����ɹ�!\n");
	fclose(fp_code);
	fclose(fp_decode);
	//printf("�����ַ�Ƶ�ʳɹ��������ַ�%d�������а���Ӣ���ַ�%d��", count2, count1);
	//fclose(fp);
	return;
}

int main()
{
	char souce_name[260];
	int frequency[128] = { 0 };
	int count = MeasuringFrequency(frequency, souce_name);
	HuffmanTree *ht = (HuffmanTree *)malloc(sizeof(HuffmanTree) * count * 2 - 1 + 1);
	char hc[128][128];
	IniHuffmanTree(ht, frequency, count); // ��ʼ����������
	CrtHuffmanTree(ht, count); // �����������
	CrtHuffmanCode(ht, hc, count); // ������������
	FileCode(ht, hc, souce_name); // �����Ľ��б��룬Ȼ��������������������ļ�(*.code)��
	FileDecode(ht, count); // ���룺�����ѽ����õĹ����������ļ�(*.code)�еĴ���������룬
						   // ��������������������ļ�(*.decode)�С�

	system("pause");
	return 0;
}