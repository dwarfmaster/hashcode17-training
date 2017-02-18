#include <iostream>
#include <vector>

using namespace std;

typedef long long int lli;
typedef unsigned long long int llu;

struct PizzaData{
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


int main ()
{
    
}
