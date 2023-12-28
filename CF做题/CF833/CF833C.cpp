#include<bits/stdc++.h>
#define int long long
using namespace std;
int L, R;
int l[20],r[20], lenl,lenr;
int ans, num[11], len;
bool check(int pos,bool lim1,bool lim2){
    if(!pos)return true;if(!lim1 && !lim2)return true;
    int down = lim1 ? l[pos] : 0;
    int up = lim2 ? r[pos] : 9;
    bool flag = false;
    for(int i = down;i <= up;i++){
        if(!num[i])continue;
        num[i]--;if(check(pos - 1,lim1 && (i == down),lim2 && (i == up)))flag = true;
        num[i]++;if(flag)break;
    }
    return flag;
}
void dfs(int u,int left){
    if(len > lenr)return;
    if(u == 9){
        if(left + len > lenr)return;
        num[u] = left;
        if(check(lenr,1,1)){
            ans++;
            // for(int i = 0;i <= 9;i++)printf("num[%lld]=%lld\n",i,num[i]);
            // getchar();
        }
        return;
    }
    for(int i = 0;i <= left;i++){
        if(u != 0)len += i;
        num[u] = i;
        dfs(u + 1,left - i);
        if(u != 0)len -= i;
        num[u] = 0;
    }
}

signed main(){
    scanf("%lld%lld",&L,&R);
    int tmp = lenl;lenl = 0;lenr = 0;
    for(int i = 1;i <= 19;i++){
        // printf("i=%lld L = %lld,R = %lld\n",i,L,R);
        if(L)lenl++;if(R)lenr++;
        // printf("lenl = %lld,lenr = %lld\n",lenl,lenr);
        l[i] = L % 10;L /= 10;
        r[i] = R % 10;R /= 10;
        // for(int j = lenl;j;j--)printf("%lld ",l[j]);puts("");
        // for(int j = lenr;j;j--)printf("%lld ",r[j]);puts("");
    }
    dfs(0, lenr); printf("%lld\n",ans);
    return 0;
}