#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
bool st;
const int maxn = 3e6 + 10;
struct Splay{
    vector<int> trash;int tot, rt;
    struct node{
        int ch[2], fa, siz;char val;
        node(char val = 0,int siz = 0,int f = 0,int c0 = 0,int c1 = 0
        ):val(val),siz(siz),fa(fa){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define Fa(p) d[p].fa
    int newnode(char ch){
        int x = 0;
        if(trash.empty()){x = ++tot;}
        else {x = trash.back();trash.pop_back();}
        d[x] = node(ch,1); return x;
    }
    void maintain(int p){d[p].siz = d[C(p,0)].siz + d[C(p,1)].siz + 1;}
    bool get(int p){return C(Fa(p),1) == p;}
    void clearp(int p){d[p] = node();trash.push_back(p);}
    void printt(int p){
        // printf("%d %d %d %d %d %c\n",Fa(p),C(p,0),C(p,1),p, d[p].siz,d[p].val);
        // printf("%d %d\n",p,Fa(p));
        if(C(p,0))printt(C(p,0));
        putchar(d[p].val);
        if(C(p,1))printt(C(p,1));
    }
    void rotate(int p){
        int y = Fa(p) , z = Fa(y), chk = get(p);
        C(y,chk) = C(p,chk ^ 1); if(C(y,chk))Fa(C(y,chk)) = y;
        Fa(y) = p;Fa(p) = z;C(p,chk ^ 1) = y;
        if(z){C(z,y == C(z,1)) = p;}
        maintain(y);maintain(p);
    }
    void splay(int p,int root = 0){
        for(int f = Fa(p);f = Fa(p),f != root;rotate(p))
            if(Fa(f) != root)rotate(get(p) == get(f) ? f : p);
        if(!root)rt = p;
    }
    void build(){
        rt = newnode('#');int p = newnode('#');
        Fa(p) = rt;C(rt,1) = p;maintain(p);maintain(rt);
    }

    int find(int pos){
        pos++;int p = rt;
        while(1){
            // printf("p = %d,sizl = %d, pos = %d\n",p,d[C(p,0)].siz + 1, pos);
            if(pos == d[C(p,0)].siz + 1)return p;
            if(pos < d[C(p,0)].siz + 1)
                p = C(p,0);
            else{pos -= d[C(p,0)].siz + 1;p = C(p,1);}
        }
    }
    int getrange(int l,int r){
        int pl = find(l - 1);splay(pl);
        int pr = find(r + 1);splay(pr,pl);
        return C(pr,0);
    }
    int pre(){
        int p = C(rt,0);
        while(C(p,1))p = C(p,1);
        splay(p);return p;
    }
    int suf(){
        int p = C(rt,1);
        while(C(p,0))p = C(p,0);
        splay(p);return p;
    }
    void move(int k){splay(find(k));}
    vector<char> tmp;
    void insert(int l,int r,int f,int ch){
        if(r < l)return;
        int mid = l + r >> 1;
        int p = newnode(tmp[mid]);
        C(f,ch) = p;Fa(p) = f;
        if(l == r)return;
        insert(l,mid - 1,p,0);insert(mid + 1,r,p,1); 
        maintain(p);
    }
    void insert(vector<char> vec){
        int p = rt;suf();tmp = vec;
        insert(0,vec.size() - 1,p,1);
        maintain(p);splay(p);
    }
    void delet(int p){
        if(C(p,0))delet(C(p,0));
        if(C(p,1))delet(C(p,1));
        clearp(p);
    }
    void erase(int n){
        int r = d[C(rt,0)].siz + 1 + n, p1 = find(r);
        // printf("p1 = %d\n",p1);
        splay(p1,rt);
        // puts("111111111");
        int p = C(C(rt,1),0), f = Fa(p), tmp = rt;
        delet(p);C(f,p == C(f,1)) = 0;
        maintain(f);maintain(f);splay(tmp);
    }
    void print(int n){
        int r = d[C(rt,0)].siz + 1 + n;
        splay(find(r),rt);
        printt(C(C(rt,1),0));
    }
}tree;
int T;
bool ed;
// char ch[maxn];
signed main(){
    cerr << (&ed - &st) / 1024.0 / 1024.0 << "Mib cost." << endl;
    T = read();char opt[20];vector<char> tmp;
    tree.build();
    while(T--){
        scanf("%s",opt);
        if(opt[0] == 'M'){tree.move(read());}
        if(opt[0] == 'I'){
            int n = read();tmp.clear();
            for(int i = 0;i < n;i++){
                int ch = getchar();
                if(ch == '\n' || ch == '\r' || ch < 32 || ch > 126){i--;continue;}
                tmp.push_back(ch);
            }
            tree.insert(tmp);
        }
        if(opt[0] == 'D'){tree.erase(read());}
        if(opt[0] == 'G'){tree.print(read());puts("");}
        if(opt[0] == 'P'){tree.pre();}
        if(opt[0] == 'N'){tree.suf();}
        // tree.printt(tree.rt);
    }
    return 0;
}