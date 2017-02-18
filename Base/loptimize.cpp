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
    int surface = (1+p.x2-p.x1)*(1+p.y2-p.y1);
    Part np = p;

    bool not_extended = true;

    if(surface < h) {
      int leftspace = h-surface;
      int w = 1+p.x2 - p.x1;
      int h = 1+p.y2 - p.y1;
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
            np.y2 = p.y2 + 1;
            for (int x=p.x1; ok && x<=p.x2; x++) {
              piz[x][np.y2].toma = 0;
              piz[x][np.y2].mush = 0;
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
            np.x2 = p.x2 + 1;
            for (int y=p.y1; ok && y<=p.y2; y++) {
              piz[np.x2][y].toma = 0;
              piz[np.x2][y].mush = 0;
            }
          }
          ok = true;
        }
      }
    }
    optimized.push_back(np);
  }

  return optimized;
}

int main() {
  int R, C, H, L;
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

  int N;
  cin >> N;
  vector<Part> lp;
  for(int i=0; i<N;i++) {
    Part p;
    cin >> p.x1 >> p.y1 >> p.x2 >> p.y2;
    lp.push_back(p);
  }

  for(int i=0;i<15;i++) {
    lp = optimize(lp,piz,H);
  }
  cout << N << endl;
  for(int i=0; i<N;i++) {
    cout << lp[i].x1 << " " << lp[i].y1 << " " << lp[i].x2 << " " << lp[i].y2 << endl;
  }
}
