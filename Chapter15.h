#ifndef CHAPTER15_H
#define CHAPTER15_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
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
//	virtual Quote* clone()&& { return new Quote(move(*this)); }

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
//	Bulk_quote_27* clone()&& { return new Bulk_quote_27(move(*this)); }

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
//    void add_item(const Quote& sale){ 
//    items.insert(shared_ptr<Quote>(sale.clone())); }
	void add_item(const shared_ptr<Quote> &sale){ items.insert(sale);  }
    //! move version
//    void add_item(Quote&& sale){ 
//    items.insert(shared_ptr<Quote>(move(sale).clone())); }
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
        sum += print_total(os, **iter, items.count(*iter));
    }                                   //! ^^^^^^^^^^^^^ using count to fetch
                                        //! the number of the same book.
    os << "Total Sale: " << sum << endl;
    return sum;
}

//15.35
// forward declaration needed for friend declaration in StrBlob
class StrBlobPtr;

class StrBlob{
	friend class StrBlobPtr;
public:
    typedef vector<string>::size_type size_type;

	// constructors
    StrBlob() : data(make_shared<vector<string>>()) { }
    StrBlob(initializer_list<string> il);

	// size operations
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const string &t) { data->push_back(t); }
    void pop_back();

    // element access
    string& front();
    string& back();

	// interface to StrBlobPtr
	StrBlobPtr begin();  // can't be defined until StrBlobPtr is
    StrBlobPtr end();
private:
    shared_ptr<vector<string>> data; 
    // throws msg if data[i] isn't valid
    void check(size_type i, const string &msg) const;
};

// constructor
inline
StrBlob::StrBlob(initializer_list<string> il): 
              data(make_shared<vector<string>>(il)) { }

// StrBlobPtr throws an exception on attempts to access a nonexistent element 
class StrBlobPtr{
	friend bool eq(const StrBlobPtr&, const StrBlobPtr&);
public:
    StrBlobPtr(): curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) { }

    //! newly overloaded why?
    StrBlobPtr(const StrBlob &a, const size_t sz = 0) : wptr(a.data), curr(sz) { }

    string& deref() const;
    StrBlobPtr& incr();       // prefix version
    StrBlobPtr& decr();       // prefix version
private:
    // check returns a shared_ptr to the vector if the check succeeds
    shared_ptr<vector<string>> 
        check(size_t, const string&) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    weak_ptr<vector<string>> wptr;  
    size_t curr;      // current position within the array
};

inline
string& StrBlobPtr::deref() const{
    auto p = check(curr, "dereference past end"); 
    return (*p)[curr];  // (*p) is the vector to which this object points
}

inline
shared_ptr<vector<string>> 
StrBlobPtr::check(size_t i, const string &msg) const{
    auto ret = wptr.lock();   // is the vector still around?
    if (!ret)
        throw runtime_error("unbound StrBlobPtr");

    if (i >= ret->size()) 
        throw out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}

// prefix: return a reference to the incremented object
inline
StrBlobPtr& StrBlobPtr::incr(){
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;       // advance the current state
    return *this;
}

inline
StrBlobPtr& StrBlobPtr::decr(){
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;       // move the current state back one element}
    check(-1, "decrement past begin of StrBlobPtr");
    return *this;
}

// begin and end members for StrBlob
inline
StrBlobPtr
StrBlob::begin() {
	return StrBlobPtr(*this);
}

inline
StrBlobPtr
StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
    return ret; 
}

// named equality operators for StrBlobPtr
inline
bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs){
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
	// if the underlying vector is the same 
	if (l == r) 
		// then they're equal if they're both null or 
		// if they point to the same element
		return (!r || lhs.curr == rhs.curr);
	else
		return false; // if they point to difference vectors, they're not equal
}

inline
bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs){
	return !eq(lhs, rhs); 
}

class QueryResult;
/**
 * @brief The TextQuery class using StrBlob
 */
class TextQuery{
public:
    typedef StrBlob::size_type line_no;
    //! constructor
    TextQuery(ifstream& fin);
    //! query operation
    QueryResult query(const string&) const;
private:
    //! data members
    StrBlob file;
    map<string, shared_ptr<set<line_no>>> wordMap;
};

