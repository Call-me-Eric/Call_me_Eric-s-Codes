#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=5e4+10;
int n,in[N];
struct koishi{
	int p[6],f;
}a[N];
inline bool check(const koishi &a,const koishi &b){
	for(int i=1;i<=5;i++)if(a.p[i]>b.p[i])return 0;
	return 1;
}
vector<int> g[N];
int dp[N],S;
signed main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	n=rd();S=n+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=5;j++)a[i].p[j]=rd();
		a[i].f=rd();
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(i==j)continue;
			if(check(a[i],a[j])){
				in[j]++;
				g[i].push_back(j);
				//cerr<<"* "<<i<<' '<<j<<endl;
			}
		}
		g[S].push_back(i);in[i]++;
	}
	queue<int> q;
	q.push(S);
	while(!q.empty()){
		int k=q.front();q.pop();
		for(int i:g[k]){
			dp[i]=max(dp[i],dp[k]);
			in[i]--;
			if(in[i]==0){
				dp[i]+=a[i].f;
				q.push(i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<dp[i]<<endl;
	}
	return 0;
}

