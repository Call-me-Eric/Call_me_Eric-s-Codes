#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=1e2+10;
int n,k;
int a[N][N];
multiset<int> rc[N][N];
vector<int> ans;
signed main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	n=rd();
	k=rd();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			a[i][j]=rd();
		}
	}
	rc[1][1].insert(a[1][1]);
	for(int i=1;i<n;i++){
		for(int j=1;j<=i;j++){
			int pos=0;
			for(auto it=rc[i][j].rbegin();it!=rc[i][j].rend();it++){
				int p=(*it);
				if(pos>k)break;
				rc[i+1][j].insert(p+a[i+1][j]);
				rc[i+1][j+1].insert(p+a[i+1][j+1]);
				pos++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		int pos=0;
		for(auto it=rc[n][i].rbegin();it!=rc[n][i].rend();it++){
			int p=(*it);
			if(pos>k)break;
			ans.push_back(p);
			pos++;
		}
	}
	sort(ans.begin(),ans.end(),greater<int>());
	printf("%d\n",ans[k-1]);
	return 0;
}