/**
 * @brief constructor using StrBlob.
 */
TextQuery::TextQuery(ifstream &fin) : file(StrBlob()), wordMap(map<string,shared_ptr<set<line_no>>>()){
    string line;
    //! each line
    while(getline(fin, line))
    {
        file.push_back(line);
        int n = file.size() - 1;    //! the current line number

        //! each word
        stringstream lineSteam(line);
        string word;
        while(lineSteam >> word) {
            shared_ptr<set<line_no>>&                          
                           sp_lines = wordMap[word];
            //! if null
            if(!sp_lines)  {
                sp_lines.reset(new set<line_no>);
            }
            sp_lines->insert(n);
        }
    }
}

/**
 * @brief do a query opertion and return QueryResult object.
 */
QueryResult
TextQuery::query(const string &sought) const{
    //! dynamicaly allocated set used for the word does not appear.
    static shared_ptr<set<line_no>> noData(new set<line_no>);

    //! fetch the iterator to the matching element in the map<word, lines>.
    //map<string, shared_ptr<set<index_Tp>>>::const_iterator
    auto iter = wordMap.find(sought);
    if(iter == wordMap.end())
        return QueryResult(sought, noData, file);
    else
        return QueryResult(sought, iter->second, file);
}

class QueryResult{
    friend ostream& print(ostream&, const QueryResult&);

public:
	QueryResult(string s,
		shared_ptr<set<TextQuery::line_no>> l,
		shared_ptr<vector<string>> f) :
		sought(s), lines(l), file(f){}

	set<TextQuery::line_no>::iterator begin(){ return lines->begin(); }
	set<TextQuery::line_no>::iterator end(){ return lines->end(); }
	shared_ptr<vector<string>> get_file(){ return file; }

private:
    string sought;
    shared_ptr<set<TextQuery::line_no>> lines;
    shared_ptr<vector<string>> file;
};

ostream& print(ostream&, const QueryResult&);

ostream& print(ostream &os, const QueryResult &qr)
{
    os <<"The result of your query "<< qr.sought <<" is: \n";
    for (const auto &index: *qr.lines)
        os << "\t(line " << index + 1 << ")"
           << *(qr.file->begin() + index) << "\n";
    return os;
}

/**
 * @brief abstract class acts as a base class for all concrete query types
 *        all members are private.
 */
class Query_base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no; //  used in the eval function
    virtual ~Query_base() = default;

private:
    //! returns QueryResult that matches this query
    virtual QueryResult eval(const TextQuery&) const = 0;

    //! a string representation of this query
    virtual string rep() const = 0;
};

/**
 * @brief The WordQuery class
 *The only class that actually performs a query on the given TextQuery object.
 *No public members defined in this class. All operation are through the friend
 *class Query.
 */
class WordQuery : public Query_base{
    //! class Query uses the WordQuery constructor
    friend class Query;
    WordQuery(const string& s): query_word(s)    {
        cout << "WordQuery::WordQuery(" + s + ")\n";
    }


    //! virtuals:
    QueryResult eval(const TextQuery& t) const override
    {   return t.query(query_word); }
    string rep() const override    {
        cout << "WodQuery::rep()\n";
        return query_word;
    }
    string query_word;
};

/**
 * @brief interface class to manage the Query_base inheritance hierachy
 */
class Query
{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    //! build a new WordQuery
    Query(const string& s) : q(new WordQuery(s)) {
        cout << "Query::Query(const string& s) where s="+s+"\n";
    }

    //! interface functions: call the corresponding Query_base operatopns
    QueryResult eval(const TextQuery& t) const { return q->eval(t); }
    string rep() const
    {
        cout << "Query::rep() \n";
        return q->rep();
    }

private:
    //! constructor only for friends
    Query(shared_ptr<Query_base> query) : q(query)    {
        cout << "Query::Query(shared_ptr<Query_base> query)\n";
    }
    shared_ptr<Query_base> q;
};

inline ostream& operator << (ostream& os, const Query& query){
    //! make a virtual call through its Query_base pointer to rep();
    return os << query.rep();
}



/**
 * @brief The BinaryQuery class
 *An abstract class holds data needed by the query types that operate on two operands
 */
