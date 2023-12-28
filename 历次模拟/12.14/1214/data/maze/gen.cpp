#include<bits/stdc++.h>
#include<random>

#define int long long

using namespace std;

mt19937 rd;

const int B=1e9,T0=4,T1=5;
const string Name="maze";

int ex_nm[T0]={1,1,1,1};
int ex_N[T0]={5,7,1000,100000};
int ex_M[T0]={8,15,2000,200000};
int ex_SP[T0]={0,0,0,1};

int da_nm[T1]={6,4,3,3,4};
int da_N[T1]={15,2000,200000,200000,200000};
int da_SP[T1]={0,0,1,2,0};

inline int random(int x,int y);

struct node
{
	int u,v,w;
};
int du[1000005];

signed main()
{
	puts("Choose to gen what 0:example/1:data");
	int opt;
	cin>>opt;
	puts("Choose to run old or make new 0:run/1:make");
	int opt2;
	cin>>opt2;
	if(opt2==1)
	{
		puts("read seed or rand seed 0:rand/1:read");
		int opt1;
		cin>>opt1;
		if(opt1==0)
		{
			int seed=time(0);
			rd=mt19937(seed);
			printf("the seed is:%d\n",seed);
		}
		else
		{
			printf("please input the seed:");
			int seed;cin>>seed;
			rd=mt19937(seed);
		}
	}
	if(opt==0)
	{
		int tot=1;
		for(int I=0;I<T0;++I)
			for(int J=0;J<ex_nm[I];++J)
			{
				FILE *file;
				string path="ex_"+Name+to_string(tot)+".in"; 
				
				if(opt2==1)
				{
					file=fopen(path.data(),"w");
					int n=ex_N[I],m=ex_M[I];
					vector<int> st;
					for(int i=2;i<=n;++i)
						if(random(0,(int)sqrt(n)))
							st.push_back(i);
					fprintf(file,"%lld %lld %lld\n",n,m,(int)st.size());
					for(int i=0;i<(int)st.size();++i)
						fprintf(file,"%lld%c",st[i],(i==(int)st.size()-1?'\n':' '));
					vector<node> ed;
					map<pair<int,int>,int> vis;
					for(int i=1;i<=n;++i)
						du[i]=0;
					for(int i=1;i<n;++i)
					{
						int u=random(1,i),v=i+1,w=random(1,n);
						ed.push_back((node){u,v,w});
						du[u]++;du[v]++;
						vis[make_pair(u,v)]=1;
						vis[make_pair(v,u)]=1;
					}
					for(int i=n;i<=m;++i)
					{
						int u=random(1,n),v=random(1,n),w=random(1,n);
						while(u==v||vis.count(make_pair(u,v)))
						{
							u=random(1,n);
							v=random(1,n);
						}
						ed.push_back((node){u,v,w});
						du[u]++;du[v]++;
						vis[make_pair(u,v)]=1;
						vis[make_pair(v,u)]=1;
					}
					for(int i=1;i<=n;++i)
						fprintf(file,"%lld%c",random(0,du[i]/2),(i==n?'\n':' '));
					for(int i=1;i<=m;++i)
						fprintf(file,"%lld %lld %lld\n",ed[i-1].u,ed[i-1].v,ed[i-1].w);
					fclose(file);
				}
				
				string Opera="std.exe < "+path+" > "+"ex_"+Name+to_string(tot)+".ans";
				system(Opera.data());
				printf("ok to gen example %lld\n",tot);
				++tot;
			}
	}
	else
	{
		int tot=1;
		for(int I=0;I<T1;++I)
			for(int J=0;J<da_nm[I];++J)
			{
				FILE *file;
				string path=Name+to_string(tot)+".in"; 
				
				if(opt2==1)
				{
					file=fopen(path.data(),"w");
					int n=da_N[I]/2,m=da_N[I];
					vector<int> st;
					for(int i=2;i<=n;++i)
						if(random(0,(int)pow(n,0.2)))
							st.push_back(i);
					fprintf(file,"%lld %lld %lld\n",n,m,(int)st.size());
					for(int i=0;i<(int)st.size();++i)
						fprintf(file,"%lld%c",st[i],(i==(int)st.size()-1?'\n':' '));
					vector<node> ed;
					map<pair<int,int>,int> vis;
					for(int i=1;i<=n;++i)
						du[i]=0;
					for(int i=1;i<n;++i)
					{
						int u=random(1,i),v=i+1,w=random(1,n);
						ed.push_back((node){u,v,w});
						du[u]++;du[v]++;
						vis[make_pair(u,v)]=1;
						vis[make_pair(v,u)]=1;
					}
					for(int i=n;i<=m;++i)
					{
						int u=random(1,n),v=random(1,n),w=random(1,n);
						while(u==v||vis.count(make_pair(u,v)))
						{
							u=random(1,n);
							v=random(1,n);
						}
						ed.push_back((node){u,v,w});
						du[u]++;du[v]++;
						vis[make_pair(u,v)]=1;
						vis[make_pair(v,u)]=1;
					}
					for(int i=1;i<=n;++i)
					{
						int x=random(0,du[i]/2);
						if(da_SP[I]==1) x=0;
						else x=random(0,min(du[i],1ll));
						fprintf(file,"%lld%c",x,(i==n?'\n':' '));
					}
					for(int i=1;i<=m;++i)
						fprintf(file,"%lld %lld %lld\n",ed[i-1].u,ed[i-1].v,ed[i-1].w);
					fclose(file);
				}
				
				string Opera="std.exe < "+path+" > "+Name+to_string(tot)+".out";
				system(Opera.data());
				printf("ok to gen data %lld\n",tot);
				++tot;
			}
	}
	return 0;
}

inline int random(int x,int y)
{
	return (rd()%B*B+rd()%B)%(y-x+1)+x;
}
