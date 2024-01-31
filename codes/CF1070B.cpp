#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
bool st;
const int maxn = 2e5 + 10, maxm = 5e6 + 10;
int n;
struct node{
    //opt == 1 : '-'
    int opt;int l, r;
    node(int opt = 0,int l = 0,int r = 0):opt(opt), l(l), r(r){}
    friend bool operator < (node a,node b){return a.l < b.l;}
}a[maxn];
char ch[100];
signed trie[maxm][2], tot = 1;
bool book[maxm][2];signed tag[maxm];
void insert(int x,int pos,int opt){
    int u = 1;
    for(int i = 32;i + 1;i--){
        bool v = ((x >> i) & 1ll);
        if(!trie[u][v])trie[u][v] = ++tot;
        u = trie[u][v];book[u][opt] = 1;
        if(i == pos){tag[u] = opt;return;}
    }
    return;
}
vector<pair<int,int> >ans;
void getans(int u,int x,int pos){
    if(pos < 0 || !u || !book[u][1] || x > (1ll << 32)){return;}
    if(tag[u] == 1){ans.push_back(make_pair(x,pos));return;}
    if(tag[u] == 0){return;}
    if(!book[u][0] && book[u][1]){ans.push_back(make_pair(x,pos));return;}
    getans(trie[u][0],x,pos - 1);getans(trie[u][1],x + (1ll << pos),pos - 1);
}
bool ed;
signed main(){
    cerr << (&ed - &st) / 1024.0 / 1024.0 << "Mib cost." << endl;
    memset(tag,-1,sizeof(tag));
    n = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1);
        a[i].opt = (ch[1] == '-');
        int j = 2, len = strlen(ch + 1);
        vector<int> tmp;tmp.clear();
        while(j <= len){
            int x = 0;
            while(j <= len && ch[j] >= '0' && ch[j] <= '9'){x = (x << 1) + (x << 3) + ((int)ch[j] ^ 48ll);j++;}
            tmp.push_back(x);j++;
        }
        if(tmp.size() == 4){tmp.push_back(32);}
        a[i].l = tmp[0] * (1ll << 24) + tmp[1] * (1ll << 16) + tmp[2] * (1ll << 8) + tmp[3];
        a[i].r = 32 - tmp[4];
    }
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++){
        if(i < n && (a[i].opt ^ a[i + 1].opt) && (a[i].l + (1 << (a[i].r)) > a[i + 1].l)){
            puts("-1"); return 0;
        }
        insert(a[i].l,a[i].r,a[i].opt);
    }
    book[1][0] = book[1][1] = 1;getans(1,0,32);
    printf("%d\n",ans.size());
    for(int j = ans.size() - 1;j + 1;j--){
        auto i = ans[j];
        // printf("%lld %lld\n",i.first,i.second);
        int x1 = i.first >> 24ll;i.first -= (x1 << 24ll);
        int x2 = i.first >> 16ll;i.first -= (x2 << 16ll);
        int x3 = i.first >> 8ll;i.first -= (x3 << 8ll);
        int x4 = i.first, pos = 32 - i.second;
        printf("%lld.%lld.%lld.%lld/%lld\n",x1,x2,x3,x4,pos - 1);
    }
    return 0;
}