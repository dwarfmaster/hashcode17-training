#include <iostream>
#include <vector>
#include <list>
#include "prettyprint.hpp"
#include "data.hpp"

list<Part> quad(const Pizza&, lli, lli);

using namespace std;

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
    int R =0 , C = 0 , H = 0, L = 0;

    cin >> R >> C >> L >> H;
    Pizza piz (R,vector<PizzaData>(C));
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

    /* 
     * computeSums(piz);
     * cout << piz << endl;
     */

    list<Part> result = quad(piz, L, H);
    cout << result.size() << endl;
    for(auto it = result.begin(); it != result.end(); ++it) cout << *it << endl;

    return 0;
}
