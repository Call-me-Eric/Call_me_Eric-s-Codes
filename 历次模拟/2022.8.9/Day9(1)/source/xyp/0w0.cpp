#include<bits/stdc++.h>
using namespace std;
#define int long long
#define debug cout<<"!!! ";
const int mod=4294967296;
int n,m,x,y,z,a[1000010];
char op;
string s;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int ans;
int search(int x,int y)
{
	int flag[5];ans=0;
	for(int i=x+2; i<=y-2; i++) if(a[i]==119)
		{
			int res1=0,res2=0;
			flag[1]=0;
			for(int j=1; j<i-1; j++) //���(0����
			{
				if(a[j]==40) flag[1]=1;
				else flag[1]=0;
				flag[2]=0;//cout<<flag[1]<<":";
				if(flag[1]==1) for(int k=j+1; k<i; k++) if(a[k]==48) flag[2]++;
				res1=(res1+flag[1]%mod*flag[2])%mod;
			}
			flag[3]=0;
			for(int j=i+1; j<y; j++) //�Ҳ�0)����
			{
				if(a[j]==48) flag[3]=1;
				else flag[3]=0;
				flag[4]=0;//cout<<a[j]<<":";
				if(flag[3]==1) for(int k=j+1; k<=y; k++) if(a[k]==41) flag[4]++;
				res2=(res2+flag[3]%mod*flag[4])%mod;
			}
			ans=(ans+res1*res2)%mod;
			//cout<<ans<<" ";
		}
	return ans;
}
signed main()
{
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	//0->48
	//(->40
	//)->41
	//w->119
	//(0w0)->40 48 119 48 41
	scanf("%lld%lld",&n,&m);
	cin>>s;
	for(int i=0; i<n; i++) a[i+1]=s[i];
	while(m--)
	{
		cin>>op;
		if(op=='A')
		{
			x=read();
			cin>>op;//string
			a[x]=op;//�����޸�
		}
		if(op=='B')
		{
			x=read(),y=read();
			cin>>op;//�����޸�
			for(int i=x; i<=y; i++) a[i]=op;
		}
		if(op=='C')
		{
			x=read(),y=read();//�����ѯ
			printf("%lld\n",search(x,y));
		}
	}
	return 0;
}
//����ͼ�ҳ���Դ��
//��һ�����е����������ж��ٸ�����a
//�����ж��ٸ���Է���·���ϱ�Ȩ�ʹ��ڵ�Ȩ��
/*
7 4
(0w0#))
C 1 6
B 5 6 w
A 6 0
C 1 7
*/
