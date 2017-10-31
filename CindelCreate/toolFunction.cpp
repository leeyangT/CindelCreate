#include "tool.h"

using namespace std;


long config::Floating_distance = 500;
long config::Space_distance = 1500;

void dealtool::createIndel(IN OUT vector<Indel>& list, string ref,config cof)
{
	int tryj=0;
	for (long i = 0; i < cof.indelNumber;)
	{
		long startPos = dealtool::getRandomNum(cof.startPos, cof.endPos);
		long length = dealtool::getRandomNum(cof.deletion_minLength, cof.deletion_maxLength);
//		cout<<startPos<<"\t"<<length<<endl;
		Indel temp = Indel(startPos, length, cof.indelType);
		if (temp.type == 2)
		{
			long istartPos = dealtool::getRandomNum(startPos - cof.Floating_distance, startPos+cof.Floating_distance);
			long ilength = dealtool::getRandomNum(cof.insertion_minLength, cof.insertion_maxLength);
			temp.IStartPos = istartPos;
			temp.ILength =ilength;
		}
		if (dealtool::canAdd(list, temp,cof))
		{
			i++;
			dealtool::getSeqSequence(ref, temp);
			if (true)
			{

			}
			list.push_back(temp);
//			cout << i <<"\t"<<tryj<< endl;
		}
	tryj++;
	}
}

bool dealtool::canAdd(IN vector<Indel> list, IN Indel temp, config cof)
{
	for (auto item = list.begin(); item != list.end(); item++)
	{
		if (temp.DstartPos < item->DstartPos && item->DstartPos - config::Space_distance < temp.DstartPos)
		{
			return false;
		}
		if (temp.DstartPos > item->DstartPos && item->DstartPos + config::Space_distance > temp.DstartPos)
		{
			return false;
		}
		if (temp.DstartPos < cof.startPos || temp.DstartPos + temp.Dlength + cof.Space_distance > cof.endPos)
		{
			return false;
		}
	}
	return true;
}

bool dealtool::canAdd(IN vector <int> list, IN int x)
{
	for (auto item = list.begin(); item != list.end(); item++)
	{
		if (*item == x)
		{
			return false;
		}
	}
	return true;
}

string dealtool::getAGCT()
{
	switch (dealtool::getRandomNum(0, 4))
	{
	case 0:return "A";
	case 1:return "G";
	case 2:return "C";
	case 3:return "T";
	default:
		throw 1;
		break;
	}
}

long dealtool::getRandomNum(long mini, long maxi)
{
	//srand((unsigned)time(NULL));
	static default_random_engine generator(time(0));
	static uniform_int_distribution<long> dis(0, LONG_MAX);
	 return mini + dis(generator)%(maxi-mini);
}

void dealtool::getSeqSequence(IN string ref, IN OUT Indel & temp)
{
	if (temp.type == 1)
	{
		for (long i = 0; i < temp.Dlength; i++)
		{
			temp.Dsequence.append(dealtool::getAGCT());
		}
	}
	else if (temp.type == 0)
	{
		temp.Dsequence = ref.substr(temp.DstartPos, temp.Dlength);
	}
	else if (temp.type == 2)
	{
		temp.Dsequence = ref.substr(temp.DstartPos, temp.Dlength);
		temp.ISeq = ref.substr(temp.IStartPos, temp.ILength);
	}
}

string * dealtool::split(IN string str,IN string sp,IN long num)
{
	string *result = new string[num];
	long start = 0;
	long end = 0;
	for (long i = 0; i < num; i++)
	{
		end = str.find_first_of(sp, start);
		result[i] = str.substr(start, end - start);
		start = end + 1;
	}
	return result;
}

bool filetool::readConfig(string filename,config &cof)
{
	ifstream in;
	in.open(filename);
	if (!in.is_open())
	{
		throw 101;
		return false;
	}
	while (!in.eof())
	{
		string temp;
		getline(in, temp);
		string*result;
		result = dealtool::split(temp, ":", 2);
		char *end;
		if (result[0] == "deletion_maxLength")
		{
			cof.deletion_maxLength  = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "deletion_minLength")
		{
			cof.deletion_minLength = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "insertion_maxLength")
		{
			cof.insertion_maxLength = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "insertion_minLength")
		{
			cof.insertion_minLength = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "startPos")
		{
			cof.startPos = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "endPos")
		{
			cof.endPos = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "indelNumber")
		{
			cof.indelNumber = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "indelType")
		{
			cof.indelType = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "ref_name")
		{
			cof.ref_name = result[1];
		}
		else if (result[0] == "oneNums")
		{
			cof.oneNums = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "oneIndelMAXNums")
		{
			cof.oneIndelMAXNums = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "oneIndelMINNums")
		{
			cof.oneIndelMINNums = static_cast<long>(strtol(result[1].c_str(), &end, 10));
		}
		else if (result[0] == "person_path")
		{
			cof.person_path = result[1];
		}
	}
	in.close();
	in.clear();

}

