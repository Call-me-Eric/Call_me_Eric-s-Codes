#include<bits/stdc++.h>
#include<random>

#define int long long

using namespace std;

mt19937 rd;

const int B=1e9,T0=5,T1=8;
const string Name="match";

int ex_nm[T0]={1,1,1,1,1};
int ex_N[T0]={2,5,2,50,1000};
int ex_M[T0]={3,6,500000,50,1000};
int ex_K[T0]={3,8,500000,50,100000};

int da_nm[T1]={3,3,2,2,2,2,3,3};
int da_N[T1]={2,10,1000,5,50,1000,200,100};
int da_M[T1]={500000,10,5,1000,50,1000,5000,10000};
int da_K[T1]={500000,15,200,1000,70,1500,700000,700000};

inline int random(int x,int y);

int b[1000000],vis[1000000],TOT,len[1000000];

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
					fprintf(file,"%lld %lld\n",n,m);
					vector<vector<int> > hv;
					int qwq=ex_K[I]/n,now=ex_K[I];
					for(int i=1;i<=n;++i)
					{
						int x=random(min(qwq,m)/2,min(qwq,m));
						now-=x;len[i]=x;
					}
					for(int i=1;i<=10;++i)
					{
						int x=random(1,n);
						int y=random(0,min((int)sqrt(now),m-len[x]));
						len[x]+=y;now-=y;
					}
					while(now)
					{
						int x=random(1,n);
						len[x]++;now--;
					}
					TOT=0;int tnow=m-1;
					
					for(int i=1;i<=n;++i)
					{
						vector<int> tmp;
						tnow=min(tnow,m-1-i+1);
						if(random(0,20)==0) tnow-=random(1,4);
						tnow=max(tnow,1ll);
						len[i]=min(len[i],tnow);
						if(len[i]!=0)
							vis[tnow]=1,tmp.push_back(tnow);
						for(int j=2;j<=len[i];++j)
						{
							int x=random(1,tnow);
							while(vis[x])
								x=random(1,tnow);
							vis[x]=1;tmp.push_back(x);
						}
						sort(tmp.begin(),tmp.end());
						for(auto j:tmp)
							vis[j]=0;
						hv.push_back(tmp);
					}
					sort(b+1,b+1+TOT);
					TOT=unique(b+1,b+1+TOT)-b-1;
					for(int i=1;i<=n;++i)
					{
						fprintf(file,"%lld ",len[i]);
						for(auto j:hv[i-1])
							fprintf(file,"%lld ",j);
						fprintf(file,"\n");
					}
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
					int n=da_N[I],m=da_M[I];
					fprintf(file,"%lld %lld\n",n,m);
					vector<vector<int> > hv;
					int qwq=da_K[I]/n,now=da_K[I];
					for(int i=1;i<=n;++i)
					{
						int x=random(min(qwq,m)/2,min(qwq,m));
						now-=x;len[i]=x;
					}
					for(int i=1;i<=10;++i)
					{
						int x=random(1,n);
						int y=random(0,min((int)sqrt(now),m-len[x]));
						len[x]+=y;now-=y;
					}
					while(now)
					{
						int x=random(1,n);
						len[x]++;now--;
					}
					TOT=0;int tnow=m-1;
					
					for(int i=1;i<=n;++i)
					{
						vector<int> tmp;
						tnow=min(tnow,m-1-i+1);
						if(random(0,20)==0) tnow-=random(1,4);
						tnow=max(tnow,1ll);
						len[i]=min(len[i],tnow);
						if(n==1000&&m==5)
						{
							if(random(0,500)==0)
							{
								len[i]=1;int x=random(1,5);
								vis[x]=1;tmp.push_back(x);	
							}
							else len[i]=0;
						}
						else
						{
							if(len[i]!=0)
								vis[tnow]=1,tmp.push_back(tnow);	
						}
						
						for(int j=2;j<=len[i];++j)
						{
							int x=random(1,tnow);
							while(vis[x])
								x=random(1,tnow);
							vis[x]=1;tmp.push_back(x);
						}
						sort(tmp.begin(),tmp.end());
						for(auto j:tmp)
							vis[j]=0;
						hv.push_back(tmp);
					}
					sort(b+1,b+1+TOT);
					TOT=unique(b+1,b+1+TOT)-b-1;
					for(int i=1;i<=n;++i)
					{
						fprintf(file,"%lld ",len[i]);
						for(auto j:hv[i-1])
							fprintf(file,"%lld ",j);
						fprintf(file,"\n");
					}
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
