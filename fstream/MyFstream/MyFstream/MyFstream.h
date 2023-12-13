#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
/**
*   һ�������� 
*	1��ios �������ĸ���
*	2��istream    ���������࣬�����������е���������ʽ���ͷǸ�ʽ����ת��������
*	   ifstream   �ļ�������
*	   istream_withassign    cin��������
*	   istrstream ���������� ����C���� char*�ı�д
*	   istringstream ���������� ����string�ı�д
*   3��ostream    ���������
*	   ofstream
*	   ostream_withassign
*	   ostrstream
*	   ostringstream
*   ������ȡstring����
*	1��cin>>string   ���Կհ��ַ� ֪�������հ��ַ�
*   2��getline(istream,string) �����Կ�ͷ�Ŀհ��ַ� ��һ���ַ��ǻ����򷵻ؿ�  ����ʱ�������з�
*	������sstream��
*	string->int
*	string res = "10000"; int n = 0; stream<<res; stream>>n; ���ת��clear���
*	to_string(string& str, const T&t) ostringstream oss; oss<<t; str = oss.str();
*	outType&& convert(const inType& t) stringstream stream;  stream<<t; outType res; stream>>res; return res;
*	stringstream ͨ��������ת��
**/

//#define BINARY 1
struct data {
	int size = 0;
	char name[100];

};
class MyStream {
public:
	MyStream() {
		Init();
	};
	~MyStream() {
		if (fp.is_open())
			fp.close();
	};


	void Init() {
		fp.open("desc.txt", std::ios::out);//д
		if (!fp.is_open()) {
			std::cout << "open file failed!" << std::endl;
			return;
		}
		fp << "test data" << std::endl;

	}
#ifdef NORMAL
	void MyRead() {
		if (fp.is_open())
			fp.close();
		std::ifstream ifs;
		ifs.open("desc.txt", std::ios::in);//��
		if (!ifs.is_open()) {
			std::cout << "read failed!" << std::endl;
			return;
		}
		//std::string data;
		//ifs >> data;//�����" "
		//std::cout << data << std::endl;
		char buf[100] = { 0 };
		//ifs.getline(buf, 100);// ��ȡ�����з� 
		//std::cout << buf << std::endl;
		//std::cout << strlen(buf) << std::endl;


		int idx = 0;
		while (1) {
			buf[idx] = ifs.get();
			if (buf[idx] == EOF) {// ���л��з���end�ڻ��з�֮��
				buf[idx] = '\0';
				std::cout << idx << std::endl;
				break;
			}
			idx++;
		}
		std::cout << buf << strlen(buf) << std::endl;
		ifs.close();

}

#elif (BINARY == 1)
	void MyRead() {
		std::fstream fs("test.doc", std::ios::out | std::ios::binary);
		if (!fs.is_open()) {
			std::cout << "open binary file failed!" << std::endl;
			return;
		}
		data d;
		strcpy_s(d.name,"��Ӯ");
		d.size = strlen(d.name);
		fs.write((const char *) & d, sizeof(data));
		fs.close();
		std::fstream ifs("test.doc", std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			std::cout << "binary read failed!" << std::endl;
		}

		char buf[100];
		data rd;
		ifs.read((char*) & rd, sizeof(data));
		std::cout << rd.name<<rd.size<< std::endl;
	}
#else
	void MyRead() {
		std::ifstream fs;
		fs.open("desc.txt", std::ios::in);
		if (!fs.is_open()) {
			std::cout << "greater open file failed!" << std::endl;
			return;
		}
		fs.seekg(0, std::ios::end);
		char buf[1024] = {0};
		std::streamoff size = fs.tellg();
		fs.seekg(0, std::ios::beg);
		while (fs >> buf) {
			std::cout << buf << std::endl;
		}
		fs.close();
	}
#endif // NORMAL




	int&& convert(const std::string& t) {
		std::stringstream stream;  stream << t; int res; stream >> res; return std::move(res);
	}

private:
	std::ofstream fp;

	std::string path;

};