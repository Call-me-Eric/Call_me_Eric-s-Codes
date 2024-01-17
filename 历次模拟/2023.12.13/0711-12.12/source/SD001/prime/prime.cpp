/*#include<bits/stdc++.h>
using namespace std;
int read() {
    char ch=getchar();int res=0,fl=1;
    while(ch<'0'||ch>'9'){if(ch=='-') fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){res=res*10+ch-'0';ch=getchar();}
    return res*fl;
}
bool isprime(int x) {
    for(int i=2;i*i<=x;++i) if(x%i==0) return false;
    return true;
}
vector<int> ans[15];
void dfs(int now,int step,int base) {
    if(isprime(now)&&now>=base/10) ans[step-1].push_back(now);
    if(step==8) return ;
    dfs(now+base*0,step+1,base*10);
    dfs(now+base*4,step+1,base*10);
    dfs(now+base*6,step+1,base*10);
    dfs(now+base*9,step+1,base*10);
    return ;
}
int main() {
    freopen("prime.out","w",stdout);

    dfs(9,2,10);
    for(int i=1;i<=8;++i) {
        for(int j=0;j<ans[i].size();++j) printf("%d ",ans[i][j]);
        printf("\n");
    }
    return 0;
}*/
#include<bits/stdc++.h>
using namespace std;
int read() {
    char ch=getchar();int res=0,fl=1;
    while(ch<'0'||ch>'9'){if(ch=='-') fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){res=res*10+ch-'0';ch=getchar();}
    return res*fl;
}
int ans[1000005],tot=0;
void ins(int x) {ans[++tot]=x;}
queue<int> q,p;
bool check(int T,int S)//s from t
{
    while(T&&S) {
        if(T%10==S%10) S/=10;
        T/=10;
    }
    return !S;
}
int lim[26]={
2,
 3,
  5,
   7,
    11,
     41,
      61,
       19,
        89,
         881,
          991,
           409,
            449,
             499,
              9001,
               9049,
                9649,
                 6949,
                  9949, 
                   6469, 
                    60649,
                     666649,
                      946669,
                       60000049,
                        66000049,
                         66600049
};
int main() {
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    double T0=clock();
    q.push(0);
    for(int step=1,len=1;step<=9;++step,len*=10) {
        while(!q.empty()) {
            int now=q.front();
            q.pop();
            p.push(now);
            for(int k=1;k<=9;++k) {
                int to=now+len*k,fl=1;
                for(int i=0;i<26;++i) if(check(to,lim[i])) {
                    fl=0;
                    break;
                }
                if(fl) {
                    p.push(to);
                    ins(to);
                }
            }
        }
        swap(p,q);
    }
    ins(1000000000);
    //for(int i=1;i<=tot;++i) printf("%lld ",ans[i]);
    //printf("%d %d %lf",tot,ans[tot],clock()-T0);
    sort(ans+1,ans+1+tot);
   // for(int i=1;i<=100;++i) printf("%d ",ans[i]);
   // printf("\n");
    int T=read();
    while(T--) {
        int l=read()-1,r=read();
        int resl=upper_bound(ans+1,ans+1+tot,l)-ans-1,resr=upper_bound(ans+1,ans+1+tot,r)-ans-1;
        //printf("%d,%d\n",ans[resr],ans[resl]);
        printf("%d\n",resr-resl);

    }
    return 0;
}