#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m, k;
char ch[maxn];
set<string> s;
inline int popcount(int x){int res = 0;for(;x;x >>= 1)res += (x & 1);return res;}
inline int lowbit(int x){return x & (-x);}
void main(){
    n = read(); m = read(); k = read();
    scanf("%s",ch + 1);
    for(int i = 1;i <= m;i++){
        string str;int l = read(), r = read();
        str.append(ch + l,r - l + 1); s.insert(str);

        if(s.size() <= k)puts("0 0");
        else{
            int mx = 0;
            vector<string> vec;vec.clear();set<string> tmp;tmp.clear();
            for(auto i : s)vec.push_back(i);
            for(int i = 0;i < (1 << vec.size());i++){
                if(popcount(i) <= k)continue;
                string st = "?";
                for(int j = 0;j < vec.size();j++){
                    if((i >> j) & 1){
                        if(st == "?")st = vec[j];
                        else{
                            int r = st.size() - 1,r1 = vec[j].size() - 1;
                            while(r >= 0 && r1 >= 0 && st[r] == vec[j][r1]){r--;r1--;}
                            st.erase(st.begin(),st.begin() + r + 1);
                        }
                    }
                }
                tmp.insert(st);
                for(int j = 0;j < st.size();j++)tmp.insert(st.substr(j));
                mx = max(mx,(int)st.size());
            }
            // for(auto i : tmp)cout << "str = " << i << endl;
            printf("%d %d\n",tmp.size(),mx);
        }
    }
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}