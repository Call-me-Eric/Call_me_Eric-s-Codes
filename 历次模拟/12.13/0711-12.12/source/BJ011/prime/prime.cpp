#include <bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
string tostr(int x)
{
	string rtn;
	while(x) rtn+=(char)(x%10+'0'),x/=10;
	reverse(rtn.begin(),rtn.end());
	return rtn;
}
bool check(int X,int Y)
{
	string x=tostr(X),y=tostr(Y);
	int nw=0;
	for(auto t:x)
	{
		if(t==y[nw]) ++nw;
		if(nw==y.size()) return 1;
	}
	return 0;
}
bool P(int x)
{
	if(x<=1) return 0;
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return 0;
	return 1;
}
vector<int> S={2,3,5,7,89,409,449,499,6469,6949,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
vector<string> SS;
namespace cal1
{
	int dp[100005][25][2];
	int ck[24][10];
	//00,1,8,9
	void init()
	{
		int nw=0;
		for(int j=0;j<=9;j++)
		{
			nw=0;
			for(int c0=0;c0<=2;c0++)
			{
				for(int c1=0;c1<=1;c1++)
				{
					for(int c8=0;c8<=1;c8++)
					{
						for(int c9=0;c9<=1;c9++)
						{
							if(j==2||j==3||j==5||j==7||c1&&(j&1))
							{
								ck[nw++][j]=25;
								continue;
							}
							if(c1)
							{
								ck[nw++][j]=4;
								continue;
							}
							if(c8&&j==8||c9&&j==9||c8&&j==9||c9&&c0==2&&j==2)
							{
								ck[nw++][j]=25;
								continue;
							}
							if(j!=0&&j!=8&&j!=1&&j!=9)
							{
								ck[nw++][j]=25;
								continue;
							}
							if(j==0&&c0)
							{
								ck[nw++][j]=25;
								continue;
							}
							int w=0;
							if(j==9) w=1;
							if(j==8) w=2;
							if(j==1) w=4;
							if(j==0) w=8*c9;
							if(j!=1)ck[nw][j]=nw+w;
							else ck[nw][j]=4;
							nw++;
						}
					}
				}
			}
		}
	}
	int solve(string a)
	{
		int n=a.size();
		a=' '+a;
		memset(dp,0,sizeof dp);
		dp[0][0][1]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=23;j++)
			{
				for(int k=0;k<=1;k++)
				{
					if(!dp[i-1][j][k]) continue;
					for(int l=0;l<=9;l++)
					{
						if(ck[j][l]>=24) continue;
						if(k&&l>a[i]-'0') continue;
						if(k&&l==a[i]-'0')
						{
							dp[i][ck[j][l]][1]=(dp[i][ck[j][l]][1]+dp[i-1][j][k])%mod;
							continue;
						}
						dp[i][ck[j][l]][0]=(dp[i][ck[j][l]][0]+dp[i-1][j][k])%mod;
					}
				}
			}
		}
		int s=0;
		for(int i=4;i<=4;i++)
			for(int j=0;j<=1;j++) s+=dp[n][i][j];
		return (s%mod+mod)%mod;
	}
}
namespace cal9
{
	int dp[25][200005][2];
	int tot;
	vector<pair<int,int> > e[200005];
	vector<int> p[200005];
	int cntp;
	map<vector<int>,int> mp;
	void dfs(vector<int> s)
	{
		if(mp.count(s)) return ;
		mp[s]=++cntp;
		for(int i=0;i<=9;i++)
		{
			if(i!=0&&i!=4&&i!=6&&i!=9&&i!=8) continue;
			vector<int> nx;
			int flag=1;
			for(int j=0;j<SS.size();j++)
			{
				if(i==SS[j][s[j]]-'0')
				{
					if(s[j]+1==(SS[j].size()))
					{
						flag=0;
						break;
					}
					nx.push_back(s[j]+1);
				}
				else nx.push_back(s[j]);
			}
			if(flag) dfs(nx),e[mp[s]].push_back({mp[nx],i});
		}
	}
	void init()
	{
		cntp=tot=0;
		vector<int> s;
		for(int i=0;i<SS.size();i++) s.push_back(0);
		dfs(s);
	}
	int solve(string a)
	{
		int n=a.size();
		a=' '+a;
		tot=cntp;
		memset(dp,0,sizeof dp);
		dp[0][1][1]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=tot;j++)
			{
				for(int k=0;k<=1;k++)
				{
					if(!dp[i-1][j][k]) continue;
					for(auto v:e[j])
					{
						int l=v.second,C=v.first;
						if(k&&l>a[i]-'0') continue;
						if(k&&l==a[i]-'0')
						{
							dp[i][C][1]=(dp[i][C][1]+dp[i-1][j][k])%mod;
							continue;
						}
						dp[i][C][0]=(dp[i][C][0]+dp[i-1][j][k])%mod;
					}
				}
			}
		}
		int s=-1;
		for(int i=1;i<=tot;i++)
			s+=dp[n][i][0]+dp[n][i][1];
		return (s%mod+mod)%mod;
	}
}
signed main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdin); 
	for(int i=4;i<S.size();i++) SS.push_back(tostr(S[i]));
	cal1::init();
	cal9::init();
	ios::sync_with_stdio(false);
	cin.tie(0);
	int ans=0;
	int T;
	cin >> T;
	while(T--)
	{
		string l,r;
		cin >> l >> r;
		--l.back();
		for(int i=l.size()-1;i>0;i--)
			if(l[i]<'0') l[i]+=10,l[i-1]--;
		int ans=cal9::solve(r)-cal9::solve(l)+cal1::solve(r)-cal1::solve(l);
		ans=(ans%mod+mod)%mod;
		cout << ans << "\n";
	}
/*	int n;
	cin >> n;
	string s=tostr(n);
	/*for(int i=1;i<=n;i++)
	{
		int flag=1;
		for(auto t:S) if(check(i,t))
		{
			flag=0;
			break;
		}
		string t=tostr(i);
		for(auto x:t) if(x=='1')
		{
			flag=0;
			break;
		}
		//cout << i << " " << flag << "\n";
		ans+=flag;
	}*/
	/*ans=cal9::solve(s);
	cout << ans << "\n";
	ans+=cal1::solve(s);
	cout << ans << " " << cal1::solve(s);*/
	return 0;
}
