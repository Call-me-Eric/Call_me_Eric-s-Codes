#include<bits/stdc++.h>
using namespace std;
int r,g,b,n,m,si[305];
struct dsu
{
	int n,fa[305];
	void init(int x){n=x;for(int i=1;i<=n;i++) fa[i]=i;}
	int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
};
struct jgt{int fr,to,col;}e[90005];
vector<jgt>er[305],eg[305],eb[305],rr,gg;
int mr[305],mg[305],mx[305];
int getnum(vector<jgt>e)
{
	dsu D;D.init(n);int ans=0;
	for(int i=0;i<e.size();i++)
	{
		int xx=D.find(e[i].fr);
		int yy=D.find(e[i].to);
		if(xx==yy) continue;
		D.fa[xx]=yy;ans++;
	}
	return ans;
}
int c[90005];
void solve(vector<jgt>r,vector<jgt>g,vector<jgt>b,int rnum,int gnum,int si)
{
	//cout<<rnum<<" "<<gnum<<" "<<si<<endl;
	dsu D;D.init(n);
	for(int i=0;i<r.size();i++)
	{
		int xx=D.find(r[i].fr);
		int yy=D.find(r[i].to);
		if(xx==yy) continue;
		D.fa[xx]=yy;
	}
	vector<pair<int,int> >vec;
	for(int i=0;i<g.size();i++)
	{
		int xx=D.find(g[i].fr);
		int yy=D.find(g[i].to);
		if(xx==yy) continue;
		D.fa[xx]=yy;c[g[i].col]=1;gnum--;
		vec.push_back(make_pair(g[i].fr,g[i].to));
	}
	D.init(n);
	for(int i=0;i<vec.size();i++)
	{
		int xx=D.find(vec[i].first);
		int yy=D.find(vec[i].second);
		if(xx==yy) continue;
		D.fa[xx]=yy;
	}
	for(int i=0;i<g.size()&&gnum;i++)
	if(!c[g[i].col])
	{
		int xx=D.find(g[i].fr);
		int yy=D.find(g[i].to);
		if(xx==yy) continue;
		D.fa[xx]=yy;c[g[i].col]=1;gnum--;
	}
	for(int i=0;i<r.size()&&rnum;i++)
	{
		int xx=D.find(r[i].fr);
		int yy=D.find(r[i].to);
		if(xx==yy) continue;
		D.fa[xx]=yy;c[r[i].col]=1;rnum--;
	}
	for(int i=0;i<b.size();i++)
	{
		int xx=D.find(b[i].fr);
		int yy=D.find(b[i].to);
		if(xx==yy) continue;
		D.fa[xx]=yy;c[b[i].col]++;
	}
}
int main()
{
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	cin>>r>>g>>b>>m;
	char s[5];n=r+g+b+1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%s",&e[i].fr,&e[i].to,s+1);
		if(s[1]=='r') e[i].col=1;
		else if(s[1]=='g') e[i].col=2;
		else e[i].col=3;
	}
	dsu E;E.init(n);
	for(int i=1;i<=n;i++) si[i]=1;
	for(int i=1;i<=m;i++) if(e[i].col==3)
	{
		int xx=E.find(e[i].fr);
		int yy=E.find(e[i].to);
		if(xx==yy) continue;
		E.fa[xx]=yy;si[yy]+=si[xx];
	}
	for(int i=1;i<=m;i++)
	{
		int xx=E.find(e[i].fr);
		int yy=E.find(e[i].to);
		if(xx==yy)
		{
			if(e[i].col==1) er[xx].push_back((jgt){e[i].fr,e[i].to,i});
			else if(e[i].col==2) eg[xx].push_back((jgt){e[i].fr,e[i].to,i});
			else eb[xx].push_back((jgt){e[i].fr,e[i].to,i});
			e[i].col=3;
		}
		else
		{
			if(e[i].col==1) rr.push_back((jgt){e[i].fr,e[i].to,i});
			else gg.push_back((jgt){e[i].fr,e[i].to,i});
		}
	}
	vector<int>poi;poi.push_back(0);
	for(int i=1;i<=n;i++) if(E.fa[i]==i) poi.push_back(i);
	int num=poi.size()-1;
	for(int i=1;i<=num;i++)
	{
		mx[i]=si[poi[i]]-1;
		mr[i]=getnum(er[poi[i]]);
		mg[i]=getnum(eg[poi[i]]);
		//cout<<mr[i]<<" "<<mg[i]<<" "<<mx[i]<<endl;
		mr[i]+=mr[i-1],mg[i]+=mg[i-1],mx[i]+=mx[i-1];
	}
	int mmr=num-getnum(gg)-1,mmg=num-getnum(rr)-1,mmx=num-1;
	//cout<<mmr<<" "<<mmg<<" "<<mmx<<endl;
	for(int i=mmr;i<=rr.size();i++)
	{
		if(mmx-i<mmg||mmx-i>gg.size()) continue;
		int x=r-i,y=g-(mmx-i);//cout<<x<<" "<<y<<endl;
		if(x<0||y<0||x>mr[num]||y>mg[num]||x+y>mx[num]) continue;
		puts("YES");vector<jgt>tmp;
		solve(rr,gg,tmp,i,mmx-i,num);
		for(int j=num;j>=1;j--)
		{
			for(int tt1=mr[j]-mr[j-1];tt1>=0;tt1--)
			{
				int t1=tt1,t2=min(mg[j]-mg[j-1],mx[j]-t1);
				int tx=x-t1,ty=y-t2;
				if(tx<0) t1+=tx,tx=0;
				if(ty<0) t2+=ty,ty=0;
				if(tx>mr[j-1]||ty>mg[j-1]||tx+ty>mx[j-1]) continue;
				solve(er[poi[j]],eg[poi[j]],eb[poi[j]],t1,t2,si[poi[j]]);
				x=tx;y=ty;
				break;
			}
		}
		for(int j=1;j<=m;j++) putchar('0'+c[j]);
		exit(0);
	}
	puts("NO");
	return 0;
}
