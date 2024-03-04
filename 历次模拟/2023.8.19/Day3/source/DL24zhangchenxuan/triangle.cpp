#include<bits/stdc++.h>
#define read(a) scanf("%d",&a)
using namespace std;
const int N=105;
int n,k,cnt=1;
int a[N][N],dp[N],f[N];
int main(){
	freopen("triangle2.in","r",stdin);
	freopen("triangle.out","w",stdout);
	read(n);read(k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			read(a[i][j]);
		}
	}
	if(k==2){
		for(int i=n;i>1;i--){
			for(int j=1;j<i;j++){
				int s1=dp[j]+a[i][j],s2=dp[j+1]+a[i][j+1];
				if(s1<s2){
					dp[j]=s2;
					if(cnt)  f[j]=max(s1,f[j]+a[i][j]);
					else  f[j]=max(s1,f[j]+max(a[i][j+1],a[i][j]));
				} 
				else{
					dp[j]=s1;
					if(cnt)  f[j]=max(s2,f[j]+a[i][j+1]);
					else  f[j]=max(s2,f[j]+max(a[i][j+1],a[i][j]));
				}
				if(cnt==1&&a[i][j+1]-a[i][j]==0){
					cnt=0;
				}  
			}
		}
		printf("%d",f[1]+a[1][1]);
	}
	else{
		for(int i=n;i>1;i--){
			for(int j=1;j<i;j++){
				dp[j]=max(dp[j]+a[i][j],dp[j+1]+a[i][j+1]);
			}
		}
		printf("%d",dp[1]+a[1][1]);
	}
}
