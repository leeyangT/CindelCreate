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
	long DstartPos;	//indel起始位置
	long Dlength;		//indel长度
	string Dsequence;	//indel序列
	long type;			//标志是0删除1插入2复杂
	long IStartPos;
	long ILength;
	string ISeq;
};



class One
{
public:
	One(){};
	long cindelNums;//包含的cindel数量
	string fref;
	string mref;
	void randomCIndel(long minNums);//随机产生个体携带根据数量随机挑选已经产生的CINDEL并随机生成类型
	vector<int> cIndelList;//包含的iNdel编号
	vector<int> cIndelType;//indel类型AB或BB，0代表BB
};

#endif
