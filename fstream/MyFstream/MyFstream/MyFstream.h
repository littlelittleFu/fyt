#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
/**
*   一、流分类 
*	1、ios 所有流的父类
*	2、istream    输入流基类，将流缓冲区中的数据做格式化和非格式化的转换并输入
*	   ifstream   文件输入类
*	   istream_withassign    cin输入流类
*	   istrstream 串输入流类 基于C类型 char*的编写
*	   istringstream 串输入流类 基于string的编写
*   3、ostream    输出流基类
*	   ofstream
*	   ostream_withassign
*	   ostrstream
*	   ostringstream
*   二、读取string对象
*	1、cin>>string   忽略空白字符 知道遇到空白字符
*   2、getline(istream,string) 不忽略开头的空白字符 第一个字符是换行则返回空  返回时丢弃换行符
*	三、对sstream库
*	string->int
*	string res = "10000"; int n = 0; stream<<res; stream>>n; 多次转换clear清除
*	to_string(string& str, const T&t) ostringstream oss; oss<<t; str = oss.str();
*	outType&& convert(const inType& t) stringstream stream;  stream<<t; outType res; stream>>res; return res;
*	stringstream 通常做数据转化
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
		fp.open("desc.txt", std::ios::out);//写
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
		ifs.open("desc.txt", std::ios::in);//读
		if (!ifs.is_open()) {
			std::cout << "read failed!" << std::endl;
			return;
		}
		//std::string data;
		//ifs >> data;//输出到" "
		//std::cout << data << std::endl;
		char buf[100] = { 0 };
		//ifs.getline(buf, 100);// 截取到换行符 
		//std::cout << buf << std::endl;
		//std::cout << strlen(buf) << std::endl;


		int idx = 0;
		while (1) {
			buf[idx] = ifs.get();
			if (buf[idx] == EOF) {// 若有换行符则end在换行符之后
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
		strcpy_s(d.name,"冠赢");
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