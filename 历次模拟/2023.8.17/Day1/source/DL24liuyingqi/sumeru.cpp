#include<bits/stdc++.h>
using namespace std;
int a[5][5];
int T;
void solve(){
	for(int i=1;i<=4;i++)
		for(int j=1;j<=3;j++)
			scanf("%d",&a[i][j]);
	for(double i=0;i<=4.00;i+=0.025){
		for(double j=0;j<=4;j+=0.025){
			for(double k=0;k<=4;k+=0.025){
				bool flag1=(abs(a[1][1]*i+a[2][1]*j+a[3][1]*k-a[4][1])<0.05);
				bool flag2=(abs(a[1][2]*i+a[2][2]*j+a[3][2]*k-a[4][2])<0.05);
				bool flag3=(abs(a[1][3]*i+a[2][3]*j+a[3][3]*k-a[4][3])<0.05);
				if(flag1&&flag2&&flag3) return printf("YES\n"),void();
			}
		}
	}
	printf("NO\n");
}

int main(){
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
//	int _=pow(5,12);
//	printf("%d",_);
	cin>>T;
	while(T--) solve();
	return 0;
	//破防了呀！为什么不是整数x1,x2,x3! 
	//写不了一点呀！！！ 
}
