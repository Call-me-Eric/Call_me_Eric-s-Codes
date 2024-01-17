#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,q;
const int p=998244353;
vector<int> pri;
bitset<10000007> l;
vector<int> ver[1000016];
set<int> emty;
char s[100005];
inline int dfs(int now,int how,bool lim,bool pre,set<int> nw){
    if(now>n) return 1;
    ll re=0;
    if(pre==1) (re+=dfs(now+1,how,lim&(s[now]=='0'),1,nw))%=p;
    for(int i=0;i<=9;++i){
        if(lim==1&&i>s[now]-'0') break;
        if(pre==1&&i==0) continue;
        if(((how>>i)&1)==0) continue;
        set<int> nxt;
        nxt.clear();
        int hhow=how;
        for(int j:nw){
            int x=j*10+i;
            if(x>1e6) continue;
            for(int k:ver[x]){
                hhow&=(1<<10)-1-(1<<k);
            }
            nxt.insert(x);
            if(j<=1e5) nxt.insert(j);
        }
        for(int k:ver[i]){
            hhow&=(1<<10)-1-(1<<k);
        }
        nxt.insert(i);
        (re+=dfs(now+1,hhow,lim&(s[now]==('0'+i)),0,nxt))%=p;
    }
    return re;
}
int main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    scanf("%d",&q);
    for(int i=2;i<=1e7;++i){
        if(l[i]==0){
            // printf("%d\n",i);
            pri.push_back(i);
        }
        for(int j:pri){
            if(1ll*i*j>1e7) break;
            l[i*j]=1;
            if(i%j==0) break;
        }
    }
    for(int i:pri){
        ver[i/10].push_back(i%10);
    }
    int pre=(1<<0)+(1<<1)+(1<<4)+(1<<6)+(1<<8)+(1<<9);
    for(int i=1;i<=q;++i){
        scanf("%s",s+1);
        n=strlen(s+1);
        for(int i=n;i>=1;--i){
            if(s[i]=='0'){
                s[i]=='9';
            }
            else{
                s[i]--;
                break;
            }
        }
        int ans=p-dfs(1,pre,1,1,emty);
        scanf("%s",s+1);
        n=strlen(s+1);
        ans=(ans+dfs(1,pre,1,1,emty))%p;
        printf("%d\n",ans);
    }
    return 0;
}

