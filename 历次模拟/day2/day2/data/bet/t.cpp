#include <bits/stdc++.h>
using namespace std;
int T,n,m,p,k;
char s[110];
char name[]="ex_bet";
int main(){
	for(int i=3;i<=3;i++){
		do{
			sprintf(s,"data.exe>%s%d.in",name,i),system(s);
			sprintf(s,"val.exe < %s%d.in",name,i),system(s);
			int st=clock();
			sprintf(s,"std.exe<%s%d.in>%s%d.ans",name,i,name,i),system(s);
			cerr<<"test "<<i<<": "<<clock()-st<<"\n";
			st=clock();
			sprintf(s,"bru.exe<%s%d.in>%s%d.out",name,i,name,i),system(s);
			cerr<<"test "<<i<<": "<<clock()-st<<"\n";
			sprintf(s,"fc %s%d.out %s%d.ans",name,i,name,i);
//			sprintf(s,"chk.exe %s%d.in %s%d.out %s%d.ans",name,i,name,i,name,i);
			if(system(s)) break;
		}while(1);
	}
}

