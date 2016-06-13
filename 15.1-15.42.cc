#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include "Chapter15.h"
using namespace std;
#define NUM1530

int main(){
/*15.1*/
#ifdef NUM151
	cout << "基类的虚成员希望派生类定义自己的版本。一般的基类都会定义虚函数，即使不做任何实际操作。"<<endl;
#endif
/*15.2*/
#ifdef NUM152
	cout<<"private成员允许基类和友元类访问,派生类不能访问；派生类有权访问protested成员，但是禁止其他成员访问，"<<endl;
#endif
/*15.3*/
#ifdef NUM153
	Quote basic( "a0-201-54848-8", 45);
	print_total(cout, basic, 20);	
#endif
/*15.4*/
#ifdef NUM154
	cout << "(a)不正确，从自己本身派生. (b)这是定义而非声明. (c)派生类的声明包含派生名但不包含派生列表."<<endl;
#endif
/*15.5*/
#ifdef NUM155
	cout <<"见Chapter15.h"<<endl;
#endif
/*15.6*/
#ifdef NUM156
	Quote basic( "0-201-54848-8", 45);
	print_total(cout, basic, 20);	
	
	Bulk_quote bulk("0-201-54848-8", 45, 15, 0.2);
	print_total(cout, bulk, 20); 
#endif
/*15.7*/
#ifdef NUM157
	Quote basic( "0-201-54848-8", 45);
	print_total(cout, basic, 30);	
	
	Limit_quote  lq("0-201-54848-8", 45, 20, 0.2);
	print_total(cout, lq, 30); 
#endif
/*15.15*/
#ifdef NUM158
	cout << "静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型."
		"动态类型则是表达式表示的内存中的对象的类型.动态类型直到运行时才可知."<<endl;
#endif
/*15.9*/
#ifdef NUM159
	cout <<"指向基类的指针和引用的静态类型都不同于它的动态类型。"<<endl;
#endif
/*15.10*/
#ifdef NUM1510
	cout<<"因为ifstream继承于istream, 所以我们能够像使用cin一样使用ifstream对象."<<endl;
#endif
/*15.11*/
#ifdef NUM1511
	Quote q("aaa", 10.60);
	Bulk_quote bq("bbb",111, 10, 0.3);
	Limit_quote lq("ccc",222,10,0.3);

    /** @note   Not dynamic binding!
		编译器在编译阶段就已经直到r所指的对象。结果时基类对象的虚函数被调用.
     */
    Quote& r = q;
    r.debug();
	cout << "\n";
    r = bq;
    r.debug();
	cout << "\n";
    r = lq;
    r.debug();
	cout << "\n";

    cout << "====================\n";
    /** @note   dynamic binding!
		print_debug编译时，编译器单独对每一个进行编译。编译器并不知道参数q所指向的对象。
		由此，编译器将这一判断留到运行时，即动态绑定。
		一旦动态绑定进行，派生类中对应的虚函数被调用。
     */
    print_debug(q);
	cout << "\n";
    print_debug(lq);
	cout << "\n";
    print_debug(bq);
	cout << "\n";	
#endif
/*15.12*/
#ifdef NUM1512
	cout <<"可以，override意味着从写在基类中同名的虚函数。final意味着防止派生类重写虚函数。"<<endl;	
#endif
/*15.13*/
#ifdef NUM1513
	cout << "派生类中的print有问题，试图调用基类的print函数，但是省略了作用域符号::,所以将陷入无限递归."
			"修改见Chapter15.h"<<endl;
	derived de;
	de.print(cout);
#endif
/*15.14*/
#ifdef NUM1514
	base bobj;
    base *bp1 = &bobj;
    base &br1 = bobj;
    derived dobj;
    base *bp2 = &dobj;
    base &br2 = dobj;
    //! a.  this is an object, so compile time.
    //bobj.print(cout);

    //! b.  this is an object, so compile time.
    //dobj.print(cout);

    //! c.  function name is not virtual , so no dynamic
    //!     binding happens.so conpile time
    //cout << bp1->name();

    //! d.  function name is not virtual , so no dynamic
    //!     binding happens.so conpile time
    //cout << bp2->name();

    //! e.  run time
    //br1.print(cout);

    //! f.  run time
    br2.print(cout);	
#endif
/*15.15*/
#ifdef NUM1515
	cout <<"见Chapter15.h"<<endl;
#endif
/*15.16*/
#ifdef NUM1516
	Limit_quote_16 lq("0-201-54848-8", 45, 20, 0.2);
	print_total(cout, lq, 20);
#endif
/*15.17*/
#ifdef NUM1517
	Disc_quote d;
#endif
/*15.18*/
#ifdef NUM1518
	Pub_Derv d1;
    Base *p = &d1;             //合法

    Priv_Derv d2;				
    //p = &d2;					//不合法

    Prot_Derv d3;
    //p = &d3;					//不合法

    Derived_from_Public dd1;
    p = &dd1;					//合法

    Derived_from_Private dd2;	
    //p =& dd2;					//不合法

    Derived_from_Protected dd3;
    //p = &dd3;					//不合法
	cout << "只有第1、4是正确的，在用户代码中，派生类向基类的转换(指针)"
		"只有当D公有的继承B时，用户代码才能使用派生类向基类转换."<<endl;
#endif
/*15.19*/
#ifdef NUM1519
	cout << "因为转换发生在函数中，关于书中的第二条规则: "
		"不论D以什么方式继承B，D的成员函数和友元函数都能使用派生类向基类的转换. 所以:"
	"所有继承于Base的类Pub_Derv, Priv_Derv, Prot_Derv都可以转换."
	"Derived_from_Public, Derived_from_Protected这两个类也可以转换两次得到."<<endl;
#endif
/*15.20*/
#ifdef NUM1520
	cout << "见15.18"<<endl;
#endif
/*15.21*/
#ifdef NUM1521
	cout <<"见Chapter15.h"<<endl;
#endif
/*15.23*/
#ifdef NUM1523
	Base_23 bobj;
	D1 d1obj;
	D2 d2obj;
    Base_23 *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
    bp1->fcn(); //虚调用，将在运行时调用Base_32::fcn()
    bp2->fcn(); //虚调用，运行时调用D1::fcn 
    bp3->fcn(); //虚调用， 运行时调用 D2::fcn   
    D1 *d1p = &d1obj; D2 *d2p = &d2obj;

    //bp2->f2();    //Base_32没有f2()的成员
    d1p->f2();    //虚调用，运行时调用 D1::f2() 
    d2p->f2();    //虚调用，运行时调用 D2::f2() 
#endif
/*15.24*/
#ifdef NUM1524
	cout<<"基类需要虚析构函数，在这些类完成动态绑定的同时，通过调用正确的析构函数来执行销毁操作."<<endl;
#endif
/*15.25*/
#ifdef NUM1525
	cout <<"会产生编译错误"          
	"因为Bulk_quote中也有默认构造函数,而这个构造函数的状态是由Disc_quote的默认构造函数决定的;"
	"Bulk_quote删除了默认构造函数,同时存在另一个4个参数的构造函数,所以编译器也不会再合成默认构造函数"<<endl;
#endif
/*15.26*/
#ifdef NUM1526
	Bulk_quote bq1;
	Bulk_quote bq2("0-201-82470-1", 45, 3, 0.3);
	bq2 = move(bq2);
	print_total(cout, bq2, 20);
#endif
/*15.27*/
#ifdef NUM1527
	Bulk_quote bq("sss",20.0,2,0.3);
#endif
/*15.218*/
#ifdef NUM1528
	 /**
     *  outcome == 9090
     */
    vector<Quote> v;
    for(unsigned i =1; i != 10; ++i)
        v.push_back(Bulk_quote_27("sss", i * 10.1, 10, 0.3));

    double total = 0;
    for (const auto& b : v)
    {
        total += b.net_price(20);
    }
    cout << total << endl;

    cout << "======================\n\n";

    /**
     *   outccome == 6363
     */
    vector<shared_ptr<Quote>> pv;    //多态

    for(unsigned i =1; i != 10; ++i)
        pv.push_back(make_shared<Bulk_quote_27>(Bulk_quote_27("sss", i * 10.1, 10, 0.3)));

    double total_p = 0;
    for (auto p : pv)
    {
        total_p +=  p->net_price(20);
		print_total(cout, *p, 20);
    }
    cout << total_p << endl;

#endif
/*15.29*/
#ifdef NUM1529
    //答案不一样 因为v保存的全部是Quote的对象(静态类型) 也就是说Bulk_quote强行转换成了Quote
    //而pv保存的是(动态类型) 转换的仅是指针
#endif
/*15.30*/
#ifdef NUM1530
	Basket basket;
    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(Bulk_quote("Bible",20.6,20,0.3));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(Bulk_quote("C++Primer",30.9,5,0.4));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(Quote("CLRS",40.1));

    ofstream log("log.txt",ios_base::app|ios_base::out);

    basket.total_receipt(log);
#endif
/*15.31*/
#ifdef NUM1531

#endif
/*15.32*/
#ifdef NUM1532

#endif
/*15.33*/
#ifdef NUM1533

#endif
/*15.34*/
#ifdef NUM1534

#endif
/*15.35*/
#ifdef NUM1535

#endif
/*15.36*/
#ifdef NUM1536

#endif
/*15.37*/
#ifdef NUM1537

#endif
/*15.38*/
#ifdef NUM1538

#endif
/*15.315*/
#ifdef NUM15315

#endif
/*15.40*/
#ifdef NUM1540

#endif
	return 0;
}
