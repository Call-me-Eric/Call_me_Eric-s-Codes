#include<iostream>
#include<cstdio>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;
string a[100001];
string b[100001];
int main(){
//	freopen("P7075_6.out.txt","r",stdin);
	int n = 1;
	do{
		getline(cin,a[n]);
	}while(a[n++] != "End");
	n--;
//	freopen("1_P7075_6.out.txt","r",stdin);
	int m = 1;
	do{
		getline(cin,b[m]);
	}while(b[m++] != "End");
	m--;
	for(int i = 1,j = 1;i <= n && j <= m;i++,j++){
		if(a[i] != b[i]){
			printf("µÚ%dÐÐÓÐÎó\n",i);
		}
	}
	return 0;
}

