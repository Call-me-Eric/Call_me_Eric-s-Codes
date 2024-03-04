//triangle
#include<bits/stdc++.h>
using namespace std;

int n,k;
int a[109][109];
priority_queue<int,vector<int>,greater<int> > hp[109][109];
priority_queue<int,vector<int>,greater<int> > ans;

inline int read()
{
	int x = 0;
	int f = 1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		x = (x*10)+(c-'0');
		c = getchar();
	}
	return x*f;
}
int main()
{
	
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	
	n = read();
	k = read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			a[i][j] = read();
		}
	}
	
	/*
	for(int i=1;i<=n;i++)
	{
		hp[n][i].push(a[n][i]);
	}
	*/
	
	hp[1][1].push(a[1][1]);//init
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			//
			priority_queue<int,vector<int>,greater<int> > jug;//实现非严格 
			
			
			
			while(!hp[i-1][j].empty())
			{
				hp[i][j].push(hp[i-1][j].top()+a[i][j]);
				jug.push(hp[i-1][j].top());
				hp[i-1][j].pop();
		    }
		    
		    while(!jug.empty()) hp[i-1][j].push(jug.top()),jug.pop();
		    
		    while(!hp[i-1][j-1].empty())
		    {
		    	hp[i][j].push(hp[i-1][j-1].top()+a[i][j]);
		    	jug.push(hp[i-1][j-1].top());
		    	hp[i-1][j-1].pop();
			}
			
			while(!jug.empty()) hp[i-1][j-1].push(jug.top()),jug.pop();
			
			while(hp[i][j].size()>k) hp[i][j].pop();
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		while(!hp[n][i].empty())
		{
			ans.push(hp[n][i].top());
			hp[n][i].pop();
		}
	}
	
	while(ans.size()>k) ans.pop();
	cout<<ans.top();
	return 0;
}
