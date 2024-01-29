#include<cstdio>
#include<cstdlib>
#define max(a,b) a > b ? a : b
using namespace std;
int m, s, t;
int run, magic, flag = 1;
int main(){
	scanf("%d%d%d",&m,&s,&t);
	for(int i = 1;i <= t;i++){
		run += 17;
		if(m >= 10){
			m -= 10;
			magic += 60;
		}
		else {
			m += 4;
		}
		run = max(run,magic);
		if(run >= s){
			printf("Yes\n%d",i);
			flag = 0;
			break;
		}
	}
	if(flag)printf("No\n%d",run);
	return 0;
}

