#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
struct Splay{
    int rt, tot;
    struct node{
        int fa,ch[2];
        int val, cnt, siz;
        node(int fa = 0,int ch0 = 0,int ch1 = 0,int val = 0,int cnt = 0,int siz = 0
        ):fa(fa),val(val),cnt(cnt),siz(siz){ch[0] = ch0;ch[1] = ch1;}
    }d[maxn];
    void maintain(int p){d[p].siz = d[d[p].ch[0]].siz + d[d[p].ch[1]].siz + d[p].cnt;}
    bool get(int p){return p == d[d[p].fa].ch[1];}
    void clearp(int p){d[p] = node();}
    void rotate(int p){
        int y = d[p].fa, z = d[y].fa, chk = get(p);
        d[y].ch[chk] = d[p].ch[chk ^ 1];
        if(d[p].ch[chk ^ 1])d[d[p].ch[chk ^ 1]].fa = y;
        d[p].ch[chk ^ 1] = y; d[y].fa = p; d[p].fa = z;
        if(z)d[z].ch[y == d[z].ch[1]] = p;
        maintain(y);maintain(p);
        // printf("%d %d\n",y,p);
    }
    void splay(int p){
        for(int f = d[p].fa;f = d[p].fa,f;rotate(p)){
            if(d[f].fa)rotate(get(f) == get(p) ? f : p);
            // printf("%d %d\n",f,p);
        }
        rt = p;
    }
    void insert(int x){
        if(!rt){
            d[rt = ++tot] = node(0,0,0,x,1,1);
            maintain(rt); return;
        }
        int p = rt, f = 0;
        while(1){
            // printf("p = %d\n",p);
            if(d[p].val == x){
                d[p].cnt++;
                maintain(p);maintain(f);
                splay(p);break;
            }
            // printf("->%d\n",d[p].val < x);
            f = p; p = d[p].ch[d[p].val < x];
            if(!p){
                p = ++tot;d[f].ch[d[f].val < x] = p;
                d[p] = node(f,0,0,x,1,1);
                maintain(p); maintain(f); splay(p); break;
            }
        }
    }
    int rank(int x){
        int res = 0, p = rt;
        while(1){
            if(x < d[p].val){p = d[p].ch[0];}
            else{
                res += d[d[p].ch[0]].siz;
                if(x == d[p].val){
                    // res += d[p].cnt;//这里需要看题干的定义
                    splay(p);return res;
                }
                res += d[p].cnt;p = d[p].ch[1];
            }
        }
    }
    int kthnum(int rnk){
        int p = rt;
        while(1){
            if(d[p].ch[0] && rnk <= d[d[p].ch[0]].siz){
                p = d[p].ch[0];
            }
            else{
                rnk -= d[d[p].ch[0]].siz + d[p].cnt;
                if(rnk <= 0){splay(p);return d[p].val;}
                p = d[p].ch[1];
            }
        }
    }
    int prenum(){//强制找根的前驱，注意这里返回的是指针
        int p = d[rt].ch[0];
        if(!p){return 0;}
        while(d[p].ch[1])p = d[p].ch[1];
        int ans = p;splay(p);
        return ans;
    }
    void delet(int x){
        rank(x);//希望这个数旋转到根可以找一下这个数的rank
        if(d[rt].cnt > 1){d[rt].cnt--;return;}
        if(!d[rt].ch[0] && !d[rt].ch[1]){
            clearp(rt);rt = 0;return;
        }
        if(!d[rt].ch[0]){
            int p = rt;rt = d[rt].ch[1];
            d[rt].fa = 0;clearp(p);
            return;
        }
        if(!d[rt].ch[1]){
            int p = rt;rt = d[rt].ch[0];
            d[rt].fa = 0;clearp(p);
            return;
        }
        int p = rt, y = prenum();
        d[d[p].ch[1]].fa = y;
        d[y].ch[1] = d[p].ch[1];
        clearp(p);maintain(rt);
    }
    int prenum(int x){
        insert(x);
        int p = d[rt].ch[0];
        if(!p){return -1;}
        while(d[p].ch[1]){p = d[p].ch[1];}
        int ans = p;splay(p);
        delet(x);
        return d[ans].val;
    }
    int sufnum(int x){
        insert(x);
        int p = d[rt].ch[1];
        if(!p){return -1;}
        while(d[p].ch[0]){p = d[p].ch[0];}
        int ans = p;splay(p);
        delet(x);
        return d[ans].val;
    }
}tree;
unordered_map<int,int> mp;
signed main(){
    int n = read(), ans = 0;
    for(int i = 1;i <= n;i++){
        int x = read();
        int a = tree.prenum(x);
        a = (a == -1) ? 0x3f3f3f3f : (x - a);
        int b = tree.sufnum(x);
        b = (b == -1) ? 0x3f3f3f3f : (b - x);
        if(mp[x])a = 0;
        if(i == 1)a = x;  ans += min(a, b);
        tree.insert(x);mp[x] = 1;
    }
    printf("%d\n",ans);
    return 0;
}
