#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
const int N=20,M=10,MAXN=10;
int fs(int x)
{
	if(rand()%2==0)
		return -x;
	else
		return x;
}
string chose[10];
int main(){
	freopen("in.in","w",stdout);
	chose[1]="INSERT";
	chose[2]="DELETE";
	chose[3]="MAKE-SAME";
	chose[4]="REVERSE";
	chose[5]="GET-SUM";
	chose[6]="MAX-SUM";
    srand(time(NULL));
    int n=N,m=M;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++){
        int x=rand()%10;
        printf("%d ",x);
    }
    puts(""); 
    for(int i=1,opt,v,x,k;i<=m;i++)
	{
		opt=rand()%6+1;
		if(!n)
		{
			if((opt%2)==0)
				opt=1;
			else
				opt=6;
		}
		cout<<chose[opt]<<" ";
		switch(opt)
		{
			case 1:
				v=rand()%(n+1);
				k=rand()%N+1;
				printf("%d %d",v,k);
				for(int i=1;i<=k;i++)
					printf(" %d",fs( rand()%(MAXN+1) ));
				puts("");
				n+=k; 
				break;
			case 2:
				v=rand()%n+1;
				k=rand()%(n-v+1)+1;
				printf("%d %d\n",v,k);
				n-=k;
				break;
			case 3:
				v=rand()%n+1;
				k=rand()%(n-v+1)+1;
				x=fs( rand()%(MAXN+1) );
				printf("%d %d %d\n",v,k,x);
				break;
			case 4:
				v=rand()%n+1;
				k=rand()%(n-v+1)+1;
				printf("%d %d\n",v,k);
				break;
			case 5:
				v=rand()%n+1;
				k=rand()%(n-v+1)+1;
				printf("%d %d\n",v,k);
				break;
			default:
				puts("");
				break;
		}
    }
    return 0;
}
