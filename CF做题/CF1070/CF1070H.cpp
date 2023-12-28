#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
map<string,int> mp;
map<string,string> mp1;
int n, q;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n;string str;
    for(int i = 1;i <= n;i++){
        cin >> str;vector<string> vec;vec.clear();
        for(int l = 0;l < str.size();l++)
            for(int r = l;r < str.size();r++)
                vec.push_back(str.substr(l,r - l + 1));
        sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
        for(auto i : vec){mp[i]++;mp1[i] = str;}
    }
    cin >> q;
    for(int i = 1;i <= q;i++){
        cin >> str;
        if(mp.count(str))cout << mp[str] << ' ' << mp1[str] << '\n';
        else cout << "0 -\n";
    }
    return 0;
}