bool filetool::readRef(IN OUT string &ref,IN config cof)
{
	ifstream ins;
	ins.open("ref.txt", std::ios::in| std::ios::binary);
	cout<<cof.ref_name<<endl;
	if (!ins.is_open())
	{
		cout<<"not open"<<endl;
		throw 102;
		return false;
	}
	string temp;
	getline(ins, temp);
	while (getline(ins,temp))
	{
		ref += temp;
	}
	ins.close();
	return true;
}

bool filetool::printIndel(IN vector <Indel> list, IN config cof)
{
	ofstream out;
	out.open("indel.txt");
	if (!out.is_open())
	{
		throw 103;
		return false;
	}
	for (auto i = list.begin(); i != list.end(); i++)
	{
		out << "19" << "\t";
		switch(i->type){
			case 0: 
			out << i->DstartPos << "\t";
			out << i->DstartPos<<"_del" << "\t";
			out << i->Dsequence << "\t";
			out << "<DEL>"<< "\t";
			out << "." << "\t";
			out << "." << "\t";
			out << "SVTYPE=DEL;END=" << i->DstartPos + i->Dlength;
			break;
			case 1: 
			out << i->IStartPos << "\t";
			out << i->IStartPos<<"_ins" << "\t";
			out << "<INS>"<< "\t";
			out << i->ISeq << "\t";
			out << "." << "\t";
			out << "." << "\t";
			out << "SVTYPE=INS;END=" << i->IStartPos + i->ILength;
			break;
			case 2: 
			out << i->DstartPos << "\t";
			out << i->DstartPos<<"_cdi" << "\t";
			out << i->Dsequence << "\t";
			out << i->ISeq << "\t";
			out << "." << "\t";
			out << "." << "\t";
			out << "SVTYPE=CDI;END=" << i->DstartPos + i->Dlength;
			break;
		}
		out << endl;
	}
	out.close();
}

bool filetool::printInpos(IN vector <Indel> list, IN config cof)
{
	ofstream out;
	out.open("inpos.txt");
	if (!out.is_open())
	{
		throw 104;
		return false;
	}
	int num = 1;
	for (auto i = list.begin(); i != list.end(); i++)
	{
		out << num << "\t";
		out << i->DstartPos << "\t";
		out << "-" << i->Dlength << "\t";
		out << 1<< "\t";
		out << 1<< "\t";
		out << 0 << "\t";
		out << i->Dsequence << "\n";
		if (i->type == 2)
		{
			out << num +1 << "\t";
			out << i->DstartPos << "\t";
			out << i->ILength << "\t";
			out << 1 << "\t";
			out << 1 << "\t";
			out << 0 << "\t";
			out << i->ISeq << "\t";
		}
		out << endl;
		num+=2;
	}
	out.close();
}

void filetool::printOne(IN vector<One> & onelist, IN vector <Indel> list, IN config cof)
{
	
	int num = 0;
	int state = access(cof.person_path.c_str(), F_OK);
	if (state !=0){
		string dir = "mkdir "+cof.person_path;
		system(dir.c_str());
	}
	for (auto i = onelist.begin(); i !=onelist.end(); i++)
	{
		ofstream out;
		std::stringstream sname;
		sname << "s" << num << ".txt";
		out.open(cof.person_path+sname.str());
		if( !out.is_open()){
			throw 111;
			return;
		}
		int inposNum = 0;
		for (int j = 0; j < i->cindelNums;j++)
		{
			if(i->cIndelType[j] == 0){
				continue;
			}
			out << inposNum*2+1 << "\t";
			out << list[j].DstartPos << "\t";
			out << "-"<<list[j].Dlength << "\t";
			out << i->cIndelType[j] << "\t";
			out << 1 << "\t";
			out << 0 << "\t";
			out << list[j].Dsequence << endl;;

			out << inposNum * 2+2 << "\t";
			out << list[j].DstartPos << "\t";
			out << list[j].ILength << "\t";
			out << i->cIndelType[j] << "\t";
			out << 1 << "\t";
			out << 0 << "\t";
			out << list[j].ISeq<< endl;
			inposNum++;
		}
		out.close();
		num++;
	}
}

void filetool::printVcfOne(IN vector<One> & onelist, IN vector <Indel> list, IN config cof)
{
	int num=0;
	for	(vector<One>::iterator oi = onelist.begin(); oi != onelist.end(); ++ oi)
	{	
		ofstream out;
		std::stringstream sname;
		sname << "vcfO" << num << ".txt";
		out.open(cof.person_path+sname.str());
		if( !out.is_open()){
			throw 111;
			return;
		}
		for(int ci=0; ci<oi->cIndelList.size(); ++ci)
		{
			Indel* i = &list[oi->cIndelList[ci]];
			out << "19" << "\t";
			switch(i->type){
				case 0: 
				out << i->DstartPos << "\t";
				out << i->DstartPos<<"_del" << "\t";
				out << i->Dsequence << "\t";
				out << "<DEL>"<< "\t";
				out << "." << "\t";
				out << "." << "\t";
				out << "SVTYPE=DEL;END=" << i->DstartPos + i->Dlength;
				out << ";TYPE=" << oi->cIndelType[ci];
				break;
				case 1: 
				out << i->IStartPos << "\t";
				out << i->IStartPos<<"_ins" << "\t";
				out << "<INS>"<< "\t";
				out << i->ISeq << "\t";
				out << "." << "\t";
				out << "." << "\t";
				out << "SVTYPE=INS;END=" << i->IStartPos + i->ILength;
				out << ";TYPE=" << oi->cIndelType[ci];
				break;
				case 2: 
				out << i->DstartPos << "\t";
				out << i->DstartPos<<"_cdi" << "\t";
				out << i->Dsequence << "\t";
				out << i->ISeq << "\t";
				out << "." << "\t";
				out << "." << "\t";
				out << "SVTYPE=CDI;END=" << i->DstartPos + i->Dlength;
				out << ";TYPE=" << oi->cIndelType[ci];
				break;
			}
			out << endl;
		}
		out.close();
		num++;
	}
}

