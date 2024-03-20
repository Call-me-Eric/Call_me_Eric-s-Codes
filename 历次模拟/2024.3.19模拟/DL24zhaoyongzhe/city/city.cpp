#include "city.h"
#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<pair<int,int>,int> piii;
const int maxn = 5e2 + 10;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
vector<int> find_roads(int n, bool gold, vector<int> u, vector<int> v) {
    vi ans;ans.clear();int m = u.size();
    if(!gold){
        for(int i = 0;i < m;i += 16){
            vi tmp;
            for(int j = 0;i + j < m && j < 16;j++){
                for(int t = 1;t <= (1 << j);t++){
                    tmp.push_back(i + j);
                }
            }
            int x = count_common_roads(tmp);
            for(int j = 0;i + j < m && j < 16;j++){
                if((x >> j) & 1){ans.push_back(i + j);}
            }
        }
        return ans;
    }
    vector<piii> vec;
    for(int i = 0;i < m;i++){
        vec.push_back(make_pair(make_pair(u[i],v[i]),i));
    }
    vector<int> tmp;
    srand(time(0));
    mt19937 rnd(rand());
    while(1){
        int siz = vec.size();tmp.clear();
        if(siz == n - 1){
            for(auto i : vec)tmp.push_back(i.second);
            return tmp;
        }
        for(int i = 0;i < n;i++){fa[i] = i;swap(vec[rnd() % siz],vec[((rnd() + i) % siz)]);}
        for(auto i : vec){
            int x = i.first.first, y = i.first.second;
            if(getf(x) != getf(y)){
                tmp.push_back(i.second);
                fa[getf(x)] = getf(y);
            }
        }
        int x = count_common_roads(tmp);
        if(x == n - 1){return tmp;}
        if(!x){
            map<int,int> mp;
            for(auto i : tmp){mp[i] = 1;}
            for(auto i = vec.begin();i != vec.end();){
                if(mp[(*i).second]){auto it = i;i++;vec.erase(it);}
                else i++;
            }
        }
    }
    return ans;
}