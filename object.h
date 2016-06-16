#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iterator>

// forward declaration needed for friend declaration in StrBlob
class StrBlobPtr;

class StrBlob
{
	friend class StrBlobPtr;
public:
    typedef std::vector<std::string>::size_type size_type;

	// constructors
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }
    StrBlob(std::initializer_list<std::string> il);

	// size operations
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();

    // element access
    std::string& front();
    std::string& back();

	// interface to StrBlobPtr
	StrBlobPtr begin();  // can't be defined until StrBlobPtr is
    StrBlobPtr end();
private:
    std::shared_ptr<std::vector<std::string>> data; 
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

// constructor
inline
StrBlob::StrBlob(std::initializer_list<std::string> il): 
              data(std::make_shared<std::vector<std::string>>(il)) { }

// StrBlobPtr throws an exception on attempts to access a nonexistent element 
class StrBlobPtr
{
	friend bool eq(const StrBlobPtr&, const StrBlobPtr&);
public:
    StrBlobPtr(): curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) { }

    //! newly overloaded why?
    StrBlobPtr(const StrBlob &a, const size_t sz = 0) : wptr(a.data), curr(sz) { }

    std::string& deref() const;
    StrBlobPtr& incr();       // prefix version
    StrBlobPtr& decr();       // prefix version
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<std::string>> 
        check(std::size_t, const std::string&) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;  
    std::size_t curr;      // current position within the array
};

inline
std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end"); 
    return (*p)[curr];  // (*p) is the vector to which this object points
}

inline
std::shared_ptr<std::vector<std::string>> 
StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();   // is the vector still around?
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");

    if (i >= ret->size()) 
        throw std::out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}

// prefix: return a reference to the incremented object
inline
StrBlobPtr& StrBlobPtr::incr()
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;       // advance the current state
    return *this;
}

inline
StrBlobPtr& StrBlobPtr::decr()
{
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;       // move the current state back one element}
    check(-1, "decrement past begin of StrBlobPtr");
    return *this;
}

// begin and end members for StrBlob
inline
StrBlobPtr
StrBlob::begin() 
{
	return StrBlobPtr(*this);
}

inline
StrBlobPtr
StrBlob::end() 
{
	auto ret = StrBlobPtr(*this, data->size());
    return ret; 
}

// named equality operators for StrBlobPtr
inline
bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
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
bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
	return !eq(lhs, rhs); 
}


class QueryResult;

/**
 * @brief The TextQuery class using StrBlob
 */
class TextQuery
{
public:
    typedef StrBlob::size_type line_no;

    //! constructor
    TextQuery(std::ifstream& fin);

    //! query operation
    QueryResult query(const std::string&) const;

private:
    //! data members
    StrBlob file;

    std::map<std::string,
             std::shared_ptr<std::set<line_no>>> wordMap;

};

/**
 * @brief constructor using StrBlob.
 */
TextQuery::TextQuery(std::ifstream &fin) :
    file(StrBlob()),
    wordMap(std::map<std::string,std::shared_ptr<std::set<line_no>>>())
{
    std::string line;

    //! each line
    while(std::getline(fin, line))
    {
        file.push_back(line);
        int n = file.size() - 1;    //! the current line number

        //! each word
        std::stringstream lineSteam(line);
        std::string word;
        while(lineSteam >> word)
        {
            std::shared_ptr<std::set<line_no>>&                          
                           sp_lines = wordMap[word];
            //! if null
            if(!sp_lines)
            {
                sp_lines.reset(new std::set<line_no>);
            }
            sp_lines->insert(n);
        }
    }
}

/**
 * @brief do a query opertion and return QueryResult object.
 */
QueryResult
TextQuery::query(const std::string &sought) const
{
    //! dynamicaly allocated set used for the word does not appear.
    static std::shared_ptr<std::set<line_no>> noData(new std::set<line_no>);

    //! fetch the iterator to the matching element in the map<word, lines>.
    //std::map<std::string, std::shared_ptr<std::set<index_Tp>>>::const_iterator
    auto iter = wordMap.find(sought);
    if(iter == wordMap.end())
        return QueryResult(sought, noData, file);
    else
        return QueryResult(sought, iter->second, file);
}



/*
 *@brief QueryResult
 */
class QueryResult{
	friend std::ostream& operator << (std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>>sp_l, StrBlob f) : sought(s), sp_lines(sp_l), file(f){ }
	
	const StrBlob& get_file() const { return file; }
	std::set<TextQuery::line_no>::iterator begin(){
		return sp_lines->begin();
	}
	std::set<TextQuery::line_no>::iterator end(){
		return sp_lines->end();
	}
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> sp_lines;
	StrBlob file;
};


/**
 * @brief print the result to the output stream specified.
 */
std::ostream&
print(std::ostream&, const QueryResult &);

/**
 * @brief   print the result to the output stream specified.
 * @note    class QueryResult's friend
 */
std::ostream&
operator <<(std::ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.sp_lines->size() << " "
       << "times"   <<  "\n";

    //! print each line in which the word appears
    for ( auto &index : *qr.sp_lines)
    {
        os << "\t(line " << index + 1 << ") ";
        const StrBlobPtr wp(qr.file, index);
        os << wp.deref() << "\n";
    }
    return os;

}

/*@brief abstruct class acts as a base class */
class Query_base{
	friend class query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	//a string representaion of this query
	virtual std::string rep() const = 0;

};

/*@brief The only class that actually performs a query on the given TextQuery object. No public members, all operation are through the friend class Query   */
class WordQuery : public Query_base{
	friend class Query ;
	WordQuery(const std::string& s) : query_word(s){
		std::cout<< "WordQuery::wordQuery("+ s +")\n";
	}
	//virtuals:
	QueryResult eval(const TextQuery& t)const override{
		return t.query(query_word); 
	}
	std::string rep() const override{
		std::cout << "wordquery::rep()\n";
		return query_word;
	}
	std::string query_word;
};

/*@brief interface class to manage the Query_base inheritance hierachy*/
class Query{
	friend Query operator~(const Query&);
	friend Query operator | (const Query&, const Query&);
	friend Query operator & (const Query&, const Query&);
public:
	Query(const std::string& s) : q(new WordQuery(s)){
		std::cout << "Query::query(const std::string& s) where s="+s+" \n";
	}
	//interface functions: call the corresspounding Query_base operations
	QueryResult eval(const TextQuery& t) const{ return q->eval(t);  }

	std::string rep() const {
		std::cout << "Query::rep() \n";
		return q->rep();
	}

private:
	Query(std::shared_ptr<Query_base> query) : q(query){
		std::cout << "Query::Query(std::shared_ptr<Query_base> query\n";
	}
	std::shared_ptr<Query_base> q;
};
inline std::ostream& operator << (std::ostream& os, const Query& query){
	//maka a vitual call through its Query_base pointer to rep();
	return os << query.rep();
}

#endif 
