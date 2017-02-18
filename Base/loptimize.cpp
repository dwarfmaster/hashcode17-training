#include <iostream>
#include <algorithm>
#include <vector>
#include "data.hpp"

using namespace std;


vector<Part> optimize(vector<Part> result, Pizza piz, lli h) {
  vector<Part> optimized;
  sort(result.begin(), result.end());
  for(Part p : result) {
    for(int x = p.x1; x <= p.x2; x++) {
      for(int y = p.y1; y <= p.y2;y++) {
        piz[x][y] = PizzaData();
      }
    }
  }

  /*
  for(int y = 0; y < piz[0].size(); y++) {
    for(int x = 0; x < piz.size(); x++)
      cout << piz[x][y];
    cout << endl;
    }*/


  for(Part p : result) {
    cout << p << " ";
    PizzaData pv = partValue(piz,p);
    int surface = pv.toma + pv.mush;
    Part np = p;

    bool not_extended = true;

    if(surface < h) {
      int leftspace = h-surface;
      int w = p.x2 - p.x1;
      int h = p.y2 - p.y1;
      // can extend vertically
      if(w <= leftspace) {
        if(p.y1 > 0) {
          bool ok = true;
          for (int x=p.x1; ok && x<=p.x2; x++) {
            if (piz[x][p.y1-1].toma + piz[x][p.y1-1].mush == 0) {
              ok = false;
            }
          }
          if(ok) {
            not_extended = false;
            cout << ":^ ";
            np.y1 = p.y1 - 1;
            for (int x=p.x1; ok && x<=p.x2; x++) {
              piz[x][np.y1].toma = 0;
              piz[x][np.y1].mush = 0;
            }
          }
        }
        if(not_extended && p.y2 < piz[0].size()-1) {
          bool ok = true;
          for (int x=p.x1; ok && x<=p.x2; x++) {
            if (piz[x][p.y2+1].toma + piz[x][p.y2+1].mush == 0) {
              ok = false;
            }
          }

          if(ok) {
            not_extended = false;
            cout << ":v ";
            np.y2 = p.y2 + 1;
            for (int x=p.x1; ok && x<=p.x2; x++) {
              piz[x][np.y1].toma = 0;
              piz[x][np.y1].mush = 0;
            }

          }
        }
      }

      if(not_extended && h <= leftspace) { // can extend horizontally
        bool ok = true;
        if(p.x1 > 0) {
          for (int y=p.y1; ok && y<=p.y2; y++) {
            if (piz[p.x1-1][y].toma + piz[p.x1-1][y].mush == 0) {
              ok = false;
            }
          }
          if(ok) {
            not_extended = false;
            cout << ":< ";
            np.x1 = p.x1 - 1;
            for (int y=p.y1; ok && y<=p.y2; y++) {
              piz[np.x1][y].toma = 0;
              piz[np.x1][y].mush = 0;
            }
          }
        }
        if(not_extended && p.x2 < piz.size()-1) {
          bool ok = true;
          for (int y=p.y1; ok && y<=p.y2; y++) {
            if (piz[p.x2+1][y].toma + piz[p.x2+1][y].mush == 0) {
              ok = false;
            }
          }
          if(ok) {
            cout << ":> ";
            np.x2 = p.x2 + 1;
            for (int y=p.y1; ok && y<=p.y2; y++) {
              piz[np.x1][y].toma = 0;
              piz[np.x1][y].mush = 0;
            }
          }
          ok = true;
        }
      }
    }
    optimized.push_back(np);
    cout << "=> " << np << endl;
  }

  return optimized;
}

int main() {
  int R, C, H, L;
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
  Part p0;
  p0.x1 = 0;
  p0.x2 = 1;
  p0.y1 = 0;
  p0.y2 = 1;

  vector<Part> p;
  p.push_back(p0);

  Part p1;
  p1.x1 = 0;
  p1.x2 = 1;
  p1.y1 = 2;
  p1.y2 = 3;
  p.push_back(p1);
  for(int i=0;i<2;i++) {
    p = optimize(p,piz,H);
  }
  cout << p[0] << p[1] << endl;
}
