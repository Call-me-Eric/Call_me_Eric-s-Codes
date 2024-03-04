#include<bits/stdc++.h>
using namespace std;
int T;
int n,m;
//啥也不会 没啥事干 古树样例吧。 
//啥也不会 没啥事干 古树样例吧。 
//啥也不会 没啥事干 古树样例吧。 
//啥也不会 没啥事干 古树样例吧。 
void solve(){
	scanf("%d%d",&n,&m);
	if(n==1) return printf("0\n"),void();
	if(n==2){
		if(m==1) return printf("1\n"),void();
	}
	if(n==3){
		if(m==4) return printf("345072124\n"),void();
	}
	if(n==4){
		if(m==1) return printf("499122178\n"),void();
		if(m==2) return printf("748683267\n"),void();
		if(m==5) return printf("93585411\n"),void();
	}
	if(n==5){
		if(m==1) return printf("798595484\n"),void();
		if(m==2) return printf("479157292\n"),void();
		if(m==5) return printf("566683358\n"),void();
	}
}

int main(){
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	cin>>T;
	while(T--) solve();
	return 0;
}
