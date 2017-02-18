#include <iostream>
#include <algorithm>
#include <vector>
#include "data.hpp"

using namespace std;


vector<Part> optimize(const vector<Part>& result, Pizza piz, lli h) {
  vector<Part> optimized;
  sort(result.begin(), result.end());

  for(Part p : result) {
    for(int x = p.x1; x <= p.x2; x++) {
      for(int y = p.y1; y <= p.y2;y++) {
        piz[x][y] = PizzaData();
      }
    }
  }

  for(Part p : result) {
    PizzaData pv = partValue(p);
    int surface = pv.toma + pv.mush;
    if(surface < h) {

      leftspace = h-surface;
      w = p.x2 - p.x1;
      h = p.y2 - p.y1;
      # can extend vertically
      if(w <= leftspace) {
        if(p.y1 > 0) {
          bool ok = true;
          for (int x=p.x1; ok && x<=p.x2; x++) {
            if (piz[x][p.y1-1].toma + piz[x][p.y1-1].mush == 0) {
              ok = false;
            }
          }
          if(ok) {
            p.y1 = p.y1 - 1;
            continue;
          }
        }
        if(p.y2 < piz[0].size()-1) {
          bool ok = true;
          for (int x=p.x1; ok && x<=p.x2; x++) {
            if (piz[x][p.y2+1].toma + piz[x][p.y2+1].mush == 0) {
              ok = false;
            }
          }
          if(ok) {
            p.y2 = p.y2 + 1;
            continue;
          }
        }
      } else if(h <= leftspace) { # can extend horizontally
        if(p.x1 > 0) {
          bool ok = true;
          for (int y=p.y1; ok && x<=p.y2; x++) {
            if (piz[p.x1-1][y].toma + piz[p.x1-1][y].mush == 0) {
              ok = false;
            }
          }
          if(ok) {
            p.x1 = p.x1 - 1;
            continue;
          }
        }
        if(p.x2 < piz.size()-1) {
          bool ok = true;
          for (int y=p.y1; ok && y<=p.y2; x++) {
            if (piz[p.x2][y].toma + piz[p.x2][y].mush == 0) {
              ok = false;
            }
          }
          if(ok) {
            p.x2 = p.x2 + 1;
            continue;
          }
        }
      }
    }
    optimized.push_back(p);
  }
}