void dealtool::createOne(IN OUT vector<One> & onelist, IN vector<Indel> list, IN config cof, IN string ref)
{
	for (int i = 0; i < cof.oneNums; i++)
	{
		One tempO = One();
		tempO.cindelNums = cof.indelNumber;//dealtool::getRandomNum(cof.oneIndelMINNums, cof.oneIndelMAXNums);
		for (int j = 0; j < tempO.cindelNums; )
		{
			int x;
			if (dealtool::canAdd(tempO.cIndelList,j/*x= dealtool::getRandomNum(0,cof.indelNumber)*/))
			{
				tempO.cIndelList.push_back(j);
				tempO.cIndelType.push_back(dealtool::getRandomNum(2, 4));
				j++;
			}
		}
		sort(tempO.cIndelList.begin(), tempO.cIndelList.end(), [](const int s1, const int s2){return s1 < s2; });
		//createOneRef(tempO, list, ref);
		onelist.push_back(tempO);
	}
	
}

void dealtool::createOneRef(IN OUT One & temp, IN vector<Indel> list,IN string ref)
{
	for (int i = 0; i < temp.cindelNums; i++)
	{
		long currentPos = 0;
		if (list[temp.cIndelList[i]].type == 0)
		{
			if (temp.cIndelType[i] == 0)
			{
				temp.fref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				temp.mref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				currentPos = list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength;
			}
			else if(temp.cIndelType[i] == 1)
			{
				temp.fref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				temp.mref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength - currentPos));
				currentPos = list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength;
			}
		}
		else if (list[temp.cIndelList[i]].type == 1)
		{
			if (temp.cIndelType[i] == 0)
			{
				temp.fref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				temp.mref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				currentPos = list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength;
				temp.fref.append(list[temp.cIndelList[i]].Dsequence);
				temp.mref.append(list[temp.cIndelList[i]].Dsequence);
			}
			else if (temp.cIndelType[i] == 1)
			{
				temp.fref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				temp.mref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength - currentPos));
				currentPos = list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength;
				temp.fref.append(list[temp.cIndelList[i]].Dsequence);
			}
		}
		else if (list[temp.cIndelList[i]].type == 2)
		{
			if (temp.cIndelType[i] == 0)
			{
				temp.fref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				temp.mref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				currentPos = list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength;
				temp.fref.append(ref.substr(list[temp.cIndelList[i]].IStartPos, list[temp.cIndelList[i]].ILength));
				temp.mref.append(ref.substr(list[temp.cIndelList[i]].IStartPos, list[temp.cIndelList[i]].ILength));
			}
			else if (temp.cIndelType[i] == 1)
			{
				temp.fref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos - currentPos));
				temp.mref.append(ref.substr(currentPos, list[temp.cIndelList[i]].DstartPos+list[temp.cIndelList[i]].Dlength - currentPos));
				currentPos = list[temp.cIndelList[i]].DstartPos + list[temp.cIndelList[i]].Dlength;
				temp.fref.append(ref.substr(list[temp.cIndelList[i]].IStartPos, list[temp.cIndelList[i]].ILength));
			}
		}
	}
}

void dealtool::run()
{
	config cof;
	string ref;
	vector<Indel> deList;
	vector<One> personList;
	filetool::readConfig("config.txt",cof);
	cout<<"read config success"<<endl;
	filetool::readRef(ref, cof);
	cout<<"read ref success"<<ref.length()<<endl;
	dealtool::createIndel(deList,ref,cof);
	cout<<"create indel success"<<endl;
	sort(deList.begin(), deList.end(), [](const Indel& s1, const Indel &s2){return s1.DstartPos < s2.DstartPos; });
	cout<<"sort success"<<endl;
	filetool::printIndel(deList, cof);
	filetool::printInpos(deList, cof);
	cout<<"print success"<<endl;
	dealtool::createOne(personList, deList, cof,ref);
	cout<<"create one success"<<endl;
	filetool::printOne(personList, deList, cof);
	cout<<"print one success"<<endl;
	filetool::printVcfOne(personList, deList, cof);
	cout << endl;
}

