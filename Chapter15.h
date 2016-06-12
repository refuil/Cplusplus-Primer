#ifndef CHAPTER15_H
#define CHAPTER15_H

#include <iostream>
#include <string>
using namespace std;

/*15.3*/
class Quote{
public:
	Quote() = default;
	Quote(const string &b, double p): bookNo(b), price(p) {}
	string isbn()const { return bookNo; }
	virtual double net_price(size_t n) const { return n*price; }
	virtual void debug() const;

	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price;

};

void Quote::debug() const{
	cout << "Data members of this class: \n" << "bookNo: " << isbn() << " "
			<< "price: " << this ->price <<" ";
}

/*15.4*/
class Bulk_quote : public Quote{
public:
	Bulk_quote() = default;
	Bulk_quote(const string &book, double p, size_t q, double d): Quote(book, p), min_qty(q), discount(d) { }
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
private:
	size_t max_qty;
	double discount;

};

void Limit_quote::debug() const{
	Quote::debug();
	cout << "max_qty= " <<this->max_qty << " " <<"discount= " << this->discount <<" ";
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





#endif
