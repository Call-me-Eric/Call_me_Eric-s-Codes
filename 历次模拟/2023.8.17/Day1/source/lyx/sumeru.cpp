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
int T;
double c[6][6],b[6][6];
const double eps=1e-7;
bool vis[10];
bool guass(){
	int out=0;
	for(int i=1;i<=3;i++){
		int res=-1;
		if(vis[i])continue;
		for(int j=i;j<=3;j++){
			if(fabs(c[j][i])>eps){
				res=j;break;
			}
		}
		if(res==-1){
			out=i;break;
		}
		if(res!=i)swap(c[i],c[res]);
		for(int j=1;j<=4;j++)if(i!=j)c[i][j]/=c[i][i];
		c[i][i]=1;
		for(int j=1;j<=3;j++){
			if(i==j)continue;
			double op=c[j][i];
			for(int k=1;k<=4;k++)c[j][k]-=op*c[i][k];
		}
	}
	if(!out){
		for(int i=1;i<=3;i++){
			if(vis[i])continue;
			if(c[i][4]<0)return 0;
		}
		return 1;
	}
	if(out==2){
		if(vis[3])return 1;
		if(fabs(c[2][3])<eps&&fabs(c[3][3])<eps)return 1;
		int a3;
		if(fabs(c[2][3])<eps||fabs(c[3][3])<eps){
			a3=(fabs(c[2][3])<eps)?c[3][4]/c[3][3]:c[2][4]/c[2][3];	
		}
		else{
			if(fabs(c[2][4]/c[2][3]-c[3][4]/c[3][3])>eps)return 0;
			a3=c[3][4]/c[3][3];
		}
		if(c[1][4]-a3*c[1][3]>=0)return 1;
		else return 0;
	}
	else if(out==3){
		if(fabs(c[3][4])>eps)return 0;
		for(int i=1;i<=2;i++){
			for(int j=1;j<=3;j++)b[i][j]=c[i][j+1];
		}
		for(int i=1;i<=2;i++){
			int res=-1;
			for(int j=i;j<=3;j++){
				if(fabs(b[j][i])>eps){
					res=j;break;
				}
			}
			if(res!=i)swap(b[i],b[res]);
			for(int j=1;j<=3;j++)if(i!=j)b[i][j]/=b[i][i];
			b[i][i]=1;
			for(int j=1;j<=2;j++){
				if(i==j)continue;
				double op=b[j][i];
				for(int k=1;k<=3;k++)b[j][k]-=op*b[i][k];
			}
		}
		for(int i=1;i<=2;i++)if(b[i][3]<0)return 0;
		return 1;
	}
}
bool solve(){
    for(int i=1;i<=3;i++){
    	int fl=1;
        for(int j=1;j<=3;j++){
            c[j][i]=rd();
            if(c[j][i]>eps)fl=0;
        }
        vis[i]=fl;
    }
    for(int i=1;i<=3;i++)c[i][4]=rd();
    return guass();
}
signed main(){
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
    T=rd();
    while(T--){
        if(!solve())puts("NO");
        else puts("YES");
    }
	return 0;
}

