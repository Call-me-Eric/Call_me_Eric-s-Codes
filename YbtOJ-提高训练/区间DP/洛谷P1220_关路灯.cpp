#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n ,c;
const int maxn = 101;
int f[maxn][maxn][2];
int pos[maxn], s[maxn];
signed main(){
    n = read(); c = read();
    for(int i = 1;i <= n;i++){
        pos[i] = read();s[i] = s[i - 1] + read();
    }
    memset(f,0x3f,sizeof(f));
    f[c][c][0] = f[c][c][1] = 0;
    for(int len = 2;len <= n;len++){
        for(int l = 1;l + len - 1 <= n;l++){
            int r = l + len - 1;
            f[l][r][0] = min(f[l][r][0],f[l + 1][r][1] + (pos[r    ] - pos[l    ]) * (s[n] - s[r    ] + s[l    ]));
            f[l][r][0] = min(f[l][r][0],f[l + 1][r][0] + (pos[l + 1] - pos[l    ]) * (s[n] - s[r    ] + s[l    ]));
            f[l][r][1] = min(f[l][r][1],f[l][r - 1][0] + (pos[r    ] - pos[l    ]) * (s[n] - s[r - 1] + s[l - 1]));
            f[l][r][1] = min(f[l][r][1],f[l][r - 1][1] + (pos[r    ] - pos[r - 1]) * (s[n] - s[r - 1] + s[l - 1]));
        }
    }
    printf("%lld\n",min(f[1][n][1],f[1][n][0]));
    return 0;
}
