#include<bits/stdc++.h>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
const int mod=1e9+7;
int pri[114514]={0,11,19,41,61,89,101,109,149,181,401,409,449,461,491,499,601,691,809,881,991,1009,1049,1069,1409,1481,1601,1609,1669,1699,1801,4001,4049,4481,4649,4691,4801,4909,4969,6091,6469,6481,6691,6869,6899,6949,6991,8009,8069,8081,8609,8669,8681,8699,8849,9001,9049,9091,9649,9901,9949,10009,10069,14009,14081,14669,14699,14869,16001,16069,16481,16649,16901,16981,18049,18481,18869,40009,40099,40609,40699,40801,40849,44699,46049,46091,46099,46649,46681,46901,48049,48091,48481,48649,48869,49009,49069,49081,49481,49669,49681,49801,60091,60649,60869,60901,64081,64609,64849,64901,66949,68099,68669,68909,69001,69481,80669,80681,80849,81001,81649,81869,84869,86069,86969,86981,88001,88469,88801,88969,90001,90469,90481,90901,91081,94009,94849,94949,96001,98801,98869,99469},p[6]={0,1,4,6,8,9},cnt=140;
int dp[6][6][6][6][6][2],v[114];
int calc(int x){
	int r=x,ct=(x==(v[1]=0));
	while(r)v[++ct]=r%10,r/=10;
	for(int i=1;i<=ct;i++)cout<<v[i];cout<<endl;
	for(int i=0;i<6;i++)
		for(int j=0;j<2;j++)
			for(int a=0;a<6;a++)
				for(int b=0;b<6;b++)
					for(int c=0;c<6;c++)
						for(int d=0;d<6;d++)dp[i][a][b][c][d][j]=0;
	dp[0][0][0][0][0][1]=1;
	for(int i=1;i<=ct;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<6;k++)
				for(int a=0;a<6;a++)
					for(int b=0;b<6;b++)
						for(int c=0;c<6;c++)
							for(int d=0;d<6;d++){
								int up=j||(p[k]>v[i]),flg=false;
								if(!dp[i-1][a][b][c][d][j])continue;
								if((i==ct)&&(p[k]>v[i]||(j&&p[k]==v[i])))continue;
								for(int l=1;l<=cnt&&(!flg);l++){
									int val=pri[l];
									if(val>10000){
										if(p[k]==val/10000)
											if(p[d]==(val%10000)/1000)
												if(p[c]==(val%1000)/100)
													if(p[b]==(val%100)/10)
														if(p[a]==val%10)flg=true;
										continue;
									}
									if(val>1000){
										if(p[k]==val/1000)
											if(p[d]==(val%1000)/100)
												if(p[c]==(val%100)/10)
													if(p[b]==val%10)flg=true;
										continue;
									}
									if(val>100){
										if(p[k]==val/100)
											if(p[d]==(val%100)/10)
												if(p[c]==val%10)flg=true;
										continue;
									}
									if(p[k]==val/10)
										if(p[d]==val%10)flg=true;
								}
								if(flg)continue;
								(dp[i][b][c][d][k][up]+=dp[i-1][a][b][c][d][j])%=mod;
							}
	int ans=0;
	for(int i=1;i<=ct;i++)
		for(int j=0;j<2;j++)
			for(int a=0;a<6;a++)
				for(int b=0;b<6;b++)
					for(int c=0;c<6;c++)
						for(int d=1;d<6;d++)
							(ans+=dp[i][a][b][c][d][j])%=mod;
	return ans;
}
void solve(){
	int l=read(),r=read();
	printf("%d %d %d\n",calc(r),calc(l-1),((calc(r)-calc(l-1))%mod+mod)%mod);
}
signed main(){
	file("prime");
	int T=read();while(T--)solve();
	return 0;
}
