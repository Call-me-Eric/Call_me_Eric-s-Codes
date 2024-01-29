#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch =  getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
typedef pair<int,int> pir;
int n;
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
pir frac(int x,int y){int g = gcd(x, y);return make_pair(x / g,y / g);}

map<int,int> mp;int tot;
int getid(int r){
    if(!mp[r])mp[r] = ++tot;
    return mp[r];
}
int cnt;
vector<pir> vec[maxn];
map<pir,int> ans;

signed main(){
    n = read();int opt, x, y;
    for(int i = 1;i <= n;i++){
        opt = read(); x = read(); y = read();
        int r = x * x + y * y, id = getid(r);
        if(opt == 1){
            cnt++;
            for(auto i : vec[id])
                ans[frac(i.first + x,i.second + y)] += 2;
            ans[frac(x,y)]++;
            vec[id].push_back(make_pair(x, y));
        }
        if(opt == 2){
            cnt--;
            pir tmp = frac(x, y);
            for(auto i : vec[id])
                if(i != make_pair(x, y))
                    ans[frac(i.first + x,i.second + y)] -= 2;
            vector<pir>::iterator it = vec[id].begin();
            while(*it != make_pair(x, y))it++;
            vec[id].erase(it);
            ans[tmp]--;
        }
        if(opt == 3){printf("%lld\n",cnt - ans[frac(x * 2,y * 2)]);}
    }
    return 0;
}