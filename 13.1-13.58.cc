#include <fstream>
#include <iostream>
#include <vector>
#include "Chapter13.h"
using namespace std;
#define NUM1324

/*13.13*/
void func(const X& rx, X x){
	vector<X> vec;
	vec.reserve(2);
	vec.push_back(rx);
	vec.push_back(x);
}
/*13.4*/


int main(){
/*13.1*/
#ifdef NUM131
	cout << "拷贝构造函数是一种特殊的构造函数，它的第一个参数是自身类型的引用。"
			"以下情况调用拷贝构造函数："
			"当用=定义变量"
			"一个对象以值传递的方式传入函数体 "
			"一个对象以值传递的方式从函数返回 "
			"一个对象需要通过另外一个对象进行初始化。"
			"用花括号列表初始化一个数组中的元素或一个聚合类中的成员。"
			"某些类类型还会对它们所分配的对象使用拷贝初始化。"<<endl;
#endif
/*13.2*/
#ifdef NUM132
	cout <<"这一方式永远不会调用拷贝构造函数，因为非引用类型的参数要进行拷贝初始化。"
			"Sales_data rhs是一个形参，因此我们需要调用拷贝构造函数来拷贝构造函数，但是为了拷"
			"贝实参，又需要调用拷贝构造函数，以此往复。"<<endl;
#endif
/*13.3*/
#ifdef NUM133
	cout <<"当拷贝一个StrBlob时，shared_ptr成员的引用计数加1；"
			"当拷贝StrBlobPtr时，week_ptr成员的计数不变。" <<endl;
#endif
/*13.4*/
#ifdef NUM134
/*	Point global;
	Pointfoo_bar(Point arg){              		  // 1
	Point local = arg, *heap = newPoint(global); // 2, 3
    *heap = local;
	Point pa[ 4 ] = { local, *heap };           // 4, 5
	return *heap;                               // 6
}
*/
#endif
/*13.5*/
#ifdef NUM135
	cout <<"见Chapter13.h"<<endl;
#endif
/*13.6*/
#ifdef NUM136
	cout<<"拷贝赋值运算符是一个名为operator=的函数。当出现赋值操作时使用。"
		"合成拷贝赋值运算符将右侧运算对象的每个非static成员赋予左侧运算对象的对应成员，"
		"这一工作通过成员类型的拷贝赋值运算符来完成。"
		"当一个类未定义自己的拷贝赋值运算符，编译器会为它生成一个合成拷贝赋值运算符。"<<endl;
#endif
/*13.7*/
#ifdef NUM137
	cout<<"右侧运算对象的每个非static成员赋予左侧运算对象的对应成员，"
			"StrBlob的引用计数加1，StrBlobPtr的引用计数不变。"<<endl;
#endif
/*13.8*/
#ifdef NUM138
	cout <<"见Chapter13.h"<<endl;
#endif
/*13.9*/
#ifdef NUM139
	cout<<"析构函数时类的成员函数，名字由(~)加类名组成，不接受参数，也没有返回值。"
		"当一个类未定义自己的析构函数时，编译器会定义一个合成析构函数。合成析构函数用来阻"
		"止该类型的对象被销毁。如果不是这样，合成析构函数体内就为空。"<<endl;
#endif
/*13.10*/
#ifdef NUM1310
	cout<<"StrBlob对象销毁时，use_count计数器递减，如果没有对象的共享类型，它的内存会被释放。"
		"当StrBlobPtr被销毁时，动态分配的对象并不会被释放。"<<endl;
#endif
/*13.11*/
#ifdef NUM1311
	cout <<"见Chapter13.h"<<endl;
#endif
/*13.12*/
#ifdef NUM1312
	cout<< "3次，accum, item1 and item2.发生了拷贝，会自动调用析构函数."<<endl;
#endif
/*13.13*/
#ifdef NUM1313
	X *ex1 = new X;
    func(*ex1, *ex1);
    delete ex1;
#endif
/*13.14*/
#ifdef NUM1314
	numbered a, b = a, c = b;
	func_14(a); func_14(b); func_14(c);
#endif
/*13.15*/
#ifdef NUM1315
	numbered_15 a, b = a, c = b;
	func_15(a); func_15(b); func_15(c);
	cout <<"因为没有用合成拷贝控制成员，而是自己定义得。输出为不同的数。"<<endl;
#endif
/*13.16*/
#ifdef NUM1316
	numbered_16 a, b = a, c = b;
	func_16(a); func_16(b); func_16(c);
	cout <<"因为f函数没有任何拷贝操作，所以输出的值和传入f函数时候相同。"<<endl;
#endif
/*13.18*/
#ifdef NUM1318
	cout <<"见Chapter13.h"<<endl;
#endif
/*13.19*/
#ifdef NUM1319
	cout << "理论上可以，但是不需要，人员类不可以拷贝。"<<endl;
#endif
/*13.20*/
#ifdef NUM1320
	cout << "TextQuery/QueryResult中的成员、智能指针将发生拷贝操作。"<<endl;
#endif
/*13.21*/
#ifdef NUM1321
	cout << "没有必要，因为两个类型之间通过智能指针实现动态内存与数据共享，自动调用合成析构函数释放内存。"<<endl;
//	TextQuery(const TextQuery&) = delete;
//	TextQuery&operator=(const TextQuery) = delete;

//	QueryResult(const QueryResult&) = delete;
//	QueryResult&operator=(const QueryResult) = delete;
#endif
/*13.22*/
#ifdef NUM1322
	cout <<"见Chapter13.h"<<endl;
#endif
/*13.24*/
#ifdef NUM1324
	cout<<"如果析构函数没有定义，将发生内存泄漏；如果拷贝函数没有定义，只有指针被拷贝了，ps指向的string并没有拷贝。"<<endl;
	HasPtr_24 aa("hello"), bb;
	bb = aa;
	cout << bb.get_24() <<endl;
#endif
/*13.25*/
#ifdef NUM1325
	cout<< "拷贝构造和拷贝赋值运算符动态分配内存，而不是与=右侧的对象共享对象。"
		"StrBlob的智能指针由合成析构函数管理，如果StrBlob对象离开作用域，智能指针的析构函数将被自动调用释放内存。"<<endl;
#endif
/*13.26*/
#ifdef NUM1326

#endif
/*13.27*/
#ifdef NUM1327

#endif
/*13.213*/
#ifdef NUM1328

#endif
/*13.213*/
#ifdef NUM13213

#endif
/*13.30*/
#ifdef NUM1330

#endif
/*13.31*/
#ifdef NUM1331

#endif
/*13.32*/
#ifdef NUM1332

#endif
/*13.33*/
#ifdef NUM1333

#endif
/*13.34*/
#ifdef NUM1334

#endif
/*13.35*/
#ifdef NUM1335

#endif
/*13.36*/
#ifdef NUM1336

#endif
/*13.37*/
#ifdef NUM1337

#endif
/*13.38*/
#ifdef NUM1338

#endif
/*13.39*/
#ifdef NUM1339

#endif
/*13.40*/
#ifdef NUM1340

#endif
	return 0;
}
