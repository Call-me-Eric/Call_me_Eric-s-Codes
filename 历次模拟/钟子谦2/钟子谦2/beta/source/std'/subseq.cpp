#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 233333
#define mp make_pair
#define pb push_back
int n,T;
char s[SZ];
const int MOD=998244353;
int f[200055];
int nx[200055][26];
void sol() {
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;++i)
        assert(islower(s[i])),
        s[i]-='a';
    for(int i=0;i<26;++i) nx[n+1][i]=n+1;
    for(int i=n;i>=1;--i) {
        memcpy(nx[i],nx[i+1],sizeof(nx[i]));
        nx[i][s[i]]=i;
    }
    for(int i=0;i<=n;++i) f[i]=0;
    f[0]=1;
    int ans=0;
    for(int i=0;i<=n;++i) {
        if(i&&nx[i+1][s[i]]>n)
            ans=(ans+f[i])%MOD;
        for(int k=0;k<26;++k) {
            int j=nx[i+1][k];
            if(j>n) continue;
            if(i&&nx[i+1][s[i]]<j) continue;
            f[j]=(f[j]+f[i])%MOD;
        }
    }
    printf("%d\n",ans);
}
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
    FO(subseq)
    scanf("%d",&T);
    while(T--) sol();
    cerr<<clock()<<"ms\n";
}