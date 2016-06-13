#ifndef CHAPTER15_H
#define CHAPTER15_H

#include <iostream>
#include <string>
#include <memory>
#include <set>
using namespace std;




/*15.3*/
class Quote{
	friend bool operator !=(const Quote& lhs, const Quote &rhs);
public:
	Quote() {cout << "Default constructing Quote. "<<endl; }
	Quote(const string &b, double p): bookNo(b), price(p) {cout <<"Quote:constructor taking 2 parameters." <<endl;}

	Quote(const Quote &q): bookNo(q.bookNo), price(q.price){
		cout << "Quote:copy costructing\n";
	}
	Quote(Quote &&q) noexcept : bookNo(move(q.bookNo)), price(move(q.price)){
				cout << "Quote:move constructing\n"; 
			}
	Quote operator = (const Quote &rhs){
		if(*this != rhs){
			bookNo = rhs.bookNo;
			price = rhs.price;
		}
		cout << "Quote:copy=() \n";
		return *this;
	}
	
	Quote& operator =(Quote &rhs)noexcept{
		if(*this != rhs){
			bookNo = move(rhs.bookNo);
			bookNo = move(rhs.price);
		}
		cout << "Quote:move != \n"<<endl;
		return *this;
	}

	virtual Quote* clone()const& { return new Quote(*this); }
	virtual Quote* clone()&& { return new Quote(move(*this)); }

	string isbn()const { return bookNo; }
	virtual double net_price(size_t n) const { return n*price; }
	virtual void debug() const;

	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price;

};

bool inline operator !=(const Quote& lhs, const Quote& rhs){
	return lhs.bookNo != rhs.bookNo	&&	lhs.price  != rhs.price;
}

void Quote::debug() const{
	cout << "Data members of this class: \n" << "bookNo: " << isbn() << " "
			<< "price: " << this ->price <<" ";
}

/*15.3*/
double print_total(ostream &os, const Quote &item, size_t n){
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: "<< n << " total due: "<< ret << endl;
	return ret;
}

/*15.4*/
class Bulk_quote : public Quote{
public:
	Bulk_quote() { cout <<"default constructing Bulk_quote \n"<<endl;}
	Bulk_quote(const string &book, double p, size_t q, double d): Quote(book, p), min_qty(q), discount(d) { 
		cout << "Bulk_quote: constructor takes 4 parameters.\n"; 
	}
	Bulk_quote(const Bulk_quote &rhs): Quote(rhs){
		cout << "Bulk_quote: copy constructor.\n";
	}

	 //! move constructor
    Bulk_quote(Bulk_quote&& bq): Quote(move(bq)){
        cout << "Bulk_quote : move constructor\n";
    }

    //! copy =()
    Bulk_quote& operator =(const Bulk_quote& rhs){
        Quote::operator =(rhs);
        cout << "Bulk_quote : copy =()\n";

        return *this;
    }
    //! move =()
    Bulk_quote& operator =(Bulk_quote&& rhs) noexcept {
        Quote::operator =(move(rhs));
        cout << "Bulk_quote : move =()\n";

        return *this;
    }
	Bulk_quote* clone()const& { return new Bulk_quote(*this); }

	double net_price(size_t n) const override{
		return n * price * (n >= min_qty ? 1- discount : 1);
	}
	void debug() const override;
private:
	size_t min_qty;
	double discount;
};

void Bulk_quote::debug() const{
	Quote::debug();
	cout << "min_qty= " <<this->min_qty << " " <<"discount= " << this->discount <<" ";
}

/*15.7*/
class Limit_quote: public Quote{
public:
	Limit_quote();
	Limit_quote(const string &book, double p, size_t mq, double d): Quote(book, p), max_qty(mq), discount(d) { } 
	double net_price(size_t n)const override{
		if(n <= max_qty)
			return n * price * (1 - discount);
		else 
			return (n - max_qty) * price + max_qty * price * (1- discount);
//		return n * price * (n <= max_qty ? 1 - discount : 1);
	}
	void debug() const override;
	Limit_quote* clone()const& { return new Limit_quote(*this); }
private:
	size_t max_qty;
	double discount;

};

void Limit_quote::debug() const{
	Quote::debug();
	cout << "max_qty= " <<this->max_qty << " " <<"discount= " << this->discount <<" ";
}

/*15.11*/
void print_debug(const Quote &q){
	q.debug();
}

/*15.13*/
class base
{
public:
   string name() { return basename; }
   virtual void print(ostream &os) { os << basename; }
   //print用来输出基类的basename. 
private:
   string basename = "base\n";
};

class derived : public base
{
public:
   void print(ostream &os) { base::print(os); os << " derived\n " << i; }
private:
   int i;
};

/*15.15*/
class Disc_quote : public Quote{
public:
	Disc_quote() = default;
	Disc_quote(const string &b, double p, size_t q, double d): Quote(b, p), quantity(q), discount(d){ }
	virtual double net_price(size_t n)const override = 0;
protected:
	size_t quantity;
	double discount;
};

class Bulk_quote1 : public Disc_quote{
public:
	Bulk_quote1() = default;
	Bulk_quote1(const string &b, double p, size_t q, double dis):Disc_quote(b, p, q, dis){ }
	double net_price(size_t n) const override;
	void debug() const override;
};

double Bulk_quote1::net_price(size_t n) const{
	return n * price * (n >= quantity ? 1-discount : 1);
} 
void Bulk_quote1::debug() const{
	Quote::debug();
	cout << "min_qty= " << quantity <<" " <<"discount= " << discount<< " ";
}

