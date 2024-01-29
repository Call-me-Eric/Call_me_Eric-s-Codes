#include <cstdio>
using namespace std;
int n, ans, t;
int main(){
	while(scanf("%d",&n) != EOF){
		int max = -90;
		ans = 90;
		for(int i = 1;i <= n;i++){
			scanf("%d",&t);
			if(t > max){
				ans += max;
				max = t;
			}
			else{
				ans += t;
			}
		}
		double tmp = (ans + max) * 1.0 / 2;
		if(ans > max){printf("%.1lf\n",tmp);}
		else printf("%.1lf\n",ans * 1.0);
	}
	return 0;
}

