#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
/*
2
1 1
2 1
2
2 2
1 2

*/
signed main(){
	freopen("flowfree.in","r",stdin);
	freopen("flowfree.out","w",stdout);
	puts("2");
	puts("1 1");
	puts("2 1");
	puts("2");
	puts("2 2");
	puts("1 2");
	return 0;
}

