//main.cc
#ifndef CHAPTER_10_H
#define CHAPTER_10_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <algorithm>
#include <exception>
using namespace std;

//14.2
class Sales_data {
    friend istream& operator>>(istream&, Sales_data&);       // input
    friend ostream& operator<<(ostream&, const Sales_data&); // output
    friend Sales_data operator+(const Sales_data&, const Sales_data&); // addition
public:
    Sales_data(const string& s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(n * p)  {  }
    Sales_data() : Sales_data("", 0, 0.0f) {}
    Sales_data(const string& s) : Sales_data(s, 0, 0.0f) {}
    Sales_data(istream& is);

    Sales_data& operator=(const string&);                 //14.22
    Sales_data& operator+=(const Sales_data&); // compound-assignment
    string isbn() const { return bookNo; }
 
    explicit operator std::string() const { return bookNo; }       //14.45
    explicit operator double() const { return avg_price(); }       //14.45
private:
    inline double avg_price() const;

    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

istream& operator>>(istream&, Sales_data&);
ostream& operator<<(ostream&, const Sales_data&);
Sales_data operator+(const Sales_data&, const Sales_data&);

inline double Sales_data::avg_price() const{
    return units_sold ? revenue / units_sold : 0;
}

Sales_data::Sales_data(istream& is) : Sales_data(){
    is >> *this;
}

Sales_data& Sales_data::operator+=(const Sales_data& rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream& operator>>(istream& is, Sales_data& item){
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
        item.revenue = price * item.units_sold;
    else
        item = Sales_data();
    return is;
}
/*
istream&operator>>(istream& in, Sales_data& s)   //14.11
{
	double price;
	in >> s.bookNo>> s.units_sold>> price;
	s.revenue = s.units_sold * price;
	return in;
}
*/
ostream& operator<<(ostream& os, const Sales_data& item){
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " "
       << item.avg_price();
    return os;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs){
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

Sales_data& Sales_data::operator=(const string& isbn){     //14.22
    *this = Sales_data(isbn);
    return *this;
}

//14.5
class Book {  
	friend istream& operator>>(istream&, Book&);       // input
    friend ostream& operator<<(ostream&, const Book&); // output
    friend bool operator==(const Book&, const Book&);
    friend bool operator!=(const Book&, const Book&);
    friend bool operator<(const Book&, const Book&);
    friend bool operator>(const Book&, const Book&);
    friend Book operator+(const Book&, const Book&);
public:  
    Book() = default;  
    Book(unsigned no, string name, string author, string pubdate):no_(no), name_(name), author_(author), pubdate_(pubdate) { }  
    Book(istream &in) { in >> no_ >> name_ >> author_ >> pubdate_; }  
	Book& operator+=(const Book&);
private:  
    unsigned no_;  
    string name_;  
    string author_;  
    string pubdate_;  
    unsigned number_;
};  

istream& operator>>(istream&, Book&);       // input
ostream& operator<<(ostream&, const Book&); // output
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
bool operator<(const Book&, const Book&);
bool operator>(const Book&, const Book&);
Book operator+(const Book&, const Book&);


istream& operator>>(istream& in, Book& book){
    in >> book.no_ >> book.name_ >> book.author_ >> book.pubdate_ >>
        book.number_;
    if (!in) book = Book();
    return in;
}

ostream& operator<<(ostream& out, const Book& book){
    out << book.no_ << " " << book.name_ << " " << book.author_ << " "
        << book.pubdate_ << " " << book.number_ << endl;
    return out;
}

bool operator==(const Book& lhs, const Book& rhs){
    return lhs.no_ == rhs.no_;
}

bool operator!=(const Book& lhs, const Book& rhs){
    return !(lhs == rhs);
}

bool operator<(const Book& lhs, const Book& rhs){
    return lhs.no_ < rhs.no_;
}

bool operator>(const Book& lhs, const Book& rhs){
    return rhs < lhs;
}

Book& Book::operator+=(const Book& rhs){
    if (rhs == *this) this->number_ += rhs.number_;
    return *this;
}

Book operator+(const Book& lhs, const Book& rhs){
    Book book = lhs;
    book += rhs;
    return book;
}

//14.7
class String {
    friend ostream& operator<<(ostream&, const String&);
    friend istream& operator>>(istream&, String&);
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    friend bool operator<(const String&, const String&);
    friend bool operator>(const String&, const String&);
    friend bool operator<=(const String&, const String&);
    friend bool operator>=(const String&, const String&);
public:
    String() : String("") {}
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    String(String&&) noexcept;
    String& operator=(String&&) noexcept;
    ~String();

    void push_back(const char);

    char* begin() const { return elements; }
    char* end() const { return last_elem; }

    char& operator[](size_t n) { return elements[n]; }               //14.26
    const char& operator[](size_t n) const { return elements[n]; }   //14.26

    const char* c_str() const { return elements; }
    size_t size() const { return last_elem - elements; }
    size_t length() const { return size(); }
    size_t capacity() const { return cap - elements; }

    void reserve(size_t);
    void resize(size_t);
    void resize(size_t, char);
private:
    pair<char*, char*> alloc_n_copy(const char*, const char*);
    void range_initializer(const char*, const char*);
    void free();
    void reallocate();
    void alloc_n_move(size_t new_cap);
    void chk_n_alloc()    {
        if (first_free == cap) reallocate();
    }
private:
    char* elements;
    char* last_elem;
    char* first_free;
    char* cap;
    allocator<char> alloc;
};

ostream& operator<<(ostream&, const String&);
istream& operator>>(istream&, String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
bool operator<(const String&, const String&);
bool operator>(const String&, const String&);
bool operator<=(const String&, const String&);
bool operator>=(const String&, const String&);

ostream& operator<<(ostream& os, const String& lhs){
    os << lhs.c_str();
    return os;
}

istream& operator>>(istream& is, String& rhs){
    for (char c; (c = is.get()) != '\n';) {
        rhs.push_back(c);
    }
    return is;
}

bool operator==(const String& lhs, const String& rhs){
    return (lhs.size() == rhs.size() &&
            equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator!=(const String& lhs, const String& rhs){
    return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs){
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
}

bool operator>(const String& lhs, const String& rhs){
    return rhs < lhs;
}

bool operator<=(const String& lhs, const String& rhs){
    return !(rhs < lhs);
}

bool operator>=(const String& lhs, const String& rhs){
    return !(lhs < rhs);
}

String::String(const char* s){
    char* sl = const_cast<char*>(s);
    while (*sl) ++sl;
    range_initializer(s, ++sl);
}

String::String(const String& rhs){
    range_initializer(rhs.elements, rhs.first_free);
}

String& String::operator=(const String& rhs){
    auto newstr = alloc_n_copy(rhs.elements, rhs.first_free);
    free();
    elements = newstr.first;
    first_free = cap = newstr.second;
    last_elem = first_free - 1;
    return *this;
}

String::String(String&& s) noexcept : elements(s.elements), last_elem(s.last_elem), first_free(s.first_free),
                                      cap(s.cap){
    s.elements = s.last_elem = s.first_free = s.cap = nullptr;
}

String& String::operator=(String&& rhs) noexcept{
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        last_elem = rhs.last_elem;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.last_elem = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

String::~String(){
    free();
}

//===========================================================================
//
//      members
//
//===========================================================================

void String::push_back(const char c){
    chk_n_alloc();
    *last_elem = c;
    last_elem = first_free;
    alloc.construct(first_free++, '\0');
}

void String::reallocate(){
    auto newcapacity = size() ? 2 * (size() + 1) : 2;
    alloc_n_move(newcapacity);
}

void String::alloc_n_move(size_t new_cap){
    auto newdata = alloc.allocate(new_cap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size() + 1; ++i)
        alloc.construct(dest++, move(*elem++));
    free();
    elements = newdata;
    last_elem = dest - 1;
    first_free = dest;
    cap = elements + new_cap;
}

void String::free(){
    if (elements) {
        for_each(elements, first_free,
                      [this](char& c) { alloc.destroy(&c); });
        alloc.deallocate(elements, cap - elements);
    }
}

pair<char*, char*> String::alloc_n_copy(const char* b, const char* e){
    auto str = alloc.allocate(e - b);
    return {str, uninitialized_copy(b, e, str)};
}

void String::range_initializer(const char* first, const char* last){
    auto newstr = alloc_n_copy(first, last);
    elements = newstr.first;
    first_free = cap = newstr.second;
    last_elem = first_free - 1;
}

void String::reserve(size_t new_cap){
    if (new_cap <= capacity()) return;
    alloc_n_move(new_cap);
}

void String::resize(size_t count, char c){
    if (count > size()) {
        if (count > capacity()) reserve(count * 2);
        for (size_t i = size(); i != count; ++i) {
            *last_elem++ = c;
            alloc.construct(first_free++, '\0');
        }
    }
    else if (count < size()) {
        while (last_elem != elements + count) {
            --last_elem;
            alloc.destroy(--first_free);
        }
        *last_elem = '\0';
    }
}

void String::resize(size_t count){
    resize(count, ' ');
}

//14.16
class StrBlobPtr;
class ConstStrBlobPtr;

//=================================================================================
//
//      StrBlob - custom vector<string>
//
//=================================================================================

class StrBlob {
    using size_type = vector<string>::size_type;
    friend class ConstStrBlobPtr;
    friend class StrBlobPtr;
    friend bool operator==(const StrBlob&, const StrBlob&);
	friend bool operator!=(const StrBlob&, const StrBlob&);
	friend bool operator<(const StrBlob&, const StrBlob&);
	friend bool operator>(const StrBlob&, const StrBlob&);
	friend bool operator<=(const StrBlob&, const StrBlob&);
	friend bool operator>=(const StrBlob&, const StrBlob&);

public:
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il))    {
    }

    StrBlob(const StrBlob& sb) : data(make_shared<vector<string>>(*sb.data)) {}
    StrBlob& operator=(const StrBlob&);

    StrBlob(StrBlob&& rhs) noexcept : data(move(rhs.data)) {}
    StrBlob& operator=(StrBlob&&) noexcept;

    StrBlobPtr begin();
    StrBlobPtr end();

    ConstStrBlobPtr cbegin() const;
    ConstStrBlobPtr cend() const;

    string& operator[](size_t n);
    const string& operator[](size_t n) const;

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(const string& t) { data->push_back(t); }
    void push_back(string&& s) { data->push_back(move(s)); }

    void pop_back();
    string& front();
    string& back();
    const string& front() const;
    const string& back() const;
private:
    void check(size_type, const string&) const;
    shared_ptr<vector<string>> data;
};

bool operator==(const StrBlob&, const StrBlob&);
bool operator!=(const StrBlob&, const StrBlob&);
bool operator<(const StrBlob&, const StrBlob&);
bool operator>(const StrBlob&, const StrBlob&);
bool operator<=(const StrBlob&, const StrBlob&);
bool operator>=(const StrBlob&, const StrBlob&);


inline void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

inline string& StrBlob::front(){
    check(0, "front on empty StrBlob");
    return data->front();
}

inline string& StrBlob::back(){
    check(0, "back on empty StrBlob");
    return data->back();
}

inline const string& StrBlob::front() const{
    check(0, "front on empty StrBlob");
    return data->front();
}

inline const string& StrBlob::back() const{
    check(0, "back on empty StrBlob");
    return data->back();
}

inline void StrBlob::check(size_type i, const string& msg) const{
    if (i >= data->size()) throw out_of_range(msg);
}
inline string& StrBlob::operator[](size_t n){
    check(n, "out of range");
    return data->at(n);
}
inline const string& StrBlob::operator[](size_t n) const{
    check(n, "out_of_range");
    return data->at(n);
}
//=================================================================================
//
//      StrBlobPtr - custom iterator of StrBlob
//
//=================================================================================

class StrBlobPtr {
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator>(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);

public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob& s, size_t sz = 0) : wptr(s.data), curr(sz) {}

    const string &operator*() const;       //14.30
    const string *operator->() const;
    StrBlobPtr &operator++();             //14.27
    StrBlobPtr &operator--();
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
    StrBlobPtr &operator+=(size_t);
    StrBlobPtr &operator-=(size_t); 
    StrBlobPtr operator+(size_t) const;     //14.28
    StrBlobPtr operator-(size_t) const;

    string& deref() const;
    StrBlobPtr& incr();
    string& operator[](size_t n);                      //14.26
    const string& operator[](size_t n) const;
private:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

bool operator==(const StrBlobPtr&, const StrBlobPtr&);
bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
bool operator<(const StrBlobPtr&, const StrBlobPtr&);
bool operator>(const StrBlobPtr&, const StrBlobPtr&);
bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
bool operator>=(const StrBlobPtr&, const StrBlobPtr&);

inline string& StrBlobPtr::deref() const{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

inline StrBlobPtr& StrBlobPtr::incr(){
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

const string &StrBlobPtr::operator*() const{       //14.30
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}
const string *StrBlobPtr::operator->() const{
	return &this->operator*();
}
inline StrBlobPtr &StrBlobPtr::operator++() {
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

inline StrBlobPtr &StrBlobPtr::operator--() {
  --curr;
  check(curr, "decrement past begin of StrBlobPtr");
  return *this;
}

inline StrBlobPtr StrBlobPtr::operator++(int) {
  StrBlobPtr ret = *this;
  ++*this;
  return ret;
}

inline StrBlobPtr StrBlobPtr::operator--(int) {
  StrBlobPtr ret = *this;
  --*this;
  return ret;
}

inline StrBlobPtr &StrBlobPtr::operator+=(size_t n) {
  curr += n;
  check(curr, "increment past end of StrBlobPtr");
  return *this;
}

inline StrBlobPtr &StrBlobPtr::operator-=(size_t n) {
  curr -= n;
  check(curr, "increment past end of StrBlobPtr");
  return *this;
}

inline StrBlobPtr StrBlobPtr::operator+(size_t n) const {
  StrBlobPtr ret = *this;
  ret += n;
  return ret;
}

inline StrBlobPtr StrBlobPtr::operator-(size_t n) const {
  StrBlobPtr ret = *this;
  ret -= n;
  return ret;
}

inline shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string& msg) const{
    auto ret = wptr.lock();
    if (!ret) throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size()) throw out_of_range(msg);
    return ret;
}

inline string& StrBlobPtr::operator[](size_t n){
    auto p = check(n, "dereference out of range.");
    return (*p)[n];
}

inline const string& StrBlobPtr::operator[](size_t n) const{
    auto p = check(n, "dereference out of range.");
    return (*p)[n];
}
//=================================================================================
//
//      ConstStrBlobPtr - custom const_iterator of StrBlob
//
//=================================================================================
class ConstStrBlobPtr {
    friend bool operator==(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator!=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
	friend bool operator<(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
	friend bool operator>(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
	friend bool operator<=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
	friend bool operator>=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);

public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob& s, size_t sz = 0) : wptr(s.data), curr(sz) {}

    const string& deref() const;
    ConstStrBlobPtr& incr();

    ConstStrBlobPtr &operator++();                  //14.27
    ConstStrBlobPtr &operator--();
    ConstStrBlobPtr operator++(int);
    ConstStrBlobPtr operator--(int);
    ConstStrBlobPtr &operator+=(size_t);
    ConstStrBlobPtr &operator-=(size_t);
    ConstStrBlobPtr operator+(size_t) const;        //14.28
    ConstStrBlobPtr operator-(size_t) const;
    const string& operator[](size_t n) const;       //14.26
	const string& operator*() const;
	const string* operator->() const;  //14.30

private:
    shared_ptr<vector<string>> check(size_t, const string&) const;

    weak_ptr<vector<string>> wptr;
    size_t curr;
};

inline const string& ConstStrBlobPtr::deref() const{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

inline ConstStrBlobPtr& ConstStrBlobPtr::incr(){
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

inline const string& ConstStrBlobPtr::operator*() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

inline const string *ConstStrBlobPtr::operator->() const {  //14.30
  return &this->operator*();
}

inline ConstStrBlobPtr &ConstStrBlobPtr::operator++() {
  check(curr, "increment past end of ConstStrBlobPtr");
  ++curr;
  return *this;
}

inline ConstStrBlobPtr &ConstStrBlobPtr::operator--() {
  --curr;
  check(-1, "decrement past begin of ConstStrBlobPtr");
  return *this;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator++(int) {
  ConstStrBlobPtr ret = *this;
  ++*this;
  return ret;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator--(int) {
  ConstStrBlobPtr ret = *this;
  --*this;
  return ret;
}

inline ConstStrBlobPtr &ConstStrBlobPtr::operator+=(size_t n) {
  curr += n;
  check(curr, "increment past end of ConstStrBlobPtr");
  return *this;
}

inline ConstStrBlobPtr &ConstStrBlobPtr::operator-=(size_t n) {
  curr -= n;
  check(curr, "increment past end of ConstStrBlobPtr");
  return *this;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator+(size_t n) const {
  ConstStrBlobPtr ret = *this;
  ret += n;
  return ret;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator-(size_t n) const {
  ConstStrBlobPtr ret = *this;
  ret -= n;
  return ret;
}

inline shared_ptr<vector<string>>
ConstStrBlobPtr::check(size_t i, const string& msg) const{
    auto ret = wptr.lock();
    if (!ret) throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size()) throw out_of_range(msg);
    return ret;
}

inline const string& ConstStrBlobPtr::operator[](size_t n) const{
    auto p = check(n, "dereference out of range.");
    return (*p)[n];
}

bool operator==(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator!=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator<(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator>(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator<=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator>=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
//==================================================================
//
//      operators
//
//==================================================================

bool operator==(const StrBlob& lhs, const StrBlob& rhs){
    return *lhs.data == *rhs.data;
}

bool operator!=(const StrBlob& lhs, const StrBlob& rhs){
    return !(lhs == rhs);
}

bool operator<(const StrBlob& lhs, const StrBlob& rhs){
	return lexicographical_compare(lhs.data->begin(), lhs.data->end(), rhs.data->begin(), rhs.data->end());
}

bool operator>(const StrBlob& lhs, const StrBlob& rhs){
	return rhs < lhs;
}
bool operator<=(const StrBlob& lhs, const StrBlob& rhs){
	return !(lhs > rhs);
}
bool operator>=(const StrBlob& lhs, const StrBlob& rhs){
	return  !(lhs < rhs);
}

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs){
    return lhs.curr == rhs.curr;
}

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs){
    return !(lhs == rhs);
}

bool operator<(const StrBlobPtr& x, const StrBlobPtr& y){
	    return x.curr < y.curr;
}

bool operator>(const StrBlobPtr& x, const StrBlobPtr& y){
	    return x.curr > y.curr;
}

bool operator<=(const StrBlobPtr& x, const StrBlobPtr& y){
	    return x.curr <= y.curr;
}

bool operator>=(const StrBlobPtr& x, const StrBlobPtr& y){
	    return x.curr >= y.curr;
}

bool operator==(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs){
    return lhs.curr == rhs.curr;
}

bool operator!=(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs){
    return !(lhs == rhs);
}

bool operator<(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs){
	    return lhs.curr < rhs.curr;
}

bool operator>(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs){
	    return lhs.curr > rhs.curr;
}

bool operator<=(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs){
	    return lhs.curr <= rhs.curr;
}

bool operator>=(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs){
	    return lhs.curr >= rhs.curr;
}

//==================================================================
//
//      copy assignment operator and move assignment operator.
//
//==================================================================
StrBlob& StrBlob::operator=(const StrBlob& lhs){
    data = make_shared<vector<string>>(*lhs.data);
    return *this;
}

StrBlob& StrBlob::operator=(StrBlob&& rhs) noexcept{
    if (this != &rhs) {
        data = move(rhs.data);
        rhs.data = nullptr;
    }

    return *this;
}

//==================================================================
//
//      members
//
//==================================================================
StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end(){
    return StrBlobPtr(*this, data->size());
}

ConstStrBlobPtr StrBlob::cbegin() const{
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::cend() const{
    return ConstStrBlobPtr(*this, data->size());
}

//StrVec
class StrVec {
    friend bool operator==(const StrVec&, const StrVec&);
	friend bool operator!=(const StrVec&, const StrVec&);
	friend bool operator<(const StrVec&, const StrVec&);
	friend bool operator>(const StrVec&, const StrVec&);
	friend bool operator<=(const StrVec&, const StrVec&);
	friend bool operator>=(const StrVec&, const StrVec&);
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    StrVec(StrVec&&) noexcept;
    StrVec& operator=(StrVec&&) noexcept;
    ~StrVec();

    StrVec& operator=(initializer_list<string>);         //14.23
    void push_back(const string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    string* begin() const { return elements; }
    string* end() const { return first_free; }

    string& at(size_t pos) { return *(elements + pos); }
    const string& at(size_t pos) const { return *(elements + pos); }

    string& operator[](size_t n) { return elements[n]; }           //14.26
    const string& operator[](size_t n) const { return elements[n]; }  //14.26

    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const string&);

private:
    pair<string*, string*> alloc_n_copy(const string*, const string*);
    void free();
    void chk_n_alloc()    {
        if (size() == capacity()) reallocate();
    }
    void reallocate();
    void alloc_n_move(size_t new_cap);
    void range_initialize(const string*, const string*);
private:
    string* elements;
    string* first_free;
    string* cap;
    allocator<string> alloc;
};

bool operator==(const StrVec&, const StrVec&);
bool operator!=(const StrVec&, const StrVec&);
bool operator<(const StrVec&, const StrVec&);
bool operator>(const StrVec&, const StrVec&);
bool operator<=(const StrVec&, const StrVec&);
bool operator>=(const StrVec&, const StrVec&);

void StrVec::push_back(const string& s){
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e){
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free(){
    if (elements) {
        for_each(elements, first_free,
                 [this](string& rhs) { alloc.destroy(&rhs); });
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::range_initialize(const string* first, const string* last){
    auto newdata = alloc_n_copy(first, last);
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(const StrVec& rhs){
    range_initialize(rhs.begin(), rhs.end());
}

StrVec::StrVec(initializer_list<string> il){
    range_initialize(il.begin(), il.end());
}

StrVec::~StrVec(){
    free();
}

StrVec& StrVec::operator=(const StrVec& rhs){
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::alloc_n_move(size_t new_cap){
    auto newdata = alloc.allocate(new_cap);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + new_cap;
}

void StrVec::reallocate(){
    auto newcapacity = size() ? 2 * size() : 1;
    alloc_n_move(newcapacity);
}

void StrVec::reserve(size_t new_cap){
    if (new_cap <= capacity()) return;
    alloc_n_move(new_cap);
}

void StrVec::resize(size_t count){
    resize(count, string());
}

void StrVec::resize(size_t count, const string& s){
    if (count > size()) {
        if (count > capacity()) reserve(count * 2);
        for (size_t i = size(); i != count; ++i)
            alloc.construct(first_free++, s);
    }
    else if (count < size()) {
        while (first_free != elements + count) alloc.destroy(--first_free);
    }
}

StrVec::StrVec(StrVec&& s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap){
    // leave s in a state in which it is safe to run the destructor.
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept{
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

bool operator==(const StrVec& lhs, const StrVec& rhs){
    return (lhs.size() == rhs.size() &&
            equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator!=(const StrVec& lhs, const StrVec& rhs){
    return !(lhs == rhs);
}

bool operator<(const StrVec& lhs, const StrVec& rhs){
	    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(const StrVec& lhs, const StrVec& rhs){
	    return rhs < lhs;
}

bool operator<=(const StrVec& lhs, const StrVec& rhs){
	    return !(rhs < lhs);
}

bool operator>=(const StrVec& lhs, const StrVec& rhs){
	    return !(lhs < rhs);
}

StrVec& StrVec::operator=(initializer_list<string> li){         //14.23
    auto data = alloc_n_copy(li.begin(), li.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

//14.24
class Date {
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool check(const Date& d);
    friend ostream& operator<<(ostream& os, const Date& d);
public:
    typedef size_t Size;

    //! default constructor
    Date() = default;
    //! constructor taking Size as days
    explicit Date(Size days);
    //! constructor taking three Size
    Date(Size d, Size m, Size y) : day(d), month(m), year(y) {}
    //! constructor taking iostream
    Date(istream& is, ostream& os);

    //! copy constructor
    Date(const Date& d);
    //! move constructor
    Date(Date&& d) noexcept;

    //! copy operator=
    Date& operator=(const Date& d);
    //! move operator=
    Date& operator=(Date&& rhs) noexcept;

    //! destructor  --  in this case, user-defined destructor is not nessary.
    ~Date() { cout << "destroying\n"; }

    //! members
    Size toDays() const; // not implemented yet.
    Date& operator+=(Size offset);
    Date& operator-=(Size offset);
    explicit operator bool() { return (year < 4000) ? true : false; }     //14.49
private:
    Size day = 1;
    Size month = 1;
    Size year = 0;
};

static const Date::Size YtoD_400 = 146097; // 365*400 + 400/4 -3 == 146097
static const Date::Size YtoD_100 = 36524; // 365*100 + 100/4 -1 ==  36524
static const Date::Size YtoD_4 = 1461; // 365*4 + 1          ==   1461
static const Date::Size YtoD_1 = 365; // 365

//! normal year
static const vector<Date::Size> monthsVec_n = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//! leap year
static const vector<Date::Size> monthsVec_l = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//! non-member operators:  <<  >>  -   ==  !=  <   <=  >   >=
//!
ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& d);
int operator-(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
Date operator-(const Date& lhs, Date::Size rhs);
Date operator+(const Date& lhs, Date::Size rhs);

//!  utillities:
bool check(const Date& d);
inline bool isLeapYear(Date::Size y);

//! check if the date object passed in is valid
inline bool check(const Date& d){
    if (d.month == 0 || d.month > 12)
        return false;
    else {
        //!    month == 1 3 5 7 8 10 12
        if (d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 ||
            d.month == 8 || d.month == 10 || d.month == 12) {
            if (d.day == 0 || d.day > 31)
                return false;
            else
                return true;
        }
        else {
            //!    month == 4 6 9 11
            if (d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) {
                if (d.day == 0 || d.day > 30)
                    return false;
                else
                    return true;
            }
            else {
                //!    month == 2
                if (isLeapYear(d.year)) {
                    if (d.day == 0 || d.day > 29)
                        return false;
                    else
                        return true;
                }
                else {
                    if (d.day == 0 || d.day > 28)
                        return false;
                    else
                        return true;
                }
            }
        }
    }
}

inline bool isLeapYear(Date::Size y){
    if (!(y % 400)) {
        return true;
    }
    else {
        if (!(y % 100)) {
            return false;
        }
        else
            return !(y % 4);
    }
}

//! constructor taking Size as days
//! the argument must be within (0, 2^32)
Date::Date(Size days){
    //! calculate the year
    Size y400 = days / YtoD_400;
    Size y100 = (days - y400 * YtoD_400) / YtoD_100;
    Size y4 = (days - y400 * YtoD_400 - y100 * YtoD_100) / YtoD_4;
    Size y = (days - y400 * YtoD_400 - y100 * YtoD_100 - y4 * YtoD_4) / 365;
    Size d = days - y400 * YtoD_400 - y100 * YtoD_100 - y4 * YtoD_4 - y * 365;
    this->year = y400 * 400 + y100 * 100 + y4 * 4 + y;

    //! check if leap and choose the months vector accordingly
    vector<Size> currYear =
        isLeapYear(this->year) ? monthsVec_l : monthsVec_n;

    //! calculate day and month using find_if + lambda
    Size D_accumu = 0, M_accumu = 0;
    //! @bug    fixed:  the variabbles above hade been declared inside the
    //! find_if as static
    //!                 which caused the bug. It works fine now after being move
    //!                 outside.

    find_if(currYear.cbegin(), currYear.cend(), [&](Size m) {

        D_accumu += m;
        M_accumu++;

        if (d < D_accumu) {
            this->month = M_accumu;
            this->day = d + m - D_accumu;

            return true;
        }
        else
            return false;
    });
}

//! construcotr taking iostream
Date::Date(istream& is, ostream& os){
    is >> day >> month >> year;

    if (is) {
        if (check(*this))
            return;
        else {
            os << "Invalid input! Object is default initialized.";
            *this = Date();
        }
    }
    else {
        os << "Invalid input! Object is default initialized.";
        *this = Date();
    }
}

//! copy constructor
Date::Date(const Date& d) : day(d.day), month(d.month), year(d.year){
}

//! move constructor
Date::Date(Date&& d) noexcept : day(d.day), month(d.month), year(d.year){
    cout << "copy moving";
}

//! copy operator=
Date& Date::operator=(const Date& d){
    this->day = d.day;
    this->month = d.month;
    this->year = d.year;

    return *this;
}

//! move operator=
Date& Date::operator=(Date&& rhs) noexcept{
    if (this != &rhs) {
        this->day = rhs.day;
        this->month = rhs.month;
        this->year = rhs.year;
    }
    cout << "moving =";

    return *this;
}

//! conver to days
Date::Size Date::toDays() const{
    Size result = this->day;

    //! check if leap and choose the months vector accordingly
    vector<Size> currYear =
        isLeapYear(this->year) ? monthsVec_l : monthsVec_n;

    //! calculate result + days by months
    for (auto it = currYear.cbegin(); it != currYear.cbegin() + this->month - 1;
         ++it)
        result += *it;

    //! calculate result + days by years
    result += (this->year / 400) * YtoD_400;
    result += (this->year % 400 / 100) * YtoD_100;
    result += (this->year % 100 / 4) * YtoD_4;
    result += (this->year % 4) * YtoD_1;

    return result;
}

//! member operators:   +=  -=

Date& Date::operator+=(Date::Size offset){
    *this = Date(this->toDays() + offset);
    return *this;
}

Date& Date::operator-=(Date::Size offset)
{
    if (this->toDays() > offset)
        *this = Date(this->toDays() - offset);
    else
        *this = Date();

    return *this;
}

//! non-member operators:  <<  >>  -   ==  !=  <   <=  >   >=

ostream& operator<<(ostream& os, const Date& d){
    os << d.day << " " << d.month << " " << d.year;
    return os;
}

istream& operator>>(istream& is, Date& d){
    if (is) {
        Date input = Date(is, cout);
        if (check(input)) d = input;
    }
    return is;
}

int operator-(const Date& lhs, const Date& rhs){
    return lhs.toDays() - rhs.toDays();
}

bool operator==(const Date& lhs, const Date& rhs){
    return (lhs.day == rhs.day) && (lhs.month == rhs.month) &&
           (lhs.year == rhs.year);
}

bool operator!=(const Date& lhs, const Date& rhs){
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs){
    return lhs.toDays() < rhs.toDays();
}

bool operator<=(const Date& lhs, const Date& rhs){
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs){
    return !(lhs <= rhs);
}

bool operator>=(const Date& lhs, const Date& rhs){
    return !(lhs < rhs);
}

Date operator-(const Date& lhs, Date::Size rhs){ //!  ^^^ rhs must not be larger than 2^32-1
    //! copy lhs
    Date result(lhs);
    result -= rhs;

    return result;
}

Date operator+(const Date& lhs, Date::Size rhs){ //!  ^^^ rhs must not be larger than 2^32-1
    //! copy lhs
    Date result(lhs);
    result += rhs;

    return result;
}

//14.32
class StrBlobPtr_pointer {
public:
	StrBlobPtr_pointer() = default;
	StrBlobPtr_pointer(StrBlobPtr* p) : pointer(p) {}

	StrBlobPtr& operator*();
	StrBlobPtr* operator->();
private:
	StrBlobPtr* pointer = nullptr;
};

StrBlobPtr& StrBlobPtr_pointer::operator*(){
	return *(this->pointer);
}

StrBlobPtr*	StrBlobPtr_pointer::operator->(){
	return &this -> operator*();
}

//14.34
class func_class{
    int operator()(int a, int b, int c){
        return a ? b : c;
    }
};

//14.35
class PrintString{
public:
    string& operator(istream in)(){
        string str;
        if(in){
          in >> str;
          return str;
        }else  
            return str;
    }
private:
    istream& is;
};
/*
class GetInput {
public:
    GetInput(std::istream& i = std::cin) : is(i) {}
    std::string operator()() const
    {
        std::string str;
        std::getline(is, str);
        return is ? str : std::string();
    }

private:
    std::istream& is;
};
*/

//14.37
class IsEqual {
    int value;
public:
    IsEqual(int v) : value(v) {}
    bool operator()(int elem) { return elem == value; }
};

//14.38
class BoundTest {
public:
    BoundTest(std::size_t l = 0, std::size_t u = 0) : lower(l), upper(u) {}
    bool operator()(const std::string& s)
    {
        return lower <= s.length() && s.length() <= upper;
    }

private:
    std::size_t lower;
    std::size_t upper;
};

//14.40
class ShorterString {
public:
    bool operator()(string const& s1, string const& s2) const
    {
        return s1.size() < s2.size();
    }
};

class BiggerEqual {
    size_t sz_;

public:
    BiggerEqual(size_t sz) : sz_(sz) {}
    bool operator()(string const& s) { return s.size() >= sz_; }
};

class Print {
public:
    void operator()(string const& s) { cout << s << " "; }
};

string make_plural(size_t ctr, string const& word, string const& ending){
    return (ctr > 1) ? word + ending : word;
}

void elimDups(vector<string>& words){
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggies(vector<string>& words, vector<string>::size_type sz){
    elimDups(words);
    stable_sort(words.begin(), words.end(), ShorterString());
    auto wc = find_if(words.begin(), words.end(), BiggerEqual(sz));
    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s") << " of length "
         << sz << " or longer" << endl;
    for_each(wc, words.end(), Print());
    cout << endl;
}






#endif
