//Chapter14.h
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include "Chapter14.h"
using namespace std;
#define NUM1432

/*14.16*/
void foo(String x){
    cout << x << endl;
}

void bar(const String& x){
    cout << x.c_str() << endl;
}

String baz(){
    String ret("world");
    return ret;
}

//14.44
//! normal function
int add(int i, int j)
{
    return i + j;
}

//! named lambda
auto mod = [](int i, int j) { return i % j; };

//! functor
struct wy_div {
    int operator()(int denominator, int divisor)
    {
        return denominator / divisor;
    }
};

//! the map
std::map<std::string, std::function<int(int, int)>> binops = {
    {"+", add},                                //  function pointer
    {"-", std::minus<int>()},                  //  library functor
    {"/", wy_div()},                           //  user-defined functor
    {"*", [](int i, int j) { return i * j; }}, //  unnamed lambda
    {"%", mod}                                 //  named lambda object
};



int main(){
/*14.1*/
#ifdef NUM141
	cout <<"不同，1. 我们可以直接调用重载运算符函数。2.重载运算符函数必须是类的成员，或者至少有一个类类型的参数."
		"重载运算符不保证操作数的求值顺序，例如对&&和||的重载版本不再具有'短路求值'的特性，两个操作数都要求值，而且不规定操作数的求值顺序。"
		"相同。重载运算符与内置运算符有一样的优先性和结合性。"<<endl;
#endif
/*14.2*/
#ifdef NUM142
	Sales_data item;
	cin >> item;
	cout << item << endl;
#endif
/*14.3*/
#ifdef NUM143
	cout <<"(a)string字符类型是const char[]类型，char*类型内置了==运算符，所以不会调用string类型的==重载. "
		"(b)string版本 (c)vector版本 (d)string版本"<<endl;
#endif
/*14.4*/
#ifdef NUM144
	cout <<"(a)对称操作符，不需要是成员.(b)改变对象的状态，必须是成员"
		"(c)改变对象状态，必须是成员(d)必须是成员(e)非成员(f)非成员(g)非成员(h)必须是成员" <<endl;
#endif
/*14.5*/
#ifdef NUM145
	Book book1(123, "C++","Lippman","2013");
	Book book2(123, "C++","Lippman","2013");
	if(book1 == book2) cout << book1 << endl;
#endif
/*14.6*/
#ifdef NUM146
	cout << "见Chapter14.h  //14.2"<<endl;
#endif
/*14.7*/
#ifdef NUM147
	String str("hello world");
	cout << str << endl;
#endif
/*14.8*/
#ifdef NUM148
	cout << "见Chapter14.h  //14.5"<<endl;
#endif
/*14.10*/
#ifdef NUM1410
	cout << "见Chapter14.h  //14.2"<<endl;
#endif
/*14.10*/
#ifdef NUM1410
	cout <<"(a)正确的形式  (b)24.95转换成unsigned类型，错误,输出10 24 22.8 0.95. "<<endl;
#endif
/*14.11*/
#ifdef NUM1411
	cout <<"只是没有添加输入检查，没有什么发生. "<<endl;	
#endif
/*14.12*/
#ifdef NUM1412
	cout << "见Chapter14.h  //14.5"<<endl;
#endif
/*14.13*/
#ifdef NUM1413
	cout << "不需要"<<endl;
#endif
/*14.14*/
#ifdef NUM1414
/*
	Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs){
		Sales_data sum = lhs;  // copy data members from lhs into sum
		sum = sum + rhs;             // add rhs into sum
		return sum;
	}
*/
	cout << "如上所示，直接定义opeartor+会拷贝一个不必要的临时对象。"<<endl;
#endif
/*14.15*/
#ifdef NUM1415
	cout << "见Chapter14.h  //14.5"<<endl;
#endif
/*14.16*/
#ifdef NUM1416
//StrBlob   StrBlobPtr
	StrBlob sb{"Hello", "World", "C++"};
    for (ConstStrBlobPtr iter = sb.cbegin(); iter != sb.cend(); iter.incr()) {
        cout << iter.deref() << " ";
    }
    cout << endl;
//StrVec
    StrVec vec;
    vec.reserve(6);
    cout << "capacity(reserve to 6): " << vec.capacity() << endl;

    vec.reserve(4);
    cout << "capacity(reserve to 4): " << vec.capacity() << endl;

    vec.push_back("hello");
    vec.push_back("world");

    vec.resize(4);

    for (auto i = vec.begin(); i != vec.end(); ++i)
        cout << *i << endl;
    cout << "-EOF-" << endl;

    vec.resize(1);

    for (auto i = vec.begin(); i != vec.end(); ++i)
        cout << *i << endl;
    cout << "-EOF-" << endl;

    StrVec vec_list{"hello", "world", "C++"};

    for (auto i = vec_list.begin(); i != vec_list.end(); ++i)
        cout << *i << " ";
    cout << endl;

    // Test operator==
    const StrVec const_vec_list{"hello", "world", "C++"};
    if (vec_list == const_vec_list)
        for (const auto& str : const_vec_list) cout << str << " ";
    cout << endl;
//string 见14.7
	char text[] = "world";
    String s0;
    String s1("hello");
    String s2(move(s0));
    String s3 = s1;
    String s4(text);
    s2 = s1;

    if (s2 == s1) cout << "s2 == s1" << endl;

    foo(s1);
    bar(s1);
    foo("temporary");
    bar("temporary");
    String s5 = baz();

    vector<String> svec;
    // svec.push_back(s0);
    svec.push_back(s1);
    svec.push_back(s2);
    svec.push_back(s3);
    svec.push_back(s4);
    svec.push_back(baz());
    svec.push_back("good job");

    for (const auto& s : svec) {
        cout << s << endl;
    }
    cout << "Input a string: ";
    String s6;
    cin >> s6;
    cout << s6 << endl;
#endif
/*14.17*/
#ifdef NUM1417
    cout << "需要，见Chapter14.h  //14.15"<<endl;
#endif
/*14.18*/
#ifdef NUM1418
//StrBlob
	StrBlob str1{"a","b","c"};
	StrBlob str2{"a","b","c"};
	if(str1 >= str2){
		for(ConstStrBlobPtr iter = str1.cbegin(); iter != str1.cend(); iter.incr())
			cout<< iter.deref()<< " ";
		cout << endl;
	}
//StrVec
	const StrVec const_vec_list{"hello", "world", "ok"};
	const StrVec const_vec_list_small{"hello", "world", "linux"};
	cout << (const_vec_list_small < const_vec_list) << endl;
//String
    String s1("hello");
	cout << "Input a string: ";
	String s6;
	cin >> s6;
	cout << s6 << endl;

	if (s6 > s1) cout << "s6 > s1" << endl;
#endif
/*14.19*/
#ifdef NUM1419
	cout << "需要，见Chapter14.h  //14.5"<<endl;
#endif
/*14.20*/
#ifdef NUM1420
	cout << "见Chapter14.h  //14.2"<<endl;
#endif
/*14.21*/
#ifdef NUM1421
/*
	Sales_data& Sales_data::operator+=(const Sales_data &rhs)
	{
		Sales_data old_data = *this;
		*this = old_data + rhs;
		return *this;
	}
	Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
	{
		Sales_data sum;
		sum.units_sold = lhs.units_sold + rhs.units_sold;
		sum.revenue = lhs.revenue + rhs.revenue;
		return sum;
	}
*/
	cout << "如上所示，+和+= 的运算符操作都定义了一个不必要的Sales_data对象。"<<endl;
#endif
/*14.22*/
#ifdef NUM1422
	string strCp5("C++ Primer");
    Sales_data cp5 = strCp5;
    cout << cp5 << endl;
#endif
/*14.23*/
#ifdef NUM1423
    const StrVec const_vec_list_small = {"hello", "world", "c++"};
    for(auto &i: const_vec_list_small) cout << i << " "; 
    cout <<endl;
#endif
/*14.24*/
#ifdef NUM1424
 	Date lhs(9999999), rhs(1);
    cout << (lhs -= 12000) << "\n";
#endif
/*14.25*/
#ifdef NUM1425
    cout <<"无需其他，见14.24"<<endl;
#endif
/*14.26*/
#ifdef NUM1426
//StrBlob 
    StrBlob sb1{"a", "b", "c"};
    StrBlob sb2 = sb1;

    sb2[2] = "abc";

    if (sb1 > sb2) {
        for (ConstStrBlobPtr iter = sb1.cbegin(); iter < sb1.cend();
             iter.incr())
            cout << iter.deref() << " ";
        cout << endl;
    }

    StrBlobPtr iter(sb2);
    cout << iter[2] << endl;
//StrVec
    const StrVec const_vec_list_small{"hello", "world", "ok"};
    cout << const_vec_list_small[1] << endl;
//String
     String s1("hello");
     cout << s1[2] << endl;
#endif
/*14.27*/
#ifdef NUM1427
    StrBlob sb1{"a", "b", "c"};
    StrBlob sb2 = sb1;
    sb2[2] = "abc";
    if (sb1 > sb2) {
    	for (StrBlobPtr iter = sb1.begin(); iter < sb1.end(); ++iter)
    		cout << iter.deref() << " ";
        cout << endl;
    }
    ConstStrBlobPtr iter(sb2);
    cout << (iter + 2).deref() << endl;
#endif
/*14.28*/
#ifdef NUM1428
    cout << "见Chapter14.h  //14.27"<<endl;
#endif
/*14.29*/
#ifdef NUM1429
    cout <<"因为++ -- 改变了对象的状态，定义const版本是没有意义的. "<<endl;
#endif
/*14.30*/
#ifdef NUM1430
    StrBlob sb1{"a", "b", "c"};
    StrBlob sb2 = sb1;
	StrBlobPtr iter1(sb1);
 	ConstStrBlobPtr iter2(sb2);
    cout << *(iter1+2) << " "<< iter2->size() << endl;
#endif
/*14.31*/
#ifdef NUM1431
	cout<< "StrBlobPtrde类中被北邮动态内存分配，所以只需要合成的析构函数. 并且, 两个成员weak_ptr<vector<string>>和size_t类型，前者定义了自己的拷贝构造函数，后者是内置类型。所以完全可以利用合成的拷贝控制。"<<endl;
#endif
/*14.32*/
#ifdef NUM1432
    StrBlob sb1{"a", "b", "c"};
    StrBlob sb2 = sb1;
	StrBlobPtr iter1(sb1);
	StrBlobPtr_pointer it(&iter1);
	cout << it->deref() <<endl;
#endif
/*14.33*/
#ifdef NUM1433
	cout <<"一个重载操作符函数与操作符相同数量的参数。因此，最小0最大256."<<endl;
#endif
/*14.34*/
#ifdef NUM1434
    func_class fc;
    cout << fc(0, 1, 2) << endl;
#endif
/*14.35*/
#ifdef NUM1435
    PrintString getstr;
    cout << getstr() << endl;
#endif
/*14.36*/
#ifdef NUM1436
    PrintString getInput;
    std::vector<std::string> vec;
    for (std::string tmp; !(tmp = getInput()).empty();) 
        vec.push_back(tmp);
    for (const auto& str : vec) 
        std::cout << str << " ";
    std::cout << std::endl;
#endif
/*14.37*/
#ifdef NUM1437
    std::vector<int> vec = {3, 2, 1, 4, 3, 7, 8, 6};
    std::replace_if(vec.begin(), vec.end(), IsEqual(3), 5);
    for (int i : vec) std::cout << i << " ";
    std::cout << std::endl;
#endif
/*14.38*/
#ifdef NUM1438
    std::ifstream fin("../data/storyDataFile.txt");

    std::size_t quantity9 = 0, quantity10 = 0;
    BoundTest test9(1, 9);
    BoundTest test10(1, 10);

    for (std::string word; fin >> word;) {
        if (test9(word)) ++quantity9;
        if (test10(word)) ++quantity10;
    }

    std::cout << quantity9 << ", " << quantity10 << std::endl;
#endif
/*14.39*/
#ifdef NUM1439

#endif
/*14.40*/
#ifdef NUM1440
    vector<string> vec{"fox", "jumps", "over", "quick", "red",
                       "red", "slow",  "the",  "turtle"};
    biggies(vec, 4);
#endif
/*14.41*/
#ifdef NUM1441
    cout <<"lambda是通过匿名的函数对象来实现的，因此我们可以把lambda看作是对函数对象在使用方式上进行的简化。"
        "当代码需要一个简单的函数，并且这个函数并不会在其他地方被使用时，就可以使用lambda来实现，"
        "此时它所起的作用类似于匿名函数。但如果这个函数需要多次使用，并且它需要保存某些状态的话，使用函数对象更合适一些。"<<endl;
#endif
/*14.42*/
#ifdef NUM1442
    using std::placeholders::_1;
    std::vector<int> ivec{1, 111, 1111, 11111};
    int count = std::count_if(ivec.cbegin(), ivec.cend(),
                              std::bind(std::greater<int>(), _1, 1024));
    std::cout << count << std::endl;

    std::vector<std::string> svec{"pooh", "pooh", "pezy", "pooh"};
    auto found =
        std::find_if(svec.cbegin(), svec.cend(),
                     std::bind(std::not_equal_to<std::string>(), _1, "pooh"));
    std::cout << *found << std::endl;

    std::transform(ivec.begin(), ivec.end(), ivec.begin(),
                   std::bind(std::multiplies<int>(), _1, 2));
    for (int i : ivec) std::cout << i << " ";
    std::cout << std::endl;
#endif
/*14.43*/
#ifdef NUM1443
    auto data = {2, 3, 4, 5};
    int input;
    std::cin >> input;
    std::modulus<int> mod;
    auto predicator = [&](int i) { return 0 == mod(input, i); };
    auto is_divisible = std::any_of(data.begin(), data.end(), predicator);
    std::cout << (is_divisible ? "Yes!" : "No!") << std::endl;
#endif
/*14.44*/
#ifdef NUM1444
 while (true) {
        std::cout << "\npleasr enter: num operator num :\n";
        int n1, n2;
        std::string s;
        std::cin >> n1 >> s >> n2;

        std::cout << binops[s](n1, n2);
    }
#endif
/*14.45*/
#ifdef NUM1445
    Sales_data cp5("C++ Primer 5th", 4, 106.5);
    std::cout << cp5 << std::endl;
    std::cout << static_cast<std::string>(cp5) << std::endl;
    std::cout << static_cast<double>(cp5) << std::endl;
#endif
/*14.46*/
#ifdef NUM1446
    cout <<"不应该，这种操作极具误导性，应该把它们声明成explicit的，这样可以防止sales_data"
        " 在默写情况下被默认转换成string或double类型，防止隐式的类型转换。"<<endl;
#endif
/*14.47*/
#ifdef NUM1447
struct Integral {
    operator const int();   // 转换成const int类型，编译器一般忽略，没有意义
    operator int() const;   //转换成int类型时，操作符不会改变对象的状态
};
#endif
/*14.48*/
#ifdef NUM1448
    cout <<"定义bool类型转换的运算符是有用处的，但是必须是explicit，防止自动类型转换。"
#endif
/*14.49*/
#ifdef NUM1449
    Date date(12, 4, 2015);
    if (static_cast<bool>(date)) std::cout << date << std::endl;
#endif
/*14.50*/
#ifdef NUM1450
struct LongDouble {
    LongDouble(double = 0.0);
    operatordouble();
    operatorfloat();
};
    LongDouble ldObj;
    int ex1 = ldObj;    // error ambiguous: double or float?
    float ex2 = ldObj;  // legal
#endif
/*14.51*/
#ifdef NUM1451
    void calc(int);
    void calc(LongDouble);
    double dval;
    calc(dval); // which calc?
best viable function: void calc(int). cause class-type conversion is the lowest ranked.
review the order:
1.  exact match
2.  const conversion
3.  promotion
4.  arithmetic or pointer conversion
5.  class-type conversion
#endif
/*14.52*/
#ifdef NUM1452
struct LongDouble {
// member operator+ for illustration purposes; + is usually a nonmember LongDouble operator+(const SmallInt&); // 1
// other members as in 14.9.2 (p. 587)
};
LongDouble operator+(LongDouble&, double); // 2
SmallInt si;
LongDouble ld;
ld = si + ld;
ld = ld + si;
ld = si + ld; is ambiguous. ld = ld + si can use both 1 and 2, but 1 is more exactly. (in the 2, SmallInt need to convert to double)
#endif
/*14.53*/
#ifdef NUM1453
    SmallInt s1;
    double d = s1 + 3.14;
    ambiguous.
Fixed:
    SmallInt s1;
    double d = s1 + SmallInt(3.14);
    内置的operator+(int, double)是可行的，而3.14可以转换为int，然后再转换为SmallInt，所以SmallInt的成员operator+也是可行的。两者都需要进行类型转换，所以会产生二义性。改为：double d = s1 +Smallint(3.14);即可。
#endif


	return 0;
}
