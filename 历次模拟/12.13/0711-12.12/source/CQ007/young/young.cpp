#include<iostream>
#include<queue>
#include<assert.h>
#include<map>
using namespace std;
const int MAXN=110,MAXM=1e6+100;
struct Que {
	int a[MAXN],n;
	bool operator <(const Que P) const {
		if(n!=P.n) return n<P.n;
		for(int i=1;i<=n;i++) {
			if(a[i]!=P.a[i]) return a[i]<P.a[i];
		}
		return 0;
	}
};
int n,m,q,k,a[MAXN],b[MAXN],f[MAXM][2],tot;
map<int,Que> mp;
map<Que,int> rmp;
int main() {
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>b[i];
	cin>>q;
	while(q--) {
		cin>>k;
		mp.clear(),rmp.clear(),tot=0;
		Que S; S.n=n; for(int i=1;i<=n;i++) S.a[i]=a[i];
		mp[++tot]=S,rmp[S]=tot; f[tot][0]=1;
		for(int p=1;p<=k;p++) {
			// cout<<"CEN "<<p<<endl;
			for(int j=1;j<=tot;j++) f[j][p&1]=0;
			for(int j=tot;j;j--) {
				Que now=mp[j];
				for(int i=1;i<=now.n;i++) {
					if(i==1||now.a[i-1]>now.a[i]) {
						++now.a[i];
						if(rmp.find(now)==rmp.end()) mp[++tot]=now,rmp[now]=tot;
						f[rmp[now]][p&1]+=f[j][!(p&1)];
						--now.a[i];
					}
					if(i==now.n||now.a[i+1]<now.a[i]) {
						--now.a[i]; 
						if(i==now.n&&!now.a[i]) --now.n;
						if(rmp.find(now)==rmp.end()) mp[++tot]=now,rmp[now]=tot;
						f[rmp[now]][p&1]+=f[j][!(p&1)];
						if(i==now.n+1&&!now.a[i]) ++now.n;
						++now.a[i];
					}
				}
				now.n++,now.a[now.n]=1;
				if(rmp.find(now)==rmp.end()) mp[++tot]=now,rmp[now]=tot;
				f[rmp[now]][p&1]+=f[j][!(p&1)];
			}
			// for(int j=1;j<=tot;j++) {
			// 	if(!f[j][p&1]) continue;
			// 	cout<<mp[j].n<<' '<<f[j][p&1]<<endl;
			// 	for(int i=1;i<=mp[j].n;i++) cout<<mp[j].a[i]<<' '; cout<<endl;
			// }
		}
		Que T; T.n=m; for(int i=1;i<=m;i++) T.a[i]=b[i];
		assert(rmp.find(T)!=rmp.end());
		cout<<f[rmp[T]][k&1]<<endl;
	}
	return 0;
}