/*15.16*/
class Limit_quote_16: public Disc_quote{
public:
	Limit_quote_16() = default;
	Limit_quote_16(const string &book, double p, size_t max, double d): Disc_quote(book, p, max, d) { }
	double net_price(size_t n)const override{
		if(n <= quantity)
			return n * price * (1 - discount);
		else 
			return (n - quantity) * price + quantity * price * (1- discount);
	}
	void debug() const override;
};

void Limit_quote_16::debug() const{
	Quote::debug();
	cout << "max_qty= " <<this->quantity << " " <<"discount= " << this->discount <<" ";
}

/*15.18*/
class Base
{
public:
    void pub_mem();   // public member
protected:
    int prot_mem;     // protected member
private:
    char priv_mem;    // private member
};

struct Pub_Derv     : public    Base{
    void memfcn(Base &b) { b = *this; }
};

struct Priv_Derv    : private   Base{
    void memfcn(Base &b) { b = *this; }
};

struct Prot_Derv    : protected Base{
    void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Public      : public Pub_Derv{
    void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Private     : public Priv_Derv{
    //void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Protected   : public Prot_Derv{
    void memfcn(Base &b) { b = *this; }
};

/*15.21*/
class Shape{
public:
	typedef pair<double, double> Coordinate;
	Shape() = default;
	Shape(const string& n): name(){ }
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual ~Shape() = default;
private:
	string name;
};

class Rectangle : public Shape{
public:
	Rectangle() = default;
	Rectangle(const string &n, const Coordinate &a, const Coordinate &b, 
			const Coordinate &c, const Coordinate &d): Shape(n), a(a), b(b), c(c), d(d){}
	double area() const;
	~Rectangle() = default;
protected:
	Coordinate a;
	Coordinate b;
	Coordinate c;
	Coordinate d;

};

class Square : public Rectangle{
public:
	Square() = default;
	Square(const string &n, const Coordinate &a, const Coordinate &b, 
			const Coordinate &c, const Coordinate &d): Rectangle(n, a, b, c, d){}
	double area() const;
	~Square() = default;
};

/*15.23*/
class Base_23{
public:
	virtual int fcn(){ cout << "Base::fcn()\n"; return 0; }
};

class D1: public Base_23{
public:
	int fcn() override {cout << "D1::fcn()\n"; return 0;}
	virtual void f2() {cout << "D1::f2()\n"; }
};

class D2 : public D1{
public:
	int fcn(int);
	int fcn() override{ cout << "D2::fcn()\n"; return 0;}
	void f2() override{ cout << "D2::f2()\n"; }
};

/*15.27*/
class Bulk_quote_27 : public Disc_quote{
public:
    Bulk_quote_27() {cout << "default constructing Bulk_quote\n"; }

    /*
    Bulk_quote(const string& b, double p, size_t q, double disc) :
        Disc_quote(b,p,q,disc) { cout << "Bulk_quote : constructor taking 4 parameters\n"; }
    */
    using Disc_quote::Disc_quote;

    //! copy constructor
    Bulk_quote_27(const Bulk_quote_27& bq) : Disc_quote(bq) { cout << "Bulk_quote_27 : copy constructor\n"; }

    //! move constructor
    Bulk_quote_27(Bulk_quote_27&& bq) : Disc_quote(move(bq))    {
        cout << "Bulk_quote_27 : move constructor\n";
    }

    //! copy =()
    Bulk_quote_27& operator =(const Bulk_quote_27& rhs){
        Disc_quote::operator =(rhs);
        cout << "Bulk_quote_27 : copy =()\n";
        return *this;
    }

    //! move =()
    Bulk_quote_27& operator =(Bulk_quote_27&& rhs){
        Disc_quote::operator =(move(rhs));
        cout << "Bulk_quote : move =()\n";
        return *this;
    }

	Bulk_quote_27* clone()const& { return new Bulk_quote_27(*this); }

    double net_price(size_t n) const override;
    void  debug() const override;

    ~Bulk_quote_27() override    {
        cout << "destructing Bulk_quote\n";
    }
};

double Bulk_quote_27::net_price(size_t n) const{
    return n * price * ( n >= quantity ? 1 - discount : 1);
}

void Bulk_quote_27::debug() const{
    cout //<< "data members of this class:\n"
              << "min_qty= " << quantity << " "
              << "discount= " << this->discount<< " \n";
}

/*15.30*/
class Basket{
public:
    //! copy verison
    void add_item(const Quote& sale){ 
    items.insert(shared_ptr<Quote>(sale.clone())); }
    //! move version
    void add_item(Quote&& sale){ 
    items.insert(shared_ptr<Quote>(move(sale).clone())); }
    double total_receipt(ostream& os) const;
private:
    //! function to compare needed by the multiset member
    static bool compare(const shared_ptr<Quote>& lhs,
                        const shared_ptr<Quote>& rhs){ 
    	return lhs->isbn() < rhs->isbn(); 
    }

    //! hold multiple quotes, ordered by the compare member
    multiset<shared_ptr<Quote>, decltype(compare)*> items{compare};
};

double Basket::total_receipt(ostream &os) const{
    double sum = 0.0;
    for(auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)){
        //!  ^^^^^^^^^^^^^^^^^^^^^^^^^^^
        //! @note   this increment moves iter to the first element with key
        //!         greater than  *iter.
        sum += print_total(os, **iter, items.count(*iter));
    }                                   //! ^^^^^^^^^^^^^ using count to fetch
                                        //! the number of the same book.
    os << "Total Sale: " << sum << endl;
    return sum;
}


#endif
