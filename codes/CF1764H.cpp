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
const int maxn = 4e5 + 10;
int n, m, k;
int l[maxn], r[maxn], ans[maxn];
struct node{
    int l, r, val;
    node(int l = 0,int r = 0,int val = 0
    ):l(l),r(r),val(val){}
    friend bool operator < (node a,node b){
        return a.l == b.l ? a.r < b.r : a.l < b.l;
    }
};
set<node> st;
void split(int x){
    auto it = st.lower_bound(node(x,x));
    if(it == st.end() || (it->l) > x)it--;
    if((it->r) == x)return;
    int tl = it->l, tr = it->r, val = it->val;
    st.erase(it);st.insert(node(tl,x,val));st.insert(node(x + 1,tr,val));
}
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s += c[x];return s;}
    void upd(int x,int add){for(;x < maxn;x += lowbit(x))c[x] += add;}
}tr;
void main(){
    n = read(); m = read(); k = read();
    for(int i = 1;i <= m;i++){l[i] = read(), r[i] = read();}
    for(int i = m + 1;i <= m + k - 1;i++){l[i] = l[i - m];r[i] = r[i - m];}
    for(int i = 1;i <= n;i++){st.insert(node(i,i,maxn - 1));tr.upd(maxn - 1,1);}
    for(int i = m + k - 1;i;i--){
        split(l[i] - 1);split(r[i]);
        auto it = st.lower_bound(node(l[i],l[i]));
        auto itt = it;int ans = it->val;
        for(;it != st.end() && (it->r) <= r[i];it++){
            int siz = (it->r) - (it->l) + 1;tr.upd((it->val),-siz);
            ans = max(ans,it->val);
        }
        st.erase(itt,it);
        st.insert(node(l[i],l[i],ans));tr.upd(ans,1);
        if(l[i] + 1 <= r[i]){st.insert(node(l[i] + 1,r[i],i));tr.upd(i,r[i] - l[i]);}
        if(i <= m){::Call_me_Eric::ans[i] = tr.qry(maxn - 1) - tr.qry(i + k - 1);}
    }
    for(int i = 1;i <= m;i++)printf("%d ",ans[i]);puts("");
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