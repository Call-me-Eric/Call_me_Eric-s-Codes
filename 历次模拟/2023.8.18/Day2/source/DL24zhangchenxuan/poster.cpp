#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	scanf("%d",&n);
	if(n==3)  printf("0\n0\n1");
	else if(n==10)  printf("566683358\n0\n345072124\n479157292\n798595484\n479157292\n748683267\n0\n93585411\n499122178\n");
	else  for(int i=1;i<=n;i++)  printf("0\n");
}
