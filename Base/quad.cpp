#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>
#include <random>
#include "data.hpp"

#define OVERLAP 6

/* Assumes p1 <= p2 */
bool overlap(const Part& p1, const Part& p2) {
    return p1.x2 >= p2.x1 && p1.y2 >= p2.y1;
}

/* [x1,x2[, [y1,y2[ */
/* Return vector is lexicographically sorted */
list<Part> quad_rec(const Pizza& piz, size_t x1, size_t x2, size_t y1, size_t y2, lli L, lli H) {
    size_t mx = (x1 + x2) / 2;
    size_t my = (y1 + y2) / 2;
    size_t ov = OVERLAP / 2;

    if(x2 - x1 <= 2 * OVERLAP) {
        list<Part> result;
        /* TODO */
        return result;
    }

    list<Part> tl = quad_rec(piz, x1, mx + ov, y1, my + ov, L, H);
    list<Part> tr = quad_rec(piz, mx - ov, x2, y1, my + ov, L, H);
    list<Part> bl = quad_rec(piz, x1, mx + ov, my - ov, y2, L, H);
    list<Part> br = quad_rec(piz, mx - ov, x2, my - ov, y2, L, H);

    list<Part> result(tl.size() + tr.size() + bl.size() + br.size());
    auto it = set_union(tl.begin(), tl.end(), tr.begin(), tr.end(), result.begin());
    it = set_union(result.begin(), it, bl.begin(), bl.end(), it);
    it = set_union(result.begin(), it, br.begin(), br.end(), it);
    result.erase(it, result.end());

    for(auto it = result.begin(); it != result.end(); ++it) {
        int choice = rand() % 2;
        for(auto it2 = ++it; it2 != result.end(); ++it) {
            if(overlap(*it, *it2)) {
                if(choice) {
                    it = result.erase(it);
                    break;
                } else it2 = result.erase(it2);
            }
            if(it2->x1 > it->x1)
                break;
        }
    }
    return result;
}

list<Part> quad(const Pizza& piz, lli L, lli H) {
    return quad_rec(piz, 0, piz.size(), 0, piz[0].size(), L, H);
}

