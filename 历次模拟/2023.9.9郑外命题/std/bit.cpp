#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int mod  = 1e6+3;
const int maxn = 2000010;
mt19937 mrand(random_device{}());
int rnd(int x) { return mrand() % x;}
#ifdef ONLINE_JUDGE
#define debug(a...)
#endif
#define endl '\n'
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
void read(int &a){scanf("%d",&a);}
void read(long long &a){scanf("%lld",&a);}
void read(double &a){scanf("%lf",&a);}
void write(int &a){printf("%d ",a);}
void write(long long &a){printf("%lld ",a);}
void write(double &a){printf("%.10lf ",a);}
void I(){};
template<class T,class... A>void I(T &a,A&... x){read(a);I(x...);}
void O(){};
template<class T,class... A>void O(T &a,A&... x){write(a);O(x...);}
int fac[maxn],inv[maxn];
void initC(){
	fac[0]=1;
	for(int i=1;i<maxn;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[1]=1;
	for(int i=2;i<maxn;i++) inv[i]=1ll*(mod-(mod/i))*inv[mod%i]%mod;
	inv[0]=1;
	for(int i=1;i<maxn;i++) inv[i]=1ll*inv[i]*inv[i-1]%mod;
}
int C(int n,int m){
	if(n<m||m<0) return 0;
	if(n==m||m==0) return 1;
	if(fac[0]==0) initC();
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void setv(int &x,int f){
	if(x!=0&&x!=f){
		cout<<0<<endl;
		exit(0);
	}
	x=f;
}
vector<int> G[maxn];
bool vis[maxn];
int main(){
	int n,m;cin>>n>>m;
	vector<int> v(n-m+1);
	for(int i=0;i<n-m+1;i++){
		cin>>v[i];
	}
	vector<int> x(n);
	for(int i=1;i<n-m+1;i++){
		if(v[i]==v[i-1]-1){
			setv(x[i-1],1);
			setv(x[i+m-1],-1);
		}else if(v[i]==v[i-1]+1){
			setv(x[i-1],-1);
			setv(x[i+m-1],1);
		}else{
			G[i-1].push_back(i+m-1);
			G[i+m-1].push_back(i-1);
		}
	}
	for(int i=0;i<n;i++){
		if(vis[i]) continue;
		if(x[i]==0) continue;
		queue<int> q;
		q.push(i);
		while(!q.empty()){
			int now=q.front();q.pop();
			for(auto to:G[now]){
				if(x[to]){
					if(x[to]!=x[now]){
						cout<<0<<endl;
						return 0;
					}
				}
				if(vis[to]) continue;
				x[to]=x[now];
				vis[to]=1;
				q.push(to);
			}
		}
	}
	int tot=0,need=v[0];
	for(int i=0;i<m;i++){
		if(x[i]==0) tot++;
		if(x[i]==1) need--;
	}	
	
	cout<<C(tot,need)<<endl;
}