#include <iostream>
#include <vector>
#include "prettyprint.hpp"

using namespace std;

typedef long long int lli;
typedef unsigned long long int llu;

struct PizzaData{
    PizzaData():toma(0),mush(0){}
    lli toma;
    lli mush;
    PizzaData operator+=(const PizzaData& p) {
        toma += p.toma;
        mush += p.mush;
        return *this;
    }
    PizzaData operator-=(const PizzaData& p) {
        toma -= p.toma;
        mush -= p.mush;
        return *this;
    }
};
PizzaData operator+(const PizzaData& p1, const PizzaData& p2) {
    PizzaData r(p1);
    r += p2;
    return r;
}
PizzaData operator-(const PizzaData& p1, const PizzaData& p2) {
    PizzaData r(p1);
    r -= p2;
    return r;
}

typedef vector< vector<PizzaData> > Pizza;

void computeSums(Pizza& piz) {
    for(size_t j = 1; j < piz[0].size(); ++j) piz[0][j] += piz[0][j-1];

    for(size_t i = 1; i < piz.size(); ++i) {
        piz[i][0] += piz[i-1][0];
        for(size_t j = 1; j < piz[i].size(); ++j) {
            piz[i][j] = piz[i][j] + piz[i-1][j] + piz[i][j-1] - piz[i-1][j-1];
        }
    }
}

ostream& operator << (ostream&out, const PizzaData& pizd){
    out << "M:" << pizd.mush << " T:" << pizd.toma << " ";
    return out;
}


int main ()
{
    int R =0 , C = 0 , H = 0, L = 0;

    cin >> R >> C >> H >> L;
    Pizza piz (R,vector<PizzaData>(C));
    cout << "hey !" << endl;
    for(int i =0 ; i < R ; ++i){
        for(int j = 0 ; j < C ; ++j){
            char t;
            cin >> t;
            if(t == 'M'){
                piz[i][j].mush = 1;
            }
            if(t == 'T'){
                piz[i][j].toma = 1;
            }
        }
    }

    cout << piz <<endl;
    computeSums(piz);
    cout << piz << endl;

    return 0;
}
