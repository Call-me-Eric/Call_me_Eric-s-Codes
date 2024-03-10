#include<bits/stdc++.h>
using namespace std;
string s;
long long m,n,x,y,mod=4294967296;
char a=' ',b=' ';
int main(){
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	cin>>n>>m;
	b=getchar();
	getline(cin,s);
    for(int zyc=1;zyc<=m;zyc++){
    	cin>>a;
    	if(a=='A'){
    		scanf("%lld",&x);
    		cin>>b;
    		s[x-1]=b;
		}
		else if(a=='B'){
		    scanf("%lld%lld",&x,&y);
		    cin>>b;
            for(int i=x;i<=y;i++)s[i-1]=b;
		}
		else if(a=='C'){
			scanf("%lld%lld",&x,&y);
			if(y-x<4){
				cout<<0<<endl;
				continue;
			}
			int tt=0;
			for(int q=x;q<=y-4;q++){
				if(s[q-1]=='('){
					for(int i=q+1;i<=y-3;i++){
				    if(s[i-1]=='0'){
					for(int j=i+1;j<=y-2;j++){
						if(s[j-1]=='w'){
							for(int k=j+1;k<=y-1;k++){
								if(s[k-1]=='0'){
									for(int r=k+1;r<=y;r++)
								    if(s[r-1]==')')tt++;
								}

							}
							tt%=mod;
						}
				}
				tt%=mod;
				}
			    }
			    tt%=mod;
				}
			}	
			cout<<tt%mod<<endl;
		}
    }
	return 0;
}
