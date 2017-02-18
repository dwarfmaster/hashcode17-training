
#ifndef DEF_DATA_H
#define DEF_DATA_H
#include <vector>
using namespace std;

typedef long long int lli;
typedef unsigned long long int llu;

struct PizzaData{
    PizzaData():toma(0),mush(0){}
    lli toma;
    lli mush;
    inline PizzaData operator+=(const PizzaData& p) {
        toma += p.toma;
        mush += p.mush;
        return *this;
    }
    inline PizzaData operator-=(const PizzaData& p) {
        toma -= p.toma;
        mush -= p.mush;
        return *this;
    }
};
inline PizzaData operator+(const PizzaData& p1, const PizzaData& p2) {
    PizzaData r(p1);
    r += p2;
    return r;
}
inline PizzaData operator-(const PizzaData& p1, const PizzaData& p2) {
    PizzaData r(p1);
    r -= p2;
    return r;
}

typedef vector< vector<PizzaData> > Pizza;

inline ostream& operator << (ostream&out, const PizzaData& pizd){
    out << "M:" << pizd.mush << " T:" << pizd.toma << " ";
    return out;
}

/* [x1,x2], [y1,y2] */
struct Part {
    size_t x1, x2, y1, y2;
};

ostream& operator<< (ostream& out, const Part& pt) {
    out << pt.x1 << " " << pt.y1 << " " << pt.x2 << " " << pt.y2;
    return out;
}

#endif
