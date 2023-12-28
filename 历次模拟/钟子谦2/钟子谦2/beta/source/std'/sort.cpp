#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 1233333
#define mp make_pair
#define pb push_back
int n,a[SZ],st[SZ],sn,s0[SZ],sn0;
int m=1;
int cur[SZ],cn,dz[SZ];
int aaa[SZ];
ll su=0;
void edt(int x,int t) {
    su-=aaa[x];
    su+=(aaa[x]=t);
}
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
    FO(sort)
    scanf("%d",&n);
    for(int i=1;i<=n;++i) {
        scanf("%d",a+i);
        {
        int l=1,r=sn+1;
        //find first <...
        while(l<r){
            int m=(l+r)>>1;
            if(a[st[m]]<a[i]) r=m;
            else l=m+1;
        }
        dz[i]=sn+3-l; // first one doesnt count
        // cout<<i<<":"<<dz[i]<<"yydz\n";
        }
        bool nw=(a[i]<a[m]);
        if((sn==0||a[st[sn]]>a[i])&&i!=1) st[++sn]=i;
        if(sn==0||a[s0[sn0]]>a[i]) s0[++sn0]=i;
        //cur: stack of a2 a3 ... a[m-1] a1 a[m+1] a[m+2] ... a[i]
        //st: stack of a1 ... ai
        if(!nw||i==1) {
            if(m==1) {
                edt(i,dz[i]); // not even trying
                // dz[i]=1; // how many in st is smaller than cur?
            }
            else {
                int l=1,r=cn+1;
                //find first <...
                while(l<r){
                    int m=(l+r)>>1;
                    if(a[cur[m]]<a[i]) r=m;
                    else l=m+1;
                }
                edt(i,cn+3-l);
                if(cn==0||a[cur[cn]]>a[i]) cur[++cn]=i;
            }
        }
        else {
            if(m==1) { // reset cur
                cn=0;
                for(int ii=2;ii<=i;++ii) {
                    if(ii!=i) edt(ii,dz[ii]);
                    int j=(ii==i)?1:ii;
                    if(cn==0||a[cur[cn]]>a[j]) cur[++cn]=j;
                }
            }
            else {
                // new cur: old stack with everything >m popped, then a[m]
                while(cn&&(cur[cn]<2||cur[cn]>m-1)) --cn;
                cur[++cn]=m;
                for(int t=m;t<i;++t) edt(t,dz[t]);
            }
            // in cur, find first <a1
            {
            int l=1,r=cn+1;
            while(l<r){
                int m=(l+r)>>1;
                if(a[cur[m]]<a[1]) r=m;
                else l=m+1;
            }
            // cout<<l<<"?\n";
            edt(i,cn+3-l);
            }
            // cout<<"updated nice!\n";
            m=i;
        }
        edt(1,sn0);
        // for(int j=1;j<=cn;++j)
        //     cout<<cur[j]<<" ";
        // cout<<"C"<<endl;
        // for(int j=1;j<=i;++j)
        //     cout<<aaa[j]<<" ";
        // cout<<endl;
        // cout<<"aa="<<su<<"\n";
        printf("%lld ",su);
    }
}
/*
Idea:
1:  am a1 a2 ...


5 4 2
2 4 5
4 2 5


m=1: a2 a3 ... a[i-1] a1 [ai]

For i<m: a2 a3 ... a[i-1] am [ai]
For i=m: a2 a3 ... a[m-1] am [a1]
For i>m: a2 a3 ... a[m-1] a1 a[m+1] a[m+2] ... a[i-1] am [ai]

T=Stack(a2,a3...a[m-1] a1 a[m+1]...a[i-1])+1


a2 a3 ... a[m-1] am

Bad newcomers affect nobody but itself!
Just need to figure out the T

Latest noob?
*/