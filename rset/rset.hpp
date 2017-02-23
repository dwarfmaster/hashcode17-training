#ifndef RSET_H
#define RSET_H

#include<set>
#include<utility>
#include<cstdlib>
#include<ctime>

template<typename T> class rset;

template<typename T>
class rsetIterator{
    friend rset<T>;
    typedef typename std::set<std::pair<int,T>>::iterator iter;
    iter _iter;
    explicit rsetIterator(const iter& it) : _iter(it){}
public:
    const T& operator*(){
        return _iter->second;
    }
    const T& operator*() const{
        return _iter->second;
    }
    rsetIterator& operator ++(){
        ++_iter;
        return *this;
    }
    rsetIterator& operator --(){
        --_iter;
        return *this;
    }
    bool operator ==(const rsetIterator& oth)const {
        return _iter == oth._iter;
    }
    bool operator !=(const rsetIterator& oth)const {
        return _iter != oth._iter;
    }
};

template<typename T>
class rset{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T* const_pointer;
    typedef rsetIterator<T> iterator;
    typedef const rsetIterator<T> const_iterator;

private:
    std::set<std::pair<int,T>> _set;
public :
    rset() : _set(){
        srand(time(NULL));
        (void)rand();
        (void)rand();
    }
    std::pair<iterator,bool> insert(const value_type& val){
        std::pair<int,T> rval = std::pair<int,T>(rand(),val);
        auto res = _set.insert(rval);
        return std::pair<iterator,bool>(iterator(res.first),res.second);
    }
    iterator begin(){
        return iterator(_set.begin());
    }
    iterator end(){
        return iterator(_set.end());
    }
    const_iterator begin()const {
        return const_iterator(_set.begin());
    }
    const_iterator end()const{
        return const_iterator(_set.end());
    }
    bool empty()const{
        return _set.empty();
    }
    size_t size()const{
        return _set.size();
    }
    iterator find(const value_type& val) { // WARNING : linear time
        for(auto it = begin(); it != end() ; ++it){
            if (*it == val) return it;
        }
        return end();
    }
    size_t count(const value_type& val)const { // WARNING : linear time
        for(auto it = begin(); it != end() ; ++it){
            if (*it == val) return 1;
        }
        return 0;
    }
    size_t erase(const value_type& val){ // WARNING : linear time
        for(auto it = begin(); it != end() ; ++it){
            if (*it == val){
                _set.erase(it._iter);
                return 1;
            }
        }
        return 0;
    }
    iterator erase(iterator it){ // WARNING : linear time
        return iterator(_set.erase(it._iter));
    }
};

#endif
