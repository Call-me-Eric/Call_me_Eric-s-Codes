#include<bits/stdc++.h>
using namespace std;
const int maxp = 820000 + 10, maxn = 50 + 10, maxm = 400 + 10;
int n, m;
int a[maxn][maxm];
int cnt[maxn];
int p[maxn];
int ans[maxp];
int CNT;
int X[maxp], Y[maxp];
void print(int x = -1,char end = '\n'){
    printf("%d%c",x,end);
    return;
}
void moved(int x,int y){
    CNT++;
    X[CNT] = x;
    Y[CNT] = y;
    a[y][++cnt[y]] = a[x][cnt[x]--];
}
inline int top(int x){
    return a[x][cnt[x]];
}
int count(int x,int y){
    int res = 0;
    for(int i = 1;i <= m;i++)res += (a[x][i] == y);
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        cnt[i] = m;
        for(int j = 1;j <= m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    cnt[n + 1] = 0;
    for(int i = 1;i <= n + 1;i++)p[i] = i;
    for(int now = n;now >= 3;now--){
        int tot = count(p[1],now);
        for(int i = 1;i <= tot;i++){
            moved(p[now],p[now + 1]);
        }
        for(int i = 1;i <= m;i++){
            if(top(p[1]) == now){
                moved(p[1],p[now]);
            }
            else moved(p[1],p[now + 1]);
        }
        for(int i = 1;i <= m - tot;i++){
            moved(p[now + 1],p[1]);
        }
        for(int i = 1;i <= m;i++){
            if(top(p[2]) == now || cnt[p[1]] == m){
                moved(p[2],p[now + 1]);
            }
            else moved(p[2],p[1]);
        }
        swap(p[1],p[now]);
        swap(p[2],p[now + 1]);
        for(int k = 1;k < now;k++){
            tot = count(p[k],now);
            for(int i = 1;i <= tot;i++){
                moved(p[now],p[now + 1]);
            }
            for(int i = 1;i <= m;i++){
                if(top(p[k]) == now){
                    moved(p[k],p[now]);
                }
                else moved(p[k],p[now + 1]);
            }
            swap(p[k],p[now + 1]);
            swap(p[k],p[now]);
        }
        for(int i = 1;i < now;i++){
            while(top(p[i]) == now){
                moved(p[i],p[now + 1]);
            }
        }
        for(int i = 1;i < now;i++){
            while(cnt[p[i]] < m){
                moved(p[now],p[i]);
            }
        }
    }
    int tot = count(p[1],1);
    for(int i = 1;i <= tot;i++){
        moved(p[2],p[3]);
    }
    for(int i = 1;i <= m;i++){
        if(top(p[1]) == 1){
            moved(p[1],p[2]);
        }
        else moved(p[1],p[3]);
    }
    for(int i = 1;i <= tot;i++){
        moved(p[2],p[1]);
    }
    for(int i = 1;i <= m - tot;i++){
        moved(p[3],p[1]);
    }
    while(cnt[p[3]])moved(p[3],p[2]);
    for(int i = 1;i <= m - tot;i++){
        moved(p[1],p[3]);
    }
    for(int i = 1;i <= m;i++){
        if(top(p[2]) == 1){
            moved(p[2],p[1]);
        }
        else moved(p[2],p[3]);
    }
    print(CNT);
    for(int i = 1;i <= CNT;i++){
        print(X[i],' ');
        print(Y[i]);
    }
    return 0;
}