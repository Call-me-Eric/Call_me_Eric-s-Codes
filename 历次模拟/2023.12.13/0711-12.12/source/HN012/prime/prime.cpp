#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using db=double;
using vi=vector<int>;
using pii=pair<int,int>;

template<typename T>
T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f|=(c=='-'),c=getchar();
	while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
	return f?-x:x;
}

#define rdi read<int>
#define rdi64 read<i64>
#define fi first
#define se second
#define pb push_back

const int P[]={2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
const int PC=sizeof(P)/sizeof(int);

const int MX=110,B=10,pw10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

int len(int v){
	return floor(log10(v))+1;
}

struct stat{
	array<int,PC> a;
	int& operator[] (int x){return a[x];}
	const int& operator[] (int x) const{return a[x];}
	bool operator< (const stat &rhs) const{return a<rhs.a;}
	bool is_end() const{
		for(int i=0;i<PC;i++)
			if(a[i]>=len(P[i])) return true;
		return false;
	}
	stat trans(int d) const{
		stat nx=*this;
		for(int i=0;i<PC;i++)
			if(P[i]/pw10[(*this)[i]]%10==d) ++nx[i];
		return nx;
	}
};

// 1: start 0: end
map<stat,int> id;
int tot;
stat st[MX];
int tr[MX][B];
vector<pii> e[MX];

void init(){
	queue<int> q;
	id[st[tot=1]={0}]=1,q.push(1);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<B;i++){
			stat nx=st[x].trans(i);
			if(!nx.is_end()){
				if(!id.count(nx)) st[id[nx]=++tot]=nx,q.push(tot);
				tr[x][i]=id[nx],e[x].pb({i,id[nx]});
			}
		}	
	}
//	cerr<<tot<<endl;
}

const int N=1e5+10,MOD=998244353;

void add(int &a,int b){
	if((a+=b)>=MOD) a-=MOD;
}

bool chk(char s[]){
	int len=strlen(s),nw=1;
	for(int i=len-1;i>=0;i--){
		nw=tr[nw][s[i]-'0'];
		if(!nw) return false;
	}
	return true;
}

int calc(char s[]){
	int len=strlen(s);
	static int f[2][MX][2];
	memset(f,0,sizeof(f));
	f[0][1][0]=1;
	for(int i=len-1,nw=0;i>=0;i--,nw^=1){
		int cur=s[i]-'0';
		for(int j=1;j<=tot;j++){
			for(auto tmp:e[j]){
				int c=tmp.fi,to=tmp.se;
				for(int k=0;k<=1;k++)
					add(f[nw^1][to][c>cur||(k&&c==cur)],f[nw][j][k]);
			}
		}
		memset(f[nw],0,sizeof(f[nw]));
	}
	int ans=0;
	for(int j=1;j<=tot;j++)
		add(ans,f[len&1][j][0]);
	return ans;
}

char L[N],R[N];
void solve(){
	scanf("%s%s",L,R);
	i64 ans=calc(R)-calc(L)+chk(L);
	ans=(ans%MOD+MOD)%MOD;
	cout<<ans<<'\n';
}

int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	init();
	int T=rdi();
	while(T--) solve();
	return 0;
}
