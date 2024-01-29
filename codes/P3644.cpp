#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int K, n, sum;
int tot;
struct node1{
    int x, y;
    node1(int x,int y):x(x),y(y){}
    friend bool operator < (node1 a,node1 b){return a.x + a.y < b.x + b.y;}
}a[maxn];
struct node{
    int fa, ch[2];
    int val, siz, cnt, sum;
    node(int val = 0,int siz = 0,int cnt = 0,int fa =0,int c0 = 0,int c1 = 0
    ):val(val),siz(siz),cnt(cnt),fa(fa),sum(sum){ch[0] = c0;ch[1] = c1;}
}d[maxn << 1];
vector<int> trash;
struct Splay{
    int rt, tot;
    #define C(p,x) d[p].ch[x]
    #define Fa(p) d[p].fa
    inline void maintain(int p){
        d[p].siz = d[C(p,0)].siz + d[p].cnt + d[C(p,1)].siz;
        d[p].sum = d[C(p,0)].sum + d[p].cnt * d[p].val + d[C(p,1)].sum;
    }
    inline bool get(int p){return C(Fa(p),1) == p;}
    inline void clearp(int p){d[p] = node();trash.push_back(p);return;}
    inline int newnode(int val){
        int x = 0;if(trash.empty())x = ++tot;
        else {x = trash.back();trash.pop_back();}
        d[x] = node(val,1,1);return x;
    }
    void rotate(int p){
        int y = Fa(p), z = Fa(y), chk = get(p);
        C(y,chk) = C(p,chk ^ 1);
        if(C(y,chk))Fa(C(y,chk)) = y;
        Fa(y) = p;Fa(p) = z;C(p,chk ^ 1) = y;
        if(z)C(z,y == C(z,1)) = p;
        maintain(y);maintain(p);
    }
    void splay(int p){
        for(int f = Fa(p);f = Fa(p), f;rotate(p))
            if(Fa(f))rotate(get(p) == get(f) ? f : p);
        rt = p;
    }
    void insert(int val){
        if(!rt){
            rt = newnode(val);
            maintain(rt);return;
        }
        int p = rt, f = 0;
        while(1){
            if(d[p].val == val){
                d[p].cnt++;
                maintain(p);maintain(f);
                splay(p);return;
            }
            f = p;p = C(f,val > d[p].val);
            if(!p){
                p = newnode(val);
                Fa(p) = f;C(f,val > d[f].val) = p;
                maintain(p);maintain(f);
                splay(p);return;
            }
        }
    }
    int find(int val){
        int p = rt;
        while(1){
            if(d[p].val == val){return p;}
            p = C(p,d[p].val > val);
        }
    }
    void delet(int val){
        int p = find(val);splay(p);
        if(d[p].cnt > 1){d[p].cnt--; maintain(p); return;}
        if(!C(p,0) && !C(p,1)){clearp(rt);rt = 0;return;}
        if(!C(p,0) || !C(p,1)){
            int chk = !C(p,1);
            
        }
    }
};
signed main(){
    K = read(); n = read();
    for(int i = 1;i <= n;i++){
        char opt = getchar();while(opt < 'A' || opt > 'B'){opt = getchar();}
        int x = read();
        char opt1 = getchar();while(opt1 < 'A' || opt1 > 'B'){opt1 = getchar();}
        int y = read();
        if(opt == opt1){sum += x + y;}
        else{sum++;a[++tot] = node1(x, y);}
    }
    sort(a + 1,a + 1 + tot);n = tot;tot = 0;
    if(K == 1){

    }
    return 0;
}