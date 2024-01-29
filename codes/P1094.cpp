#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct cmp{
	bool operator ()(int a,int b){
		if(a < b)return 1;
		else return 0;
	};
};
int p[30101], n, w, ans;
int main(){
	//开局发育 
	scanf("%d%d",&w,&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&p[i]);
	}
	sort(p + 1,p + 1 + n,cmp());
	int l = 1, r = n;
	//决赛圈 
	while(l <= r){
		if(p[l] + p[r] <= w){
			l++;
			r--;
			ans++;
		}
		else{
			r--;
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}

