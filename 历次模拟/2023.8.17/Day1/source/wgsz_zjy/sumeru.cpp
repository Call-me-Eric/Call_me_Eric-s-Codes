#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=i1;i0<=i2;++i0)
#define int long long 
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
#define dl  double 
dl b[5][4],a[4][5];
void out(){
	F(i,1,3){
		F(j,1,4)cout<<a[i][j]<<' ';
		cout<<'\n';
	}
	cout<<'\n';
}
bool solve(){
	F(i,1,3){
		dl o=a[i][i];
		if(!a[i][i]){
			F(j,i+1,3){
				if(a[j][i]){
					F(k,1,4){
						swap(a[i][k],a[j][k]);
					}
				}
			}
//			cout<<"**"<<'\n';
			o=a[i][i];
//			out();
		}
		if(o==0)continue;
		F(j,i+1,3){
			if(i==j||a[j][i]==0)continue;
			dl de=o/a[j][i];
			F(k,1,4){
				a[j][k]=a[i][k]-a[j][k]*de;
//				if(a[j][k]<1e-7)a[j][k]=0;
			}
		}
//		out();
		
	}
	
	F(i,2,3){
		dl o=a[i][i];
		if(a[i][i]==0){
			if(a[i][4])return 0;
			else continue;
		}
		
		F(j,1,i-1){
			if(a[j][i]){
				dl de=a[i][i]/a[j][i];
				F(k,1,4){
					a[j][k]=a[i][k]-a[j][k]*de;
//					if(a[j][k]<1e-7)a[j][k]=0;
				}
			}
		}
//		out();
	}
	F(i,1,3){
//		cout<<a[i][i]<<' '<<a[i][4]<<'\n';
		if(a[i][i]==0&&a[i][4]==0)continue;
		if(a[i][4]*a[i][i]<0)return 0;
	}
	//||(a[i][4]&&!a[i][i])
	return 1;
}
signed main(){
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
	int T;cin>>T;
	while(T--){
		F(i,1,4)
			F(j,1,3)cin>>b[i][j];
		F(i,1,3)
			F(j,1,4)a[i][j]=b[j][i];
//		out();
		cout<<(solve()?"YES":"NO")<<'\n';	
	}
		
	
	return 0;
}
/*
2
3 4 4 4 3 0 2 3 2 9 10 6
0 3 1 0 1 3 4 0 4 4 1 10 3 3
3 1 3 1 4 1 3 4 1 0 0 4
*/
