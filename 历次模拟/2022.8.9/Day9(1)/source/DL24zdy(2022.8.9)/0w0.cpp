#include <bits/stdc++.h>
using namespace std;
#define op(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define cl() fclose(stdin),fclose(stdout)
string s;
int n,m;
inline void init(){
	scanf("%d%d",&n,&m);
	cin>>s;
	char opt;
	for(int i=1;i<=m;i++){
//		scanf("%c",&opt);
		cin>>opt;
		if(opt=='A'){
			int x;
			char y;
//			scanf("%d %c",&x,&y);
			cin>>x>>y;
			s[x-1]=y;
		}else if(opt=='B'){
			int x,y;
			char z;
//			scanf("%d %d %c",&x,&y,&z);
			cin>>x>>y>>z;
			for(int j=x-1;j<y;j++){
				s[j]=z;
			}
		}else{
			int x,y;
//			scanf("%d%d",&x,&y);
			cin>>x>>y;
			int ans=0;
			for(int k=x-1;k<y;k++){
				if(s[k]=='('){
					for(int p=k+1;p<y;p++){
						if(s[p]=='0'){
							for(int q=p+1;q<y;q++){
								if(s[q]=='w'){
									for(int a=q+1;a<y;a++){
										if(s[a]=='0'){
											for(int b=a+1;b<y;b++){
												if(s[b]==')'){
													ans++;
													break;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			printf("%d\n",ans);
		}
	}
}
int main(){
	op("0w0");
	init();
	cl();
	return 0;
}
