#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
unsigned int seed;
const int T[10]={0,0,0,0,1,1,0,0,0,0};
const int N[10]={10,13,13,13,16,16,16,16,16,16};
const int M[10]={10,13,(int)1e9,(int)1e9,(int)1e9,(int)1e9,(int)1e9,(int)1e9,(int)1e9,(int)1e9};
int main(){
	scanf("%u",&seed);
	mt19937 rng(seed);
	for(int ID=0;ID<10;ID++){
		FILE *I=fopen((to_string(ID)+".in").c_str(),"w");
		int n=N[ID],m=M[ID]-rng()%(M[ID]/100+1);
		fprintf(I,"%d %d\n",n,m);
		if (T[ID]){
			for(int i=1;i<=n;i++)fprintf(I,"%d ",(1<<i));
		}
		else{
			for(int i=1;i<=n;i++)fprintf(I,"%d ",rng()%(1<<30));
		}
		fclose(I);
		system(("partition < "+to_string(ID)+".in > "+to_string(ID)+".ans").c_str());
	}
	return 0;
}