class BinaryQuery : public Query_base{
protected:
    BinaryQuery(const Query&l, const Query& r, string s):
        lhs(l), rhs(r), opSym(s)    {
        cout << "BinaryQuery::BinaryQuery()  where s=" + s + "\n";
    }

    //! @note:  abstract class: BinaryQuery doesn't define eval

    string rep() const override    {
        cout << "BinaryQuery::rep()\n";
        return "(" + lhs.rep() + " "
                   + opSym + " "
                + rhs.rep() + ")";
    }
    Query lhs, rhs;
    string opSym;
};

class OrQuery :public BinaryQuery{
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query& left, const Query& right):
        BinaryQuery(left, right, "|")    {
        cout << "OrQuery::OrQuery\n";
    }

    QueryResult eval(const TextQuery& )const override;
};

inline Query operator|(const Query &lhs, const Query& rhs){
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const{
    QueryResult right = rhs.eval(text), left= lhs.eval(text);

    //! copy the left-hand operand into the result set
    shared_ptr<set<line_no>> ret_lines =
            make_shared<set<line_no>>(left.begin(), left.end());

    //! inert lines from the right-hand operand
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(rep(),ret_lines,left.get_file());
}

/**
 * @brief The NotQuery class
 *
 *The ~ operator generates a NotQuery, which holds a Query,
 *which it negates.
 */
class NotQuery : public Query_base{
    friend Query operator~(const Query& operand);
    NotQuery(const Query& q): query(q)    {
        cout << "NotQuery::NotQuery()\n";
    }

    //! virtuals:
    string rep() const override {
        cout << "NotQuery::rep()\n";
        return "~(" + query.rep() + ")";
    }

    QueryResult eval(const TextQuery &) const override;
    Query query;
};

inline Query operator~(const Query& operand){
    return shared_ptr<Query_base>(new NotQuery(operand));
    //!    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //! note : There is an imlplicit conversion here.
    //!        The Query constructor that takes shared_ptr is not
    //!        "explicit", thus the compiler allows this conversion.
}

/**
 * @brief NotQuery::eval
 * @return the lines not in its operand's result set
 */
QueryResult NotQuery::eval(const TextQuery &text) const{
    //! virtual call to eval through the Query operand
    QueryResult result = query.eval(text);

    //! start out with an empty result set
    shared_ptr<set<line_no>>
            ret_lines = make_shared<set<line_no>>();

    set<TextQuery::line_no>::iterator
            begin = result.begin(),
            end   = result.end();

    StrBlob::size_type sz = result.get_file().size();

    for(size_t n = 0; n != sz; ++n)    {
        if(begin == end || *begin != n)
            ret_lines->insert(n);
        else if (begin != end)
            ++begin;
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}

class AndQuery : public BinaryQuery{
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query& left, const Query& right):
        BinaryQuery(left,right, "&")    {
        cout << "AndQuery::AndQuery()\n";
    }

    //! @note: inherits rep and define eval

    QueryResult eval(const TextQuery &) const override;
};

inline Query operator& (const Query& lhs, const Query& rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

/**
 * @brief AndQuery::eval
 * @return  the intersection of its operands' result sets
 */
QueryResult AndQuery::eval(const TextQuery &text) const{
    //! virtual calls through the Query operands to get result sets for the operands
    QueryResult left = lhs.eval(text), right = rhs.eval(text);

    //! set to hold the intersection of the left and right
    shared_ptr<set<line_no>>
                   ret_lines = make_shared<set<line_no>>();

    //! writes the intersection of two ranges to a destination iterator
    set_intersection(left.begin(), left.end(),
                          right.begin(), right.end(),
                          inserter(*ret_lines, ret_lines->begin()));

    return QueryResult(rep(), ret_lines, left.get_file());
}

//15.42  
class QueryHistory
{
public:
	Query& operator[](size_t n)	{
		return *(query_vec[n]);
	}

	//return the assigned number of the  new query
	size_t add_query(const Query&);
private:
	vector<shared_ptr<Query>> query_vec;
};

size_t QueryHistory::add_query(const Query &query){
	shared_ptr<Query> p = make_shared<Query>(query);
	query_vec.push_back(p);
	return query_vec.size() - 1;
}
#endif
