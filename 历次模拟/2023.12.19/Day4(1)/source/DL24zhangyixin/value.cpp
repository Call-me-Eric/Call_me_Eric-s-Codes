#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int n,a[N],b[N],aa[N],bb[N],vis[N],visb[N];
int ans,val,num,numb;
int main()
{
	freopen("value.in","r",stdin);
	freopen("value.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&a[i],&b[i]);
		if(!vis[a[i]]) vis[a[i]]=1,aa[++num]=a[i];
		if(!visb[b[i]]) visb[b[i]]=1,bb[++numb]=b[i];
 	}
 	for(int i=1;i<=num;i++)
 	{
 		for(int j=1;j<=numb;j++)
 		{
 			val=0;
 			if(aa[i]<bb[j]) continue;
 			for(int k=1;k<=n;k++)
 			{
 				if(aa[i]<=a[k]) val+=aa[i];
 				else if(bb[j]<=b[k]) val+=bb[j]; 
			 }
			 ans=max(ans,val);
		 }
	}
	printf("%d",ans);
	return 0;
}
