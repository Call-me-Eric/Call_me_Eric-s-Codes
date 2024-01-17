#include<bits/stdc++.h>
using namespace std;
#define get() (rng()&1 ? rng()%n+1 : a[rng()%a[0]+1])
typedef long long ll;
unsigned int seed;
const int T[10]={0,0,0,0,0,1,1,0,0,0};
const int N[10]={(int)1e4,(int)1e4,(int)5e4,(int)5e4,(int)5e4,(int)1e6,(int)1e6,(int)1e6,(int)1e6,(int)1e6};
const int M[10]={(int)1e3,(int)1e3,(int)5e4,(int)5e4,(int)5e4,(int)1e6,(int)1e6,(int)1e6,(int)1e6,(int)1e6};
int a[1000005];
int main(){
	scanf("%u",&seed);
	mt19937 rng(seed);
	for(int ID=0;ID<10;ID++){
		FILE *I=fopen((to_string(ID)+".in").c_str(),"w");
		int n=N[ID]-rng()%(N[ID]/100+1),m=M[ID]-rng()%(M[ID]/100+1),q=M[ID]-rng()%(M[ID]/100+1);
		fprintf(I,"%d %d %d\n",n,m,q);
		a[0]=(int)sqrt(n);
		for(int i=1;i<=n;i++)a[i]=i;
		shuffle(a+1,a+n+1,rng);
		for(int i=1;i<=m;i++){
			int p=(T[ID] ? rng()%2+2 : rng()%3+1);
			if (p==1){
				int x=get(),y=get();
				while (x==y)x=get(),y=get();
				fprintf(I,"1 %d %d\n",x,y);
			}
			if (p==2){
				int l=rng()%n+1,r=rng()%n+1;
				if (l>r)swap(l,r);
				fprintf(I,"2 %d %d %d\n",l,r,rng()%n+1);
			}
			if (p==3)fprintf(I,"3 %d\n",get());
		}
		for(int i=1;i<=q;i++){
			int l=rng()%m+1,r=rng()%m+1;
			if (l>r)swap(l,r); 
			fprintf(I,"%d %d\n",l,r);
		} 
		fclose(I);
		system(("operate < "+to_string(ID)+".in > "+to_string(ID)+".ans").c_str());
	}
	return 0;
}
