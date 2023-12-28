#include<cstdio>
#include<cstring>
using namespace std;
char s[1000010];
int cnt[300],l=1,r=1,sum,q,L;

int main()
{
	freopen("abcd.in","r",stdin);
	freopen("abcd.out","w",stdout);
	scanf("%s",s+1);
	L=strlen(s+1);
	for (r=1;r<=26;r++)
	{
		if (s[r]=='?') q++;
		else
		{
			cnt[s[r]]++;
			if (cnt[s[r]]==1) sum++;
		}
	}
	while (r<=L)
	{
		if (sum+q==26) break;
		if (s[r]=='?') q++;
		else
		{
			cnt[s[r]]++;
			if (cnt[s[r]]==1) sum++;
		}
		if (s[l]=='?') q--;
		else
		{
			cnt[s[l]]--;
			if (!cnt[s[l]]) sum--;
		}
		l++;r++;
	}
	r--;
	if (r<=L)
	{
		for (int i=l;i<=r;i++)
		{
			if (s[i]=='?')
				for (int j='A';j<='Z';j++)
					if (!cnt[j])
					{
						s[i]=j;
						cnt[j]=1;
						break;
					}
			printf("%c",s[i]);
		}
	}
	else printf("-1");
	return 0;
}

