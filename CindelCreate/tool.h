#include "BaseClass.h"

#ifndef LEE_CINDEL_CREATE_TOOL_H
#define LEE_CINDEL_CREATE_TOOL_H
#define IN
#define OUT

class config{
public:
	long deletion_maxLength=1000;/*ɾ������󳤶�*/
	long deletion_minLength=-1;/*ɾ������С����*/
	long insertion_maxLength=-1;/*�������󳤶�*/
	long insertion_minLength=-1;/*�������С����*/
	long startPos=-1;		/*ref�ǰ��indelλ��*/
	long endPos=-1;			/*ref����indelλ��*/
	static long Floating_distance;/*�������е����¸�����Χ*/
	static long Space_distance;/*����indel�ļ������*/
	long indelNumber=-1;/*����indel����*/
	long indelType=-1;/*indel���ͣ�0ɾ����1���룬2����indel*/
	long oneIndelMAXNums = -1;/*һ�����庬�е�indel���ֵ*/
	long oneIndelMINNums = -1;/*һ�����庬�е�indel��Сֵ*/
	long oneNums = -1;/*��Ⱥ����*/
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
