#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 10,maxm = 10000 + 10;
struct stations{
    int off, latest, arrive;
}sta[maxn];
int n, m, k, ans;
int dis[maxn];
struct passenger{
    int start, end;
}pas[maxm];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 1;i < n;i++){
        scanf("%d",&dis[i]);
    }
    int t;
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&pas[i].start,&t,&pas[i].end);
        sta[t].latest = max(sta[t].latest,pas[i].start);
        sta[pas[i].end].off++;
    }
    int time = 0;
    for(int i = 1; i <= n;i++){
        sta[i].arrive = time;
        time = max(time,sta[i].latest);
        time += dis[i];
    }
    int maxnum, maxpos, tmp;
    while(k--){
        maxnum = 0;
        for(int i = 2;i <= n;i++){
            if(!dis[i - 1])continue;
            tmp = 0;
            for(int j = i;j <= n;j++){
                tmp += sta[j].off;
                if(sta[j].arrive <= sta[j].latest){
                    break;
                }
            }
            if(tmp > maxnum)maxnum = tmp,maxpos = i;
        }
        dis[maxpos-1]--;
        for(int i = maxpos;i <= n;i++){
            sta[i].arrive --;
            if(sta[i].arrive < sta[i].latest)break;
        }
    }
    for(int i = 1;i <= m;i++){
        ans += sta[pas[i].end].arrive - pas[i].start;
    }
    printf("%d",ans);
    return 0;
}