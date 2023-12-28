#include<cstdio>
#include<iostream> 
using namespace std;
string s;

int lengthOfLongestSubstring(string s) 
{
    int cnt[300]={0};
    int l=s.length(),st=0,ans=0;
    for (int i=0;i<l;i++)
    {
        if (cnt[s[i]])
        {
            ans = max(ans, i-st);
            while (s[st]!=s[i])
                cnt[s[st++]]=0;
            st++;
        }
        cnt[s[i]]=1;
    }
    ans = max(l-st,ans);
    return ans;
}

int main()
{
//	freopen("../../data/T4 slide/2.in","r",stdin);
//	freopen("../../data/T4 slide/2.out","w",stdout);
	cin>>s;
	printf("%d\n",lengthOfLongestSubstring(s));
	return 0;
}
