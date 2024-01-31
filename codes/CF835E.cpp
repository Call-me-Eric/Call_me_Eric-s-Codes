#include<bits/stdc++.h>
using namespace std;
int n, x, y, tmp;
vector<int> vec1,vec;
void solve(int l,int r){
    if(l == r){
        cout << "! " << min(vec1[l],(tmp ^ vec1[l])) << ' ' << max((tmp ^ vec1[l]),vec1[l])<< endl;
        exit(0);
    }
    int mid = l + r >> 1;vec.clear();
    for(int i = l;i <= mid;i++){vec.push_back(vec1[i]);}
    cout << "? " << vec.size();for(int i : vec)cout << ' ' << i;cout << endl;
    int res;cin >> res;
    if(vec.size() % 2){
        if(res == y){solve(l,mid);}
        else solve(mid + 1,r);
    }
    else{
        if(res == (x ^ y)){solve(l,mid);}
        else solve(mid + 1,r);
    }
}
signed main(){
    cin >> n >> x >> y;
    for(int i = 9;i + 1;i--){
        vec.clear();
        for(int j = 1;j <= n;j++){if(j & (1 << i))vec.push_back(j);}
        if(!vec.size())continue;
        cout << "? " << vec.size();for(int j : vec){cout << ' ' << j;}cout << endl;
        int res;cin >> res;
        if(vec.size() % 2){
            if(res == y){
                if(!vec1.size()){for(int j : vec)vec1.push_back(j);}
                tmp |= (1 << i);
            }
        }
        else{
            if(res == (x ^ y)){
                if(!vec1.size()){for(int j : vec)vec1.push_back(j);}
                tmp |= (1 << i);
            }
        }
    }
    solve(0,vec1.size() - 1);
    return 0;
}