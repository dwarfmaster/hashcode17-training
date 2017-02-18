#include <bits/stdc++.h>

#define FOR(i,n) for(lli i=0;i<(lli)(n);++i)
#define FORU(i,j,k) for(int i=(j);i<=(k);++i)
#define FORD(i,j,k) for(int i=(j);i>=(k);--i)

#define error(args...) { vector<string> _v = split(#args, ','); err(_v.begin(), args); }

#define pb push_back
#define mt make_tuple

using namespace std;

using lli = long long int;
using pll = pair<lli, lli>;

using vi = vector<lli>;
using vvi = vector<vi>;
using pii = tuple<lli, lli>;
using vii = vector<pii>;
using vvii = vector<vii>;

#define X(a) get<0>(a)
#define Y(a) get<1>(a)
#define Z(a) get<2>(a)

string TYPE(const int*)  { return "%d";   }
string TYPE(const lli*)  { return "%lld"; }
string TYPE(const char*) { return "%c";   }
string TYPE(const char**) { return "%s";   }
string TYPE(char**) { return "%s";   }

struct Part
{
    int r1, c1, r2, c2;
    Part(int r1, int c1, int r2, int c2) : r1(r1), c1(c1), r2(r2), c2(c2) {}
};

struct Coin
{
    int r, c;
    int seed;
    Coin(int r, int c, int seed) : r(r), c(c), seed(seed) {}
    bool operator < (const Coin & droite) const
    {
        return seed < droite.seed;
    }
};

int nbLig, nbCol;
lli cPizza[1042][1042];
int n;
char tmp;
lli curL;
lli amT, amM;
lli surf;
bool pris[1042][1042];
bool dejaVu[1042][1042];

set<Coin> coins;
vector<Part> parts;

vector<Part> coin(vector<vector<bool> > pizza, int mini, int maxi)
{
    parts.clear();
    srand(time(NULL));
    nbLig = pizza.size();
    nbCol = pizza[0].size();
    FOR(i, nbLig+1)
        FOR(j, nbCol+1)
        {
            dejaVu[i][j] = pris[i][j] = false;
            cPizza[i][j] = 0;
        }
    FORU(i, 1, nbLig)
    {
        curL = 0;
        FORU(j, 1, nbCol)
        {
            curL += pizza[i-1][j-1];
            cPizza[i][j] = curL + cPizza[i-1][j];
        }
    }
    coins.insert(Coin(0,0,rand()%(int)(1E9+7)));
    while(coins.size())
    {
        Coin cur = *coins.begin();
        coins.erase(coins.begin());
        if(!dejaVu[cur.r][cur.c])
        {
            dejaVu[cur.r][cur.c] = true;
            if(cur.r < nbLig-1)
                coins.insert(Coin(cur.r+1, cur.c, rand()%(int)(1E9+7)));
            if(cur.c < nbLig-1)
                coins.insert(Coin(cur.r, cur.c+1, rand()%(int)(1E9+7)));
            if(!pris[cur.r][cur.c])
            {
                vector<Coin> sel;
                FORU(i, cur.r, min(nbLig, cur.r+maxi)-1)
                {
                    int deb = cur.c, fin = min(nbCol, cur.c+maxi)-1;
                    while(deb < fin)
                    {
                        int mil = (deb + fin) / 2;
                        int nbT = cPizza[i+1][mil+1] - cPizza[i+1][cur.c] - cPizza[cur.r][mil+1] + cPizza[cur.r][cur.c];
                        int nbM = (i - cur.r + 1) * (mil - cur.c + 1) - nbT;
                        if(nbT >= mini && nbM >= mini)
                            fin = mil;
                        else
                            deb = mil + 1;
                    }
                    int nbT = cPizza[i+1][deb+1] - cPizza[i+1][cur.c] - cPizza[cur.r][deb+1] + cPizza[cur.r][cur.c];
                    int nbM = (i - cur.r + 1) * (deb - cur.c + 1) - nbT;
                    bool valid = nbT >= mini && nbM >= mini && nbT + nbM <= maxi;
                    FORU(i2, cur.r, i)
                        FORU(j, cur.c, deb)
                            if(pris[i2][j])
                                valid = false;
                    int borneMax = deb;
                    while(valid && borneMax < nbCol)
                    {
                        ++borneMax;
                        FORU(i2, cur.r, i)
                            if(pris[i2][borneMax])
                                valid = false;
                        valid &= (i - cur.r + 1) * (borneMax - cur.c + 1) <= maxi;
                    }
                    if(borneMax != deb)
                        sel.push_back(Coin(i, rand() % (borneMax-min(deb, borneMax-1)) + min(deb, borneMax - 1), rand()%(int)(1E9+7)));
                }
                if(sel.size())
                {
                    sort(sel.begin(), sel.end());
                    parts.push_back(Part(cur.r, cur.c, sel[0].r, sel[0].c));
                    FORU(i, cur.r, sel[0].r)
                        FORU(j, cur.c, sel[0].c)
                            pris[i][j] = 1;
                    if(nbLig < 600)
                    {
                        FORU(i, cur.r, cur.r)
                            coins.insert(Coin(i, sel[0].c+1, rand()%(int)(1E9+7)));
                        FORU(i, cur.c, cur.c)
                            coins.insert(Coin(sel[0].r+1, i, rand()%(int)(1E9+7)));
                    }
                    //FORU(i, cur.r, sel[0].r+1)
                    //    coins.insert(Coin(i, sel[0].c+1, rand()%(int)(1E9+7)));
                    //FORU(i, cur.c, sel[0].c)
                    //    coins.insert(Coin(sel[0].r+1, i, rand()%(int)(1E9+7)));
                }
            }
        }
    }
    return parts;
}
