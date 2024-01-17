#include <bits/stdc++.h>

using namespace std;

const int mod=998244353;
const int maxst=150000; 

int n; 
int add(int x,int y) {
    return (x+=y)>=mod?x-mod:x;
}
int p=0,cnt=0,ch[200][6]; 
unordered_map<long long,int> inq; 
int ed[200]; 
int dig[6]={0,1,4,6,8,9}; 
int digid[10]={0,1,-1,-1,2,-1,3,-1,4,5}; 
int trans[maxst+5][6],ntrans[maxst+5][6]; 
int endst=0;
int stnum=0; 
int poswei[1000]; 
int weinum[1000]; 
#define ull unsigned long long 
mt19937 rnd(20060426);
ull val[maxst*6+6];
int bel[maxst+5]; 



int num[27]={
11,
19,
41,
61,
89,
409,
449,
499,
881,
991,
6469,
6949,
9001,
9049,
9649,
9949,
60649,
666649,
946669,
60000049,
66000049,
66600049
}; 

const int maxn=1e5; 

char s[maxn+5]; 
int f[105][maxst+5][2]; 
int rt; 
int sol() {
    memset(f,0,sizeof(f));
    f[0][1][1]=1;
    for (int i=1;i<=n;i++) {
        int nwd=s[i]-'0'; 
        for (int lstst=1;lstst<=stnum;lstst++) {
            for (int o=0;o<2;o++) {
                if (!f[i-1][lstst][o]) continue ; 
                for (int j=0;j<6;j++) {
                    int nst=trans[lstst][j];
                    if (nst==-1) continue ; 
                    int d=dig[j];
                    if (o==1 && d>nwd) continue ;
                    int p=o;  
                    if (d<nwd) p=0;
                    f[i][nst][p]=add(f[i][nst][p],f[i-1][lstst][o]);  
                }
            }
        }
    } 
    int ans=0;
    for (int i=1;i<=stnum;i++) {
        ans=add(ans,add(f[n][i][0],f[n][i][1])); 
    }
    return ans; 
}
void solve() {
    cin>>(s+1); 
    n=strlen(s+1); 
    s[n]--;
    for (int i=n;i>=1;i--) {
        if (s[i]<'0') s[i]+=10,s[i-1]--; 
    }
    int ans=add(0,mod-sol()); 
    cin>>(s+1);
    n=strlen(s+1);
    ans=add(ans,sol());
    cout<<ans<<'\n'; 
}

int id(int x,int y) {
    return x*6+y; 
}
int top[maxst+5],toplen,ind[maxst+5],nbel[maxst+5]; 
void suo() {
    int nstnum=stnum; 
    for (int i=1;i<=stnum;i++) bel[i]=1; 
    for (int j=0;j<6;j++) {
        map<ull,int> mp; mp.clear(); 
        int nwnum=nstnum; 
        nstnum=0; 
        for (int i=1;i<=stnum;i++) {
            int v=trans[i][j];
            if (v==-1) v=0; else v=bel[v]; 
            ull info=val[bel[i]+maxst]^val[v]; 
            if (!mp[info]) {
                mp[info]=++nstnum; 
            }
            nbel[i]=mp[info]; 
        }
        for (int i=1;i<=stnum;i++) bel[i]=nbel[i],cout<<bel[i]<<' ';
        cout<<'\n'; 
    }
    rt=bel[1]; 
    stnum=nstnum; 
    for (int i=1;i<=stnum;i++) for (int j=0;j<6;j++) trans[i][j]=ntrans[i][j]; 
}
int main() {
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout); 
    memset(ch,-1,sizeof(ch)); 
    memset(trans,-1,sizeof(trans)); 
    for (int i=0;i<22;i++) {
        int a[100]={},len=0,x=num[i]; 
        while (x) {
            a[len++]=x%10; 
            x/=10; 
        }
        int p=0; 
        for (int i=len-1;i>=0;i--) {
            int o=digid[a[i]]; 
            if (ch[p][o]==-1) ch[p][o]=++cnt;
            p=ch[p][o]; 
        }
        ed[p]=1; 
    }
    int oknum=0,endpos=-1; 
    for (int i=0;i<cnt;i++) {
        if (!ed[i]) {
            poswei[i]=oknum;
            weinum[oknum]=i;
            oknum++; 
        }
    }
    endpos=oknum; 
    queue<long long> Q; 
    Q.emplace(1ll<<poswei[0]); 
    inq[1ll<<poswei[0]]=++stnum;
    while (!Q.empty()) {
        long long u=Q.front(); Q.pop(); 
        vector<long long> id;
        int uid=inq[u]; 
        if (u>>endpos&1ll) {
            endst=inq[u];
            continue ;
        }
        for (int i=0;i<oknum;i++) {
            if (u>>i&1ll) {
                id.emplace_back(weinum[i]); 
            }
        }
        for (int i=0;i<6;i++) {
            long long v=0; 
            v=u; 
            for (auto t:id) {
                int o=ch[t][i];
                if (o!=-1) {
                    if (!ed[o])
                        v|=(1ll<<poswei[o]); 
                    else v|=(1ll<<endpos);
                }
            }
            if (v>>endpos&1ll) v=(1ll<<endpos); 
            if (!inq[v]) {
                inq[v]=++stnum; 
                Q.emplace(v);
            }
            if (!(v>>endpos&1ll)) trans[uid][i]=inq[v];  
        }
    }
    mt19937 rnd(20060426);
    for (int i=0;i<=maxst*6;i++) {
        val[i]=rnd(); 
    }
   // suo();  
 //   cout<<stnum<<'\n'; 
    int T;
    cin>>T;
    while (T--) solve(); 
    return 0; 
}
