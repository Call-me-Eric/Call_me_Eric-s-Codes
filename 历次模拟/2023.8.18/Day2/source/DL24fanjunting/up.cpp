#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e4+5;
int f[maxn];
struct node{
	int a,b;
}p[maxn];
struct node2{
	int l,r;
}q[maxn];
int n,qq;
signed main(){
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>qq;
	for(int i=1;i<=n;i++){
		cin>>p[i].a>>p[i].b;
	}
	for(int i=1;i<=qq;i++){
		cin>>q[i].l>>q[i].r;
	}
	for(int i=1;i<=qq;i++){
		int ans=0;
		for(int j=1;j<=n;j++){
			int kk=q[i].l+q[i].r;
			int pp=p[j].a+p[j].b;
			int mo=pp%kk;
//			cout<<i<<" "<<j<<" "<<kk<<" "<<pp<<'\n';
			if(mo==q[i].l||mo==q[i].r){
				ans++;
			}
		
		}
		cout<<ans<<'\n';
	}
	return 0;
}

