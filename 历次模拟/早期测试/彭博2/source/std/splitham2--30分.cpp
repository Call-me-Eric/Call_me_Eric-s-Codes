#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 505;
int n,X[1005],Y[1005];
bool cmp1(int a,int b){
	return X[a]<X[b];
}
bool cmp2(int a,int b){
	return Y[a]<Y[b];
}
vector<int> A[N<<2],indep[N];
vector<double> dp[N][N<<2];
int mxdep,bel[N][N];
void init(int k,int dep,vector<int> id,int type) {
	//cout<<k<<' '<<dep<<'\n';
	A[k]=id;
	indep[dep].push_back(k);
	mxdep=max(mxdep,dep);
	for(int i:id)bel[dep][i]=k;
	if(id.size()==1)return ;
	vector<int> S,T;
	S = id;
	if(type==0)
		sort(S.begin(),S.end(),cmp1);
	else
		sort(S.begin(),S.end(),cmp2);
	int K = id.size()/2;
	for(int i=1;i<=K;i++){
		T.push_back(S.back());
		S.pop_back();
	}
	sort(S.begin(),S.end());
	sort(T.begin(),T.end());
	init(k<<1,dep+1,S,type^1);
	init(k<<1|1,dep+1,T,type^1);
}
/*void Dp(int k,int id){
	if(A[id].size()==1){
		dp[k][id].push_back(hypot(X[k]-X[A[id][0]],Y[k]-Y[A[id][0]]));
		return ;
	}
	Dp(k,id<<1);
	Dp(k,id<<1|1);
	for(int i=0;i<A[id<<1].size();i++){
		for(int j=0;j<A[id<<1|1].size();j++){
			dp[k][j]=min(dp[k])
		}
	}
}*/
double u[N];
const double eps=1e-9;
void Print(int k,int jj,int l){
	if(A[jj].size()==1){
		cout<<A[jj][0]<<' ';
		return ;
	}
	int p=A[jj][l];
	double rw=dp[k][jj][l];
	for(int i=0;i<A[jj<<1].size();i++){
		for(int j=0;j<A[jj<<1|1].size();j++){
			if(A[jj<<1|1][j]!=p)continue;
			double w=dp[k][jj<<1][i]+dp[A[jj<<1][i]][jj<<1|1][j];
			if(fabs(w-rw)<eps){
				Print(k,jj<<1,i);
				Print(A[jj<<1][i],jj<<1|1,j);
				return ;
			}
		}
	}
	for(int i=0;i<A[jj<<1|1].size();i++){
		for(int j=0;j<A[jj<<1].size();j++){
			if(A[jj<<1][j]!=p)continue;
			double w=dp[k][jj<<1|1][i]+dp[A[jj<<1|1][i]][jj<<1][j];
			if(fabs(w-rw)<eps){
				Print(k,jj<<1|1,i);
				Print(A[jj<<1|1][i],jj<<1,j);
				return ;
			}
		}
	}
}
int main(){
//	freopen("data101.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>X[i]>>Y[i];
	}
	vector<int> c;
	for(int i=1;i<=n;i++)c.push_back(i);
	init(1,1,c,0);
	fill(u+1,u+n+1,1e18);
	for(int ii=mxdep;ii>=1;ii--){
		for(int jj:indep[ii]){
			for(int k=1;k<=n;k++){
				if(A[jj].size()==1){
					dp[k][jj].push_back(hypot(X[k]-X[A[jj][0]],Y[k]-Y[A[jj][0]]));
					continue;
				}
				for(int i=0;i<A[jj<<1].size();i++){
					for(int j=0;j<A[jj<<1|1].size();j++){
						u[A[jj<<1|1][j]]=min(u[A[jj<<1|1][j]],dp[k][jj<<1][i]+dp[A[jj<<1][i]][jj<<1|1][j]);
					}
				}
				for(int i=0;i<A[jj<<1|1].size();i++){
					for(int j=0;j<A[jj<<1].size();j++){
						u[A[jj<<1][j]]=min(u[A[jj<<1][j]],dp[k][jj<<1|1][i]+dp[A[jj<<1|1][i]][jj<<1][j]);
					}
				}
				for(int i:A[jj])dp[k][jj].push_back(u[i]),u[i]=1e18;
			}
		}
	}
	double ans=1e18;
	int mnp=0,mmnp=0;
	for(int k=1;k<=n;k++){
		for(int l=0;l<n;l++){
			if(dp[k][1][l]<ans){
				ans=dp[k][1][l];
				mnp=k;
				mmnp=l;
			}
		}
	}
	printf("%.2lf\n",ans);
//	Print(mnp,1,mmnp);
//	for(int i=1;i<=n<<2;i++){
//		if(!A[i].size())continue;
//		for(auto x:A[i])cout << x << ' ';
//		cout << endl;
//	}
	
}
