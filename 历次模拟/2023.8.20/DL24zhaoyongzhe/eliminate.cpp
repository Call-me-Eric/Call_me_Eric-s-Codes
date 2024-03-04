#include<bits/stdc++.h>
#define max(a,b) (a) > (b) ? (a) : (b)
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
int now[4][4], lst[4][4];
char opt;int x;
signed main(){
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	memset(now,-0x3f,sizeof(now)); now[0][0] = 0;
	while((opt = getchar())!= EOF){
		x = 0;
		if(opt == 'R')x = 1;
		if(opt == 'G')x = 2;
		if(opt == 'B')x = 3;
		if(!x)continue;
		lst[0][0] = now[0][0];lst[0][1] = now[0][1];lst[0][2] = now[0][2];lst[0][3] = now[0][3];
		lst[1][0] = now[1][0];lst[1][1] = now[1][1];lst[1][2] = now[1][2];lst[1][3] = now[1][3];
		lst[2][0] = now[2][0];lst[2][1] = now[2][1];lst[2][2] = now[2][2];lst[2][3] = now[2][3];
		lst[3][0] = now[3][0];lst[3][1] = now[3][1];lst[3][2] = now[3][2];lst[3][3] = now[3][3];
		now[x][0] = max(lst[0][0], now[x][0]);//case 1
		
		now[1][x] = max(lst[1][0], now[1][x]);//case 2
		now[2][x] = max(lst[2][0], now[2][x]);
		now[3][x] = max(lst[3][0], now[3][x]);
		
		now[1][0] = max(now[1][0],lst[x][x] + 1);//case 3
		now[2][0] = max(now[2][0],lst[x][x] + 1);
		now[3][0] = max(now[3][0],lst[x][x] + 1);
		
		if(x == 1){
			//case 4
			now[1][1] = max(now[1][1],max(lst[3][2],lst[2][3]));
			now[1][2] = max(now[1][2],max(lst[3][2],lst[2][3]));
			now[1][3] = max(now[1][3],max(lst[3][2],lst[2][3]));
			
			now[2][1] = max(now[2][1],max(lst[3][2],lst[2][3]));
			now[2][2] = max(now[2][2],max(lst[3][2],lst[2][3]));
			now[2][3] = max(now[2][3],max(lst[3][2],lst[2][3]));
			
			now[3][1] = max(now[3][1],max(lst[3][2],lst[2][3]));
			now[3][2] = max(now[3][2],max(lst[3][2],lst[2][3]));
			now[3][3] = max(now[3][3],max(lst[3][2],lst[2][3]));
			
		}else if(x == 2){
			now[1][1] = max(now[1][1],max(lst[3][1],lst[1][3]));
			now[1][2] = max(now[1][2],max(lst[3][1],lst[1][3]));
			now[1][3] = max(now[1][3],max(lst[3][1],lst[1][3]));
			
			now[2][1] = max(now[2][1],max(lst[3][1],lst[1][3]));
			now[2][2] = max(now[2][2],max(lst[3][1],lst[1][3]));
			now[2][3] = max(now[2][3],max(lst[3][1],lst[1][3]));
			
			now[3][1] = max(now[3][1],max(lst[3][1],lst[1][3]));
			now[3][2] = max(now[3][2],max(lst[3][1],lst[1][3]));
			now[3][3] = max(now[3][3],max(lst[3][1],lst[1][3]));
		}else{
			now[1][1] = max(now[1][1],max(lst[1][2],lst[2][1]));
			now[1][2] = max(now[1][2],max(lst[1][2],lst[2][1]));
			now[1][3] = max(now[1][3],max(lst[1][2],lst[2][1]));
			
			now[2][1] = max(now[2][1],max(lst[1][2],lst[2][1]));
			now[2][2] = max(now[2][2],max(lst[1][2],lst[2][1]));
			now[2][3] = max(now[2][3],max(lst[1][2],lst[2][1]));
			
			now[3][1] = max(now[3][1],max(lst[1][2],lst[2][1]));
			now[3][2] = max(now[3][2],max(lst[1][2],lst[2][1]));
			now[3][3] = max(now[3][3],max(lst[1][2],lst[2][1]));
		}
		//case 5
		if(x != 1)now[1][x] = max(now[1][x],lst[x][1]);
		if(x != 2)now[2][x] = max(now[2][x],lst[x][2]);
		if(x != 3)now[3][x] = max(now[3][x],lst[x][3]);
	}
	int ans = -1;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			ans = max(ans,now[i][j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}

