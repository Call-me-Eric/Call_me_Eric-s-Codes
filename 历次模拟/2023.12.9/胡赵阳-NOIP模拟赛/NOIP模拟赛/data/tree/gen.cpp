#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
unsigned int seed;
const int T[10]={0,0,0,0,1,2,2,0,0,0}; 
const int N[10]={18,(int)1e3,(int)1e3,(int)1e3,(int)5e5,(int)5e5,(int)5e5,(int)5e5,(int)5e5,(int)5e5};
int main(){
	scanf("%u",&seed);
	mt19937 rng(seed);
	for(int ID=0;ID<10;ID++){
		FILE *I=fopen((to_string(ID)+".in").c_str(),"w");
		int n=N[ID]-rng()%(N[ID]/100+1);
		fprintf(I,"%d\n",n);
		for(int i=1;i<=n;i++){
			if (T[ID]==2)fprintf(I,"%d ",rng()%min(n,2)+1);
			else fprintf(I,"%d ",rng()%n+1);
		}
		fprintf(I,"\n");
		int K=(int)sqrt(n);
		for(int i=1;i<n;i++){
			if (T[ID]==1)fprintf(I,"%d %d\n",i,i+1);
			else fprintf(I,"%d %d\n",i-rng()%min(i,K),i+1);
		}
		fclose(I);
		system(("tree < "+to_string(ID)+".in > "+to_string(ID)+".ans").c_str());
	}
	return 0;
}
