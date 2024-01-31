#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int x = 0, f= 1;char  ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10;
const ull  K = 27;
ull hashh[maxn][2], up[maxn];
char ch[maxn];
int n;
int pos[maxn][maxn];
ll ans[maxn];
ull Hash(int l,int r,int opt){
    if(opt)return (hashh[l][opt] - hashh[r + 1][opt] * up[r - l + 1]);
    return (hashh[r][opt] - hashh[l - 1][opt] * up[r - l + 1]);
}
signed main(){
    scanf("%s",ch + 1);n = strlen(ch + 1);
    up[0] = 1;
    for(int i = 1;i <= n;i++){
        hashh[i][0] = (hashh[i - 1][0] * K + (ull)(ch[i] - 'a'));
        up[i] = up[i - 1] * K;
    }
    for(int i = n;i;i--){hashh[i][1] = (hashh[i + 1][1] * K + (ull)(ch[i] - 'a'));}
    for(int i = 1;i <= n;i++)pos[i][i] = 1;
    for(int len = 2;len <= n;len++){
        for(int i = 1;i + len - 1 <= n;i++){
            int j = i + len - 1,k,l;
            if(len & 1){k = i + len / 2 - 1;l = i + (len + 1) / 2;}
            else {k = i + len / 2 - 1;l = i + len / 2;}
            if(Hash(i,k,0) == Hash(l,j,1) && Hash(i,k,1) == Hash(l,j,0)){
                pos[i][j] = max(pos[i][j],pos[i][k] + 1);
            }
        }
    }
    for(int len = 1;len <= n;len++){
        for(int i = 1;i + len - 1 <= n;i++){
            int j = i + len - 1, k = i + (len + 1) / 2 - 1,l = i + len - len / 2;
            ans[pos[i][j]]++;
            // printf("pos[%d][%d]=%d\n",i,j,pos[i][j]);
        }
    }
    // printf("hash(1,2)=%llu,hash(3,4)=%llu\n",Hash(1,2,0),Hash(3,4,1));
    for(int i = n;i;i--)ans[i] += ans[i + 1];
    for(int i = 1;i <= n;i++)printf("%lld ",ans[i]);
    return 0;
}