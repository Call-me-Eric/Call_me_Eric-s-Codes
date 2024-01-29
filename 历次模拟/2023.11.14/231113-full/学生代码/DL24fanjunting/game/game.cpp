#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int a[maxn];
int n;
int l,r;
signed main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	cin>>l>>r;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	int now=0;
	for(int i=1;i<=n;i+=2){
		now+=a[i];
	}
	int now2=0;
	for(int i=n;i>0;i-=2){
		now2+=a[i];
	}
	if(now>now2) swap(now,now2);
	if(now<l||now2>r){
		cout<<"Alice";
	}
	else cout<<"Bob";
	return 0;
}

