#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0,  f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10,INF = 0x3f3f3f3f;
struct Splay{
    int rt, tot;
    struct node{
        int val, ch[2], fa;
        int siz, cnt;
        node(int fa = 0,int c0 = 0,int c1 = 0,int val = 0,int  siz=  0,int cnt = 0
            ):fa(fa),val(val),cnt(cnt),siz(siz){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    void maintain(int p){d[p].siz = d[d[p].ch[0]].siz + d[d[p].ch[1]].siz + d[p].cnt;}
    bool get(int p){return p == d[d[p].fa].ch[1];}
    void rotate(int p){
        int y = d[p].fa, z = d[y].fa, chk = get(p);
        d[y].ch[chk] = d[p].ch[chk ^ 1];
        if(d[p].ch[chk ^ 1])d[d[p].ch[chk ^ 1]].fa = y;
        d[p].ch[chk ^ 1] = y;d[y].fa = p;d[p].fa = z;
        if(z){d[z].ch[y == d[z].ch[1]] = p;}
        maintain(y);maintain(p);
    }
    void splay(int p){
        for(int f = d[p].fa;f = d[p].fa,f;rotate(p))
            if(d[f].fa)rotate(get(f) == get(p) ? f : p);
        rt = p;
    }
    void insert(int x){
        if(!rt){
            d[rt = ++tot] = node(0,0,0,x,1,1);
            maintain(rt); return;
        }
        int p = rt, f = 0;
        while(1){
            if(d[p].val == x){
                d[p].cnt++;
                maintain(p);maintain(f);
                splay(p);return;
            }
            f = p;p = d[p].ch[x > d[p].val];
            if(!p){
                p = ++tot;
                d[f].ch[x > d[f].val] = p;
                d[p] = node(f,0,0,x,1,1);
                maintain(p);maintain(f);
                splay(p); return;
            }
        }
    }
    int kthnum(int k){
        int p = rt;
        while(1){
            if(!p)return -INF * 2;
            // printf("p = %d,ls = %d,rs = %d k = %d,val = %d\n",p,d[d[p].ch[0]].siz,d[d[p].ch[1]].siz,k,d[p].val);
            if(d[p].ch[1] && d[d[p].ch[1]].siz >= k){
                p = d[p].ch[1];continue;
            }
            k -= d[d[p].ch[1]].siz + d[p].cnt;
            if(k <= 0){splay(p);return d[p].val;}
            p = d[p].ch[0];
        }
    }
    int rank(int val){
        int p = rt, res = 0;
        if(!p)return 0;
        while(1){
            // printf("p = %d -> %d\n",p,d[p].val > val);
            if(val < d[p].val){p = d[p].ch[0];continue;}
            res += d[d[p].ch[0]].siz;
            if(d[p].val == val){splay(p);return res;}
            res += d[p].cnt;p = d[p].ch[1];
        }
    }
    int prenum(){
        int p = d[rt].ch[0];
        if(!p)return 0;
        while(d[p].ch[1])p = d[p].ch[1];
        splay(p);return p;
    }
    void delet(int x){
        // rank(x);//希望这个数旋转到根可以找一下这个数的rank
        if(d[rt].cnt > 1){d[rt].cnt--;return;}
        if(!d[rt].ch[0] && !d[rt].ch[1]){
            d[rt] = node();rt = 0;return;
        }
        if(!d[rt].ch[0]){
            int p = rt;rt = d[rt].ch[1];
            d[rt].fa = 0;d[p] = node();
            return;
        }
        if(!d[rt].ch[1]){
            int p = rt;rt = d[rt].ch[0];
            d[rt].fa = 0;d[p] = node();
            return;
        }
        int p = rt, y = prenum();
        d[d[p].ch[1]].fa = y;
        d[y].ch[1] = d[p].ch[1];
        d[p] = node(); maintain(rt);
    }
    int erase(int val){
        insert(val);
        int x = d[d[rt].ch[0]].siz;
        d[d[rt].ch[0]] = node();d[rt].ch[0] = 0;
        maintain(rt); delet(val);maintain(rt);
        return x;
    }
    void print(int p){
        if(d[p].ch[0])print(d[p].ch[0]);
        printf("%d ",d[p].val);
        if(d[p].ch[1])print(d[p].ch[1]);
    }
}tree;
int n, minv;
int allupd;
signed main(){
    n = read(); minv = read();
    char opt[5];int x, sum = 0;
    for(int i = 1;i <= n;i++){
        scanf(" %s",opt);x = read();
        if(opt[0] == 'I'){if(x >= minv)tree.insert(x - allupd);}
        if(opt[0] == 'A'){allupd += x;}
        if(opt[0] == 'S'){allupd -= x;}
        if(opt[0] == 'F'){int y = tree.kthnum(x) + allupd;printf("%d\n",y < -INF ? -1 : y);}
        sum += tree.erase(minv - allupd);
        // tree.print(tree.rt);printf("root = %d,val = %d\n",tree.rt,tree.d[tree.rt].val);
    }
    printf("%d\n",sum);
    return 0;
}