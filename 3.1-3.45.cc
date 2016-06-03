#include <iostream>
#include <vector>
#define NUM317

using namespace std;

int main(){
	cout <<"*****************"<<endl;
	cout <<"*****************"<<endl;
/*3.1*/
#ifdef NUM31
	cout<<"参见：http://blog.csdn.net/refuil/article/details/51226530 "
		"http://blog.csdn.net/refuil/article/details/51236735"<<endl;
#endif
/*3.2*/
#ifdef NUM32
	string line;
	string word;
	while(getline(cin, line)//一次读入一行，直至遇见文件结束符
		cout << line <<endl;
	while(cin >> word)		//一次读入一个单词，直至遇见文件结束符
		cout << word <<endl;
#endif
/*3.3*/
#ifdef NUM33
	cout<<"string类型读取并忽略有效字符之前所有的空白字符，然后读取字符直至再次遇到空白字符，读取终止（空白字符仍留在输入流中）"
		"getline()函数不忽略开头的空白字符，读取字符直至遇到换行符，读取终止并丢弃换行符。"<<endl;
#endif
/*3.4*/
#ifdef NUM34
	string str1, str2;
	cout << "Enter two strings: " <<endl;
	cin >> str1 >> str2;
	if(str1 == str2)
		cout << "They are the same."<<endl;
	else if(str1 > str2)
		cout << "The bigger one is: " << str1 <<endl;
	else 
		cout << "The bigger one is: " << str2 <<endl;
/* 比较size */	
	string::size_type len1, len2;
	len1 = str1.size();
	len2 = str2.size();
	if(len1 == len2)
		cout << "They are the same length."<<endl;
	else if(len1 > len2)
		cout << "The longer one is: "<<str1<<endl;
	else 
		cout << "The longer one is: "<<str2<<endl;
#endif
/*3.5*/
#ifdef NUM35
	string str, sum;
	cout << "Enter two strings: " <<endl;
	while(cin >> str)
		sum += str;
	cout<< "The concatenation of string is: "<< sum <<endl;
/* Add the blank*/
	cout << "Enter two strings: " <<endl;
	while(cin >> str)
		sum += " " + str;
	cout<< "The concatenation of string is: "<< sum <<endl;	
#endif
/*3.6*/
#ifdef NUM36
	string str("abcddefg");
	for(auto  &c :  str){
		if(!isspace(c))
			c = 'X';
	}
	cout<< str << endl;
#endif
/*3.7*/
#ifdef NUM37
	string str("abcddefg");
	for(char &c : str){
		if(!isspace(c))
			c = 'X';
	}
	cout << str << endl;
#endif
/*3.8*/
#ifdef NUM38
	string str("abcddefg");	
	int index = 0;
	while(index !=str.size()){
		if(!isspace(str[index]))
		str[index] = 'X';
		++index;
	}
	cout<< "while语句: "<< str<<endl;
/* for语句*/
	for(decltype(str.size()) index =0; index != str.size();++index){
		if(!isspace(str[index]))
			str[index] = 'X';
	}
	cout<< "for语句: " <<str <<endl;
#endif
/*3.9*/
#ifdef NUM39
	string s;
	cout << s[0] << endl;
	cout<<"输出s字符的第一个字符，不合法，因为s没有初始化是空字符串，是s[0]是无效的."<<endl;
#endif
/*3.10*/
#ifdef NUM310
	string str, result;
	bool has_punct;
	cout<<"Enter the string with punctuation: "<<endl;
	getline(cin,  str);
	for(auto &c : str){
		if(ispunct(c))
			has_punct = true;
		else
			result += c;
	}
	if(has_punct)
		cout<<"After the remove: "<< result <<endl;
	else{
	cout<<"No punctuation character in the string" <<endl;
	return -1;
	}
#endif
/*3.11*/
#ifdef NUM311
	cout<<"当且仅当不去改变 c 值时才是合法的，c的类型是const char&; 如果试图改变就是不合法的。"<<endl;
#endif
/*3.12*/
#ifdef NUM312
	cout<<"(b)不合法，赋值左右类型不同，svec是string对象的vector对象，ivec是保存vector<int>对象的vector对象. "<<endl;
#endif
/*3.13*/
#ifdef NUM313
	cout<<"(a)0个int元素;(b)10个int元素，值都是0;(c)10个int元素，值都是42;(d)1个int型元素，值是10;(e)两个int元素，10和42;(f)10个string元素，值为0;(g)10个hi元素。"<<endl;
#endif
/*3.14*/
#ifdef NUM314
	vector<int> vec;
	int i;
	cout<<"Enter number: "<<endl;
	while(cin >> i){
		vec.push_back(i);
	}
	for(auto &c : vec)
		cout<< c;
	cout<<endl;
#endif
/*3.15*/
#ifdef NUM315
	vector<string> vec;
	string i;
	cout<<"Enter string : "<<endl;
	while(cin >> i){
		vec.push_back(i);
	}
	for(auto &c : vec)
		cout<< c;
	cout<<endl;
#endif
/*3.16*/
#ifdef NUM316
	vector<int> v1;         // size:0,  no values. 
	cout<<"v1: size is "<<v1.size()<<" ";
	for(auto &c : v1)
		cout<< c;
	cout<<endl;
	vector<int> v2(10);     // size:10, value:0
	cout<<"v2: size is "<<v2.size()<<" ";
	for(auto &c : v2)
		cout<< c <<" ";
	cout<<endl;
	vector<int> v3(10, 42); // size:10, value:42 
	cout<<"v3: size is "<<v3.size()<<" ";
	for(auto &c : v3)
		cout<< c <<" ";
	cout<<endl;
	vector<int> v4{10};     // size:1,  value:10 
	cout<<"v4: size is "<<v4.size()<<" ";
	for(auto &c : v4)
		cout<< c <<" ";
	cout<<endl;
	vector<int> v5{10, 42}; // size:2,  value:10, 42 
	cout<<"v5: size is "<<v5.size()<<" ";
	for(auto &c : v5)
		cout<< c <<" ";
	cout<<endl;
	vector<string> v6{10};  // size:10, value:""  
	cout<<"v6: size is "<<v6.size()<<" ";
	for(auto &c : v6)
		cout<< c <<" ";
	cout<<endl;
	vector<string> v7{10, "hi"};  // size:10, value:"hi"
	cout<<"v7: size is "<<v7.size()<<" ";
	for(auto &c : v7)
		cout<< c <<" ";
	cout<<endl;
#endif
/*3.17*/
#ifdef NUM317
	string str;
	vector<string> vec;
	while(cin >> str)
		vec.push_back(str);
	for(decltype(vec.size()) index = 0; index != vec.size(); ++index){
		for(auto &c : vec[index]){
			if(!isupper(c))
			toupper(c);
		}
	}
	for(decltype(vec.size()) index = 0; index != vec.size(); ++index){
		for(auto &c : vec[index]){
			cout<< c <<endl;
		}
	}





	return 0;
}
