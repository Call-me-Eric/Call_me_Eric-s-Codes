#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=1e6+5;

int n;
vector<int> c[N];

int ls[N*4], lsi, d[N*4];
#define Find(x) (lower_bound(ls+1, ls+1+lsi, x)-ls)

bool check(int lambda){
	for(int i=1; i<=n; i++){
		for(int j:c[i]){
			ls[++lsi]=j;
//			ls[++lsi]=j-1;
//			ls[++lsi]=j+1;
			ls[++lsi]=j+lambda;
//			ls[++lsi]=j+lambda-1;
//			ls[++lsi]=j+lambda+1;
		}
	}
	sort(ls+1, ls+1+lsi); lsi=unique(ls+1, ls+1+lsi)-ls-1;
	for(int i=1; i<=n; i++){
		int mx=0;
		for(int j:c[i]){
			int l=Find(j), r=Find(j+lambda);
			for(int k=max(l, mx+1); k<=r; k++) d[k]++;
			mx=max(mx, r);
		}
	}
	bool flag=0;
	for(int i=1; i<=lsi; i++) if(d[i]==n){
		flag=1;
		break;
	}
	for(int i=1; i<=lsi; i++) d[i]=0; lsi=0;
	return flag;
}

signed main(){
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	n=rd();
	for(int i=1; i<=n; i++){
		int sz=rd();
		for(int j=1; j<=sz; j++) c[i].push_back(rd());
		sort(c[i].begin(), c[i].end());
	}
	int L=-1, R=2e9+5;
	while(R-L>1){
		int mid=(L+R)/2;
		if(check(mid)) R=mid;
		else L=mid;
	}
	printf("%lld\n", R);
	return 0;
}
