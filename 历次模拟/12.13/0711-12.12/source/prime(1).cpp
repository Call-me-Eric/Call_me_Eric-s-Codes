#include<bits/stdc++.h>
using namespace std;int t,num[6],b[10],bs[10],ans[10000001],cnt,p[100000001],pr[100001],prim[100001],cntt;
long long l,r;
int check(int x){
	for(int i=1;i<=cnt;i++)if(ans[i]>x)return i-1;
	return cnt;
}
int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	num[0]=0,num[1]=1,num[2]=4,num[3]=6,num[4]=8,num[5]=9;b[0]=bs[0]=p[1]=p[9]=1;cin>>t;
	for(int i=2;i<=100000;i++)if(!pr[i]){for(int j=2*i;j<=100000;j+=i)pr[j]=1;prim[++cntt]=i;}
	for(int i=1;i<=9;i++)b[i]=b[i-1]*6,bs[i]=bs[i-1]*10;ans[++cnt]=1;
	for(int i=2;i<=10077696;i++){
		int x=0,k=i;for(int j=1;j<=9;j++){
			x+=bs[j-1]*num[k%b[j]/b[j-1]];
			k-=k%b[j];if(!k)break;
		}int xx=x;if(x%2==0){
			while(x){
				x/=10;
				if(x%2==1){
					if(p[x])ans[++cnt]=xx;
					break;
				}
			}if(!x)ans[++cnt]=xx;
			continue;
		}int f=1,ip=1;
		for(int j=9;j>=1;j--){
			if(x>bs[j])if(!p[x%bs[j]+x/bs[j+1]*bs[j]])f=0;
			if(!f)break;
		}if(!f)continue;
		for(int j=2;j<=cntt;j++){
			if(prim[j]>sqrt(x))break;
			if(x%prim[j]==0){ip=0;break;}
		}
		if(!ip){
			ans[++cnt]=x;
			if(x<=1e8)p[x]=1;
		}
	}ans[++cnt]=1e9;
	while(t--){
		cin>>l>>r;
		cout<<check(r)-check(l-1)-1<<endl;
	}
	return 0;
}
