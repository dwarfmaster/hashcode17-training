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

const int MAX_BUF = 1000*1000;
char buf[MAX_BUF];

void RD() {}
template<typename T, typename... Args> 
void RD(T* v, Args... args)
{
    scanf((" " + TYPE(v)).c_str(), v);
    RD(args...);
}
template<typename... Args> 
void RD(string* v, Args... args)
{
    scanf(" %s", buf);
    *v = buf;
    RD(args...);
}

bool error = false;

void PR(bool nl = true)
{ error = true; if(nl) printf("\n"); }
template<typename T, typename... Args> 
void PR(bool nl, T v, Args... args)
{
    printf((TYPE(&v) + " ").c_str(), v);
    PR(nl, args...);
}
template<typename... Args> 
void PR(bool nl, string v, Args... args)
{
    printf("%s", v.c_str());
    PR(nl, args...);
}
template<typename... Args> 
void PR(Args... args)
{ PR(true, args...); }

vector<string> split(const string& s, char c)
{
    vector<string> v;
    stringstream ss(s);
    string x;
    while (getline(ss, x, c))
        v.emplace_back(x);
    return move(v);
}

void err(vector<string>::iterator) {}
template<typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args)
{
    cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << '\n';
    err(++it, args...);
}

const long long int oo = 1000*1000*1000;

struct Coord
{
    int x, y;
    Coord(int x = 0, int y = 0) : x(x), y(y) {}
    Coord operator + (const Coord& droite) const
    {
        return Coord(x + droite.x, y + droite.y);
    }
};

struct AB
{
    int k;
    vector<lli> arbre;
    AB(int _k = 20, lli def = 0)
    {
        k = _k;
        FOR(i, 1 << k)
            arbre.push_back(i < (1 << (k-1)) ? 0LL : def);
        FORD(i, ((1 << (k-1)) - 1), 1)
            arbre[i] = arbre[i << 1] + arbre[(i << 1) ^ 1];
    }
    void set(int i, lli x)
    {
        int feuille = i + (1 << (k-1));
        arbre[feuille] = x;
        iset(feuille >> 1);
    }
    void iset(int noeud)
    {
        if(noeud)
        {
            arbre[noeud] = arbre[noeud << 1] + arbre[(noeud << 1)  ^ 1];
            iset(noeud >> 1);
        }
    }
    lli sum(int deb, int fin, int noeud = 1, int p = 0, int q = -1)
    {
        if(q < p)
            q = 1 << (k-1);
        if(deb <= p && q <= fin)
            return arbre[noeud];
        if(deb >= q || fin <= p)
            return 0LL;
        int mil = (p + q) / 2;
        return sum(deb, fin, noeud << 1, p, mil) + sum(deb, fin, (noeud << 1) ^ 1, mil, q);
    }
};

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

int nbLig, nbCol, mini, maxi;
bool pizza[1042][1042];
bool pizza2[1042][1042];
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

int main()
{
    srand(time(NULL));
    int rot = rand()%4;
    RD(&nbLig, &nbCol, &mini, &maxi);
    FOR(i, nbLig)
        FOR(j, nbCol)
        {
            RD(&tmp);
            pizza[i][j] = tmp == 'T';
        }
    FOR(r, rot)
    {
        swap(nbLig, nbCol);
        FOR(i, nbLig)
            FOR(j, nbCol)
                pizza2[i][j] = pizza[j][nbLig-i-1];
        FOR(i, nbLig)
            FOR(j, nbCol)
                pizza[i][j] = pizza2[i][j];
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
                        sel.push_back(Coin(i, rand() % (borneMax-max(deb, borneMax-1)) + max(deb, borneMax - 1), rand()%(int)(1E9+7)));
                }
                if(sel.size() && rand()%10)
                {
                    sort(sel.begin(), sel.end());
                    Part rep = Part(cur.r, cur.c, sel[0].r, sel[0].c);
                    FOR(r, rot)
                    {
                        rep = Part(rep.c1, nbLig-rep.r1-1, rep.c2, nbLig-rep.r2-1);
                        swap(nbLig, nbCol);
                    }
                    FOR(r, 4-rot)
                        swap(nbLig, nbCol);
                    parts.push_back(rep);
                    FORU(i, cur.r, sel[0].r)
                        FORU(j, cur.c, sel[0].c)
                            pris[i][j] = 1;
                    if(nbLig < 600)
                    {
                        FORU(i, cur.r, cur.r+1)
                            coins.insert(Coin(i, sel[0].c+1, rand()%(int)(1E9+7)));
                        FORU(i, cur.c, cur.c+1)
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
    PR((int)parts.size());
    for(auto p : parts)
        PR(min(p.r1,p.r2), min(p.c1,p.c2), max(p.r2,p.r1), max(p.c2,p.c1));
    //fprintf(stderr, "%d\n", rot);
    return 0;
}
