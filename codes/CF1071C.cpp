#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
const int opt[1 << 6][7] = {
{-1,-1,-1,-1,-1,-1},
{6,8,10,-1,-1,-1},
{5,8,11,-1,-1,-1},
{5,6,7,-1,-1,-1},
{4,7,10,-1,-1,-1},
{4,6,8,-1,-1,-1},
{3,4,5,3,7,11},
{4,5,6,-1,-1,-1},
{3,7,11,-1,-1,-1},
{3,6,9,-1,-1,-1},
{3,5,7,-1,-1,-1},
{1,3,5,1,6,11},
{3,4,5,5,7,9},
{2,3,4,2,6,10},
{3,4,5,-1,-1,-1},
{3,4,5,6,7,8},
{2,4,6,4,6,8},
{2,6,10,-1,-1,-1},
{2,5,8,-1,-1,-1},
{2,5,8,6,7,8},
{2,3,4,3,7,11},
{2,4,6,-1,-1,-1},
{2,3,4,3,5,7},
{2,4,6,5,7,9},
{2,3,4,4,7,10},
{1,2,3,1,6,11},
{1,2,3,1,5,9},
{2,3,4,4,5,6},
{2,3,4,-1,-1,-1},
{2,3,4,6,7,8},
{2,3,4,5,7,9},
{2,3,4,5,6,7},
{1,3,5,3,5,7},
{1,6,11,-1,-1,-1},
{1,5,9,-1,-1,-1},
{1,3,5,3,6,9},
{1,4,7,-1,-1,-1},
{1,4,7,6,7,8},
{1,4,7,5,7,9},
{1,4,7,5,6,7},
{1,3,5,5,7,9},
{1,2,3,2,6,10},
{1,3,5,-1,-1,-1},
{1,3,5,6,7,8},
{3,4,5,1,5,9},
{1,2,3,2,4,6},
{1,3,5,4,7,10},
{1,3,5,4,6,8},
{1,2,3,3,7,11},
{1,2,3,3,6,9},
{1,2,3,3,5,7},
{2,5,8,1,6,11},
{2,4,6,1,6,11},
{1,4,7,2,6,10},
{1,2,3,3,4,5},
{2,4,6,1,5,9},
{1,2,3,-1,-1,-1},
{1,2,3,6,7,8},
{1,2,3,5,7,9},
{1,2,3,5,6,7},
{1,2,3,4,7,10},
{1,2,3,4,6,8},
{2,3,4,1,5,9},
{1,2,3,4,5,6}
};
int n;
int a[maxn];
vector<pair<int,pair<int,int> > > res;

int pr[40][2], tot;
bool chose[40];
bool flag = false;
int add;
void dfs(int step,int sta,int nsta){
    if(flag)return;
    // printf("sta =  %d nsta = %d\n",sta,nsta);
    if(nsta == sta){
        int cnt = 0;
        for(int i = 0;i <= tot;i++){
            if(chose[i])res.push_back(make_pair(pr[i][0] - pr[i][1] + add,make_pair(pr[i][0] + add,pr[i][0] + pr[i][1] + add)));
        }
        flag = true;
        return;
    }
    if(step == -1){return;}
    int x1 = pr[step][0] - pr[step][1],x2 = pr[step][0],x3 = pr[step][0] + pr[step][1];
    x1 = n - x1;x2 = n - x2;x3 = n - x3;
    nsta ^= (1 << x1);nsta ^= (1 << x2);nsta ^= (1 << x3);
    chose[step] = 1; dfs(step - 1,sta,nsta);
    nsta ^= (1 << x1);nsta ^= (1 << x2);nsta ^= (1 << x3);
    chose[step] = 0;dfs(step - 1,sta,nsta);
}
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    int l = 1;
    for(int i = 1;i <= n;i += 6,l = i){
        int sta = 0;
        for(int j = 0;j < 6;j++)sta = (sta << 1) + a[i + j];
        if(opt[sta][2] + i - 1 > n || opt[sta][5] + i - 1 > n)break;
        if(opt[sta][0] != -1){
            res.push_back(make_pair(opt[sta][0] + i - 1,make_pair(opt[sta][1] + i - 1,opt[sta][2] + i - 1)));
            a[opt[sta][0] + i - 1] ^= 1;a[opt[sta][1] + i - 1] ^= 1;a[opt[sta][2] + i - 1] ^= 1;
        }
        if(opt[sta][3] != -1){
            res.push_back(make_pair(opt[sta][3] + i - 1,make_pair(opt[sta][4] + i - 1,opt[sta][5] + i - 1)));
            a[opt[sta][3] + i - 1] ^= 1;a[opt[sta][4] + i - 1] ^= 1;a[opt[sta][5] + i - 1] ^= 1;
        }
    }
    int sta = 0;
    if(n - l + 1 < 8){l = max(1,n + 1 - 8);}
    for(int j = l;j <= n;j++)sta = (sta << 1) + a[j];
    add = l - 1;
    int cnt = 0;
    for(int i = 2;i < n - l + 1;i++)
        for(int r = 1;i - r >= 1 && i + r <= n - l + 1;r++){
            pr[cnt][0] = i;pr[cnt++][1] = r;
        }
    n = n - l + 1;
    flag = 0;cnt--;tot = cnt;dfs(tot,sta,0);
    // printf("sta = %d,flag = %d\n",sta,flag);
    if(flag){
        puts("YES");
        printf("%d\n",res.size());
        for(auto i : res)printf("%d %d %d\n",i.first,i.second.first,i.second.second);
    }
    else{puts("NO");}
    return 0;
}