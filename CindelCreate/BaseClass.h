#include <vector>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <istream>
#include <functional>
#include <random>
#include <algorithm>
#include <sstream>
#include <climits>
#include <unistd.h>
#ifndef LEE_CINDEL_CREATE_BASECLASS_H
#define LEE_CINDEL_CREATE_BASECLASS_H
using namespace std;

class Indel
{
public:
	Indel(long sPos, long l, long t){ DstartPos = sPos; Dlength = l; type = t; IStartPos = 0; ILength = 0; }
	void print();
	long DstartPos;	//indel��ʼλ��
	long Dlength;		//indel����
	string Dsequence;	//indel����
	long type;			//��־��0ɾ��1����2����
	long IStartPos;
	long ILength;
	string ISeq;
};



class One
{
public:
	One(){};
	long cindelNums;//������cindel����
	string fref;
	string mref;
	void randomCIndel(long minNums);//�����������Я���������������ѡ�Ѿ�������CINDEL�������������
	vector<int> cIndelList;//������iNdel���
	vector<int> cIndelType;//indel����AB��BB��0����BB
};

#endif
