#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

const int maxk=20;
const int maxn=1e6+5;

int p[maxk],t;
bitset<maxn> ok[maxk];
char ans[maxn];
int main(){
    #ifndef dengyaotriangle
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    #endif
    ios::sync_with_stdio(0);cin.tie(0);
    int n,k;
    cin>>n>>k;
    int cn=n;
    for(int i=2;i<=n;i++){
        if(cn%i==0){
            p[t++]=i;
            while(cn%i==0)cn/=i;
        }
    }
    ok[0][0]=1;
    for(int i=0;i<t;i++){
        ok[i+1]=ok[i];
        for(int j=p[i];j<=n;j++){
            ok[i+1][j]=ok[i][j]|ok[i+1][j-p[i]];
        }
    }
    while(!ok[t][k]||!ok[t][n-k])k--;
    cerr<<k<<endl;
    int ork=k;
    for(int i=0;i<n;i++)ans[i]='0';
    int r=__gcd(k,n);
    if(r>1){
        int q=n/r;
        for(int i=0;i<k/r;i++){
            for(int j=0;j<r;j++){
                int p=i+j*q;
                ans[p]='1';
            }
        }
        cout<<ans;
        return 0;
    }
    assert(t>=2);
    int m=n/p[0]/p[1];
    assert(m!=1);
    bool flg=0;
    if(k*2>n){
        k=n-k;
        flg=1;
    }
    if(k<(p[0]-1)*(p[1]-1)){
        int cur=k;
        for(int i=t-1;i>=0;i--){
            int c=-1;
            for(int j=0;;j++){
                if(ok[i][cur-j*p[i]]){
                    c=j;
                    cur-=j*p[i];
                    break;
                }
            }
            int l=n/p[i],ri=p[i];
            for(int i=0;i<l;i++){
                if(!c)break;
                bool ok=1;
                for(int j=0;j<ri;j++){
                    if(ans[i+j*l]=='1')ok=0;
                }
                if(ok){
                    for(int j=0;j<ri;j++){
                        ans[i+j*l]='1';
                    }
                    c--;
                }
            }
            assert(c==0);
        }
    }else{
        int a=INT_MIN,b=INT_MIN;
        for(int i=0;i<p[0];i++){
            int ca=(k-p[1]*i)/p[0];
            if(ca*(long long)p[0]+i*(long long)p[1]==k){
                a=ca;b=i;
                break;
            }
        }
        //a p[0]+ b p[1]==k
        int l1=n/p[1];
        for(int i=0;i<b;i++){
            int si=i*m;
            for(int j=0;j<p[1];j++){
                ans[si+j*l1]='1';
            }
        }
        int l0=n/p[0];
        for(int i=0;i<l0;i++){
            if(!a)break;
            bool ok=1;
            for(int j=0;j<p[0];j++){
                if(ans[i+j*l0]=='1')ok=0;
            }
            if(ok){
                a--;
                for(int j=0;j<p[0];j++){
                    ans[i+j*l0]='1';
                }
            }
        }
        assert(a==0);
    }
    for(int i=0;i<n;i++)ans[i]^=flg;
    cout<<ans;
    for(int i=0;i<n;i++)ork-=ans[i]=='1';
    assert(ork==0);
    return 0;
}