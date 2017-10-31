#include "BaseClass.h"

#ifndef LEE_CINDEL_CREATE_TOOL_H
#define LEE_CINDEL_CREATE_TOOL_H
#define IN
#define OUT

class config{
public:
	long deletion_maxLength=1000;/*删除的最大长度*/
	long deletion_minLength=-1;/*删除的最小长度*/
	long insertion_maxLength=-1;/*插入的最大长度*/
	long insertion_minLength=-1;/*插入的最小长度*/
	long startPos=-1;		/*ref最靠前的indel位置*/
	long endPos=-1;			/*ref最靠后的indel位置*/
	static long Floating_distance;/*插入序列的上下浮动范围*/
	static long Space_distance;/*两个indel的间隔距离*/
	long indelNumber=-1;/*撒入indel数量*/
	long indelType=-1;/*indel类型，0删除，1插入，2复杂indel*/
	long oneIndelMAXNums = -1;/*一个个体含有的indel最大值*/
	long oneIndelMINNums = -1;/*一个个体含有的indel最小值*/
	long oneNums = -1;/*种群数量*/
	string ref_name = "ref.txt";
	string person_path = "person/";
};


class dealtool{
public:
	void static  run();
	long static  getRandomNum(IN long min, IN long max);
	void static  createIndel(IN OUT vector<Indel> & list, IN string ref, IN config cof);//
	bool static canAdd(IN vector <Indel> list, IN Indel temp, IN config cof);
	string static getAGCT();
	void static getSeqSequence(IN string ref, IN OUT Indel & temp);
	void static createOne(IN OUT vector<One> & onelist, IN vector<Indel> list, IN config cof, IN string);
	void static createOneRef(IN OUT One & temp, IN vector<Indel> list,IN string ref);
	bool static canAdd(IN vector <int> list, IN int x);
	string static  *split(IN string str, IN string sp, IN long num);
};


class filetool{
public:
	static bool readConfig(IN string filename,IN OUT config &cof);
	static bool readRef(IN OUT string &ref, IN config cof);
	static bool printIndel(IN vector <Indel> list, IN config cof);
	static bool printInpos(IN vector <Indel> list, IN config cof);
	static void printOne(IN vector<One> & onelist, IN vector <Indel> list, IN config cof);
	static void printVcfOne(IN vector<One> & onelist, IN vector <Indel> list, IN config cof);
};


#endif
