#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sum=0,fh=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')fh=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		sum=sum*10+c-'0';
		c=getchar();
	}
	return sum*fh;
}
#define maxn 709
#define mp make_pair
#define fi first
#define se second
#define pb push_back
const int mod=998244353;
int fp(int x,int y){
	int sum=1;
	while(y){
		if(y&1)sum=1ll*sum*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return sum;
}
int n,q,top;
void add(int &x,int y){x+=y;if(x>=mod)x-=mod;return ;}
struct equation{
	int w[maxn];
	void output(){
		cout<<"eq:";for(int i=1;i<=n+1;i++)cout<<w[i]<<" ";cout<<endl; 
	}
}eqs[maxn<<1];
int ltim[maxn<<1],rtim[maxn<<1],id[maxn]; 
vector<int > tre[maxn<<2];

int has[maxn],dcnts=0;
vector<pair<int ,equation > > marix;
void glass(equation &x,equation y,int zi){
	int det=1ll*x.w[zi]*fp(y.w[zi],mod-2)%mod;
	for(int k=1;k<=n+1;k++)add(x.w[k],mod-1ll*y.w[k]*det%mod);
//	cout<<"chk:"<<x.w[zi]<<" "<<zi<<endl;
	return ;
}
bool ins(equation x){
	int xid=0;
//	cout<<"ins:"<<endl;
//	x.output(); 
//	for(int i=1;i<=n;i++)if(has[i]!=-1)cout<<"qwq:"<<i<<":",marix[has[i]].se.output();
//	for(int i=1;i<=n;i++)if(has[i]!=-1)glass(x,marix[has[i]].se,i);
	for(auto i:marix)if(i.fi)glass(x,i.se,i.fi);
//	x.output(); 
	for(int i=1;i<=n;i++)if(x.w[i])xid=i;
//	cout<<"xid:"<<xid<<endl;
	if(xid)has[xid]=marix.size();
	else dcnts++;
	marix.pb(mp(xid,x));
	if(!xid&&x.w[n+1])return false;
	return true;
}
void pop(){
	if(marix.back().fi)has[marix.back().fi]=-1;
	else dcnts--;
	marix.pop_back();
	return ;
}
void cg(int ql,int qr,int eqi,int now=1,int l=0,int r=q){
	if(ql<=l&&r<=qr){tre[now].pb(eqi);return ;}
	int mid=(l+r)>>1;
	if(ql<=mid)cg(ql,qr,eqi,now<<1,l,mid);
	if(qr>mid)cg(ql,qr,eqi,now<<1|1,mid+1,r);
	return ; 
} 
int ans[maxn];
void work(int now=1,int l=0,int r=q){
	int cnt=0;
	for(auto i:tre[now]){
		cnt++;
		if(!ins(eqs[i])){
			while(cnt--)pop();
			for(int j=l;j<=r;j++)puts("No");
			return ;
		}
	}
	if(l<r){
		int mid=(l+r)>>1;
		work(now<<1,l,mid);work(now<<1|1,mid+1,r);
	}
	else{
		if(dcnts)puts("Many");
		else{
//			for(auto i:marix){
//				cout<<"id:"<<i.fi<<" vec:";
//				for(int j=1;j<=n+1;j++)cout<<i.se.w[j]<<" ";cout<<endl; 
//			}
//			printf("%d %d\n",(int)marix.size(),l);
			for(int i=marix.size()-1;i>=0;i--){
				auto now=marix[i];
				ans[now.fi]=now.se.w[n+1];
				for(int j=i+1;j<marix.size();j++){
					add(ans[now.fi],mod-1ll*ans[marix[j].fi]*now.se.w[marix[j].fi]%mod);
				}
				ans[now.fi]=1ll*ans[now.fi]*fp(now.se.w[now.fi],mod-2)%mod; 
			}
			for(int i=1;i<=n;i++)printf("%d%c",ans[i],(i==n?'\n':' '));
		}
	}
	while(cnt--)pop();
	return ;
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	top=n=read();q=read();
	for(int i=1;i<=n;i++){
		ltim[i]=0;id[i]=i;
		for(int j=1;j<=n+1;j++)eqs[id[i]].w[j]=read();
	}
	for(int i=1;i<=q;i++){
		int z=read();rtim[id[z]]=i-1;ltim[++top]=i;
		id[z]=top;
		for(int j=1;j<=n+1;j++)eqs[id[z]].w[j]=read();
	}
	for(int i=1;i<=n;i++)rtim[id[i]]=q;
	for(int i=1;i<=top;i++)cg(ltim[i],rtim[i],i);
	for(int i=0;i<=n;i++)has[i]=-1;work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

