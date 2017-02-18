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

int nbLig, nbCol, mini, maxi;
bool pizza[1042][1042];
lli cPizza[1042][1042];
int n;
lli cut[1042][1042];
lli cCut[1042][1042];
char tmp;
lli curL;
lli amT, amM;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        PR("help");
        return 0;
    }
    freopen(argv[1], "r", stdin);
    RD(&nbLig, &nbCol, &mini, &maxi);
    FOR(i, nbLig)
        FOR(j, nbCol)
        {
            RD(&tmp);
            pizza[i][j] = tmp == 'T';
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
    freopen(argv[2], "r", stdin);
    RD(&n);
    FOR(i, n)
    {
        int r1, c1, r2, c2;
        RD(&r1, &c1, &r2, &c2);
        if(r1 < 0 || c1 < 0 || r2 >= nbLig || c2 >= nbCol || r1 > r2 || c1 > c2)
            PR("La part", r1, c1, r2, c2, "a des coordonées invalides");
        ++r1; ++r2;
        ++c1; ++c2;
        cut[r1][c1] += 1;
        cut[r2+1][c2+1] += 1;
        cut[r1][c2+1] += -1;
        cut[r2+1][c1] += -1;
        amT = cPizza[r2][c2] - cPizza[r1-1][c2] - cPizza[r2][c1-1] + cPizza[r1-1][c1-1];
        amM = (r2-r1+1)*(c2-c1+1) - amT;
        if(amT < mini)
            PR("La part", r1-1, c1-1, r2-1, c2-1, "n'a pas assez de tomate");
        if(amM < mini)
            PR("La part", r1-1, c1-1, r2-1, c2-1, "n'a pas assez de champignons");
        if(amT + amM > maxi)
            PR("La part", r1-1, c1-1, r2-1, c2-1, "est trop grosse");
    }
    FORU(i, 1, nbLig)
    {
        curL = 0;
        FORU(j, 1, nbCol)
        {
            curL += cut[i][j];
            cCut[i][j] = curL + cCut[i-1][j];
        }
    }
    FORU(i, 1, nbLig)
        FORU(j, 1, nbCol)
            if(cCut[i][j] > 1)
                PR("La case", i-1, j-1, "à étée prise trop de fois");
    if(error == false)
        PR(n);
    return 0;
}
