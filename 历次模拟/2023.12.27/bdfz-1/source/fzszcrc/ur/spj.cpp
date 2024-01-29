#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sum=0,fh=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')fh=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		sum=sum*10+c-'0';
		c=getchar();
	}
	return sum*fh;
}
#define maxn 1000009
int main(){
	freopen("ur.out","r",stdin);
//	freopen(".out","w",stdout);
	int sum=0,fh=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')fh=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		sum+=c-'0';
		c=getchar();
	}
	cout<<sum;
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

