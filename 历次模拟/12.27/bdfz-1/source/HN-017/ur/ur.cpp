#include <bits/stdc++.h>
// #define ll long long
using namespace std;

template<typename ...Args>
signed debug(const char*str,Args ...args){return fprintf(stderr,str,args...);}

inline static int read(){
    int sum=0; bool neg=false; char ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=(sum<<3)+(sum<<1)+(ch^48),ch=getchar();
    return neg?-sum:sum;
}


const int prime[168]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};

int n,k;
int f[200],g[200],tot;
bitset<1000000> flag;
bitset<1000000> ans; int acnt;

void dfs(int now,int cnt,int begin){
    while(g[begin]+cnt>k) begin++;
    if(f[begin]==now) begin++;
    if(begin==tot+1){
        if(acnt<cnt) ans=flag,acnt=cnt;
        if((double)clock()/CLOCKS_PER_SEC>0.8){
            for(int i=0;i<n;i++) printf("%d",(int)ans[i]);
            exit(0);
        } return;
    }
    for(int i=begin;i<=tot;i++){
        bool qwq=1;
        for(int j=1,p=now;j<=g[i];j++,p+=f[i]) if(flag[p]){qwq=0;break;}
        if(qwq){
            for(int j=1,p=now;j<=g[i];j++,p+=f[i]) flag[p]=1;
            dfs(now+1,cnt+g[i],begin);
            for(int j=1,p=now;j<=g[i];j++,p+=f[i]) flag[p]=0;
        }
    }
    dfs(now+1,cnt,begin);
    return;
}

signed main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    n=read(),k=read(); int t=n;
    if(n==k){
        for(int i=1;i<=n;i++) putchar('1');
        return 0;
    }
    if(k==0){
        for(int i=1;i<=n;i++) putchar('0');
        return 0;
    }
    for(int i=0;i<168;i++){
        if(t%prime[i]==0){
            tot++,f[tot]=n/prime[i],g[tot]=prime[i];
            do t/=prime[i]; while(t%prime[i]==0);
        }
    } if(t!=1) tot++,f[tot]=n/t,g[tot]=t;
    reverse(f+1,f+tot+1),reverse(g+1,g+tot+1);
    
    if(tot==1){
        for(int i=k/g[1]-1;i>=0;i--) for(int j=1,p=i;j<=g[1];j++,p+=f[1]) ans[p]=1;
        for(int i=0;i<n;i++) printf("%d",(int)ans[i]);
    }else if(tot==2 && g[1]*g[2]==n){
        if(k%g[1]<k%g[2]) for(int i=k/g[1]-1;i>=0;i--) for(int j=1,p=i;j<=g[1];j++,p+=f[1]) ans[p]=1;
        else for(int i=k/g[2]-1;i>=0;i--) for(int j=1,p=i;j<=g[2];j++,p+=f[2]) ans[p]=1;
        for(int i=0;i<n;i++) printf("%d",(int)ans[i]);
    }else{
        dfs(0,0,1);
        for(int i=0;i<n;i++) printf("%d",(int)ans[i]);
    }
    
    return 0;
}