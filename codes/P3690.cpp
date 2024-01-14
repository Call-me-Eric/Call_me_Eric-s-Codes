#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0 , f  =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
struct LCT{
    struct node{
        int fa, ch[2]; int val, sum;
        node(int fa = 0,int c0 = 0,int c1 = 0,int val = 0,int sum = 0
        ):fa(fa),val(val),sum(sum){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define FA(p) d[p].fa
    void maintain(int p){d[p].sum = d[C(p,0)].sum ^ d[p].val ^ d[C(p,1)].sum;}
    int get(int p){return p == C(FA(p),0) ? 0 : (p == C(FA(p),1) ? 1 : -1);}//return p == Fa(p,1),but return -1 when p is the root of Splay
    void connect(int p,int f,int chk){FA(p) = f; if(chk == 0 || chk == 1)C(f,chk) = p;}
    
    void rotate(int x){
        int y = FA(x), z = FA(y), chkx = get(x), chky = get(y);
        int u = chkx != -1 ? C(x,chkx ^ 1) : 0;
        connect(u,y,chkx);connect(y,x,chkx ^ 1);connect(x,z,chky);
        maintain(y);maintain(x);
    }
    void splay(int p){
        while(get(p) != -1){
            int f = FA(p);
            if(get(f) == -1)rotate(p);
            else if(get(f) == get(p)){rotate(f);rotate(p);}
            else {rotate(p);rotate(p);}
        }
    }
    void access(int p){
        
    }
};
signed main(){
    return 0;
}