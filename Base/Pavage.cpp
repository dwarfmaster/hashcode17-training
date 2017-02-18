#include"prettyprint.hpp"
#include"data.hpp"



vector<Part> pavage(const Pizza& piz,int h,int w,int l){
    vector<Part> res;
    int L = piz.size();
    int C = piz[0].size();
    for(int i = 0 ; i <= L - h; i+= h){
        for(int j = 0 ; j <= C - w ; j += w){
            Part par = {i,i+h-1,j,j+w-1};
            cout << i << " " << j << " " << par << endl;
            auto p = partValue(piz,par);
            if(p.toma >= l && p.mush >= l){
                res.push_back(par);
            }
        }
    }
    return res;
}
