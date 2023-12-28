#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define ll long long
using namespace std;

typedef unsigned long long ull;
const int N = 400000;
char cc[1005];int dy[1005],pc[1 << 16];
struct div16{
	unsigned short a[16];
	void init(){
		for(int i = 0;i < 16;i++){
			a[i] = 0;
		}
	}
}s[400005];
int tot = 0, ind[16][1 << 16], mw[16][1 << 16], nxt[10000005], zhi[10000005];
void addedge(int u1,int u2,int v){
	if(!ind[u1][u2])ind[u1][u2] = ++tot;
	else nxt[mw[u1][u2]] = ++ tot;
	mw[u1][u2] = tot;
	zhi[tot] = v;
}
ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, ull a1, ull a2) {
	for(int i = 1;i <= n;i++)
		for(int j = 0;j < 16;j++)
			for(int k = 0;k < 16;k++)
				s[i].a[j] |= (1 << 15 - k) * ( (myRand(a1, a2) & (1ull << 32)) ? 1 : 0);
	for(int i = 1;i <= n;i++)
		for(int j = 0;j < 16;j++)
			addedge(j, s[i].a[j], i);
}
inline ull read(){
	ull x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x;
}
/*
bool tmp[300];
bool to[512][4];
ll n, q, a1, a2;
bool lastans = 0;
bool is16(char ch){
	return ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F'));
}
void unlock(){
	ll cnt = 0;
	char ch = getchar();
	while(!is16(ch))ch = getchar();
	while(is16(ch) && cnt < 256){
		for(int i = 0;i < 4;i++){
			tmp[cnt + i] = (to[(int)ch][i] ^ lastans);
		}
		cnt += 4;
		ch = getchar();
	}
	return;
}
bool solve(){
	unlock();
	ll k = read();
	for(int i = 1;i <= n;i++){
		ll diff = 0;
		for(int j = 0;j < 256;j++){
			if(tmp[j] != s[i][j])diff++;
		}
		if(diff <= k)return 1;
	}
	return 0;
}
void work(){
	to['0'][0] = 0; to['0'][1] = 0; to['0'][2] = 0; to['0'][3] = 0;
	to['1'][0] = 0; to['1'][1] = 0; to['1'][2] = 0; to['1'][3] = 1;
	to['2'][0] = 0; to['2'][1] = 0; to['2'][2] = 1; to['2'][3] = 0;
	to['3'][0] = 0; to['3'][1] = 0; to['3'][2] = 1; to['3'][3] = 1;
	to['4'][0] = 0; to['4'][1] = 1; to['4'][2] = 0; to['4'][3] = 0;
	to['5'][0] = 0; to['5'][1] = 1; to['5'][2] = 0; to['5'][3] = 1;
	to['6'][0] = 0; to['6'][1] = 1; to['6'][2] = 1; to['6'][3] = 0;
	to['7'][0] = 0; to['7'][1] = 1; to['7'][2] = 1; to['7'][3] = 1;
	to['8'][0] = 1; to['8'][1] = 0; to['8'][2] = 0; to['8'][3] = 0;
	to['9'][0] = 1; to['9'][1] = 0; to['9'][2] = 0; to['9'][3] = 1;
	to['A'][0] = 1; to['A'][1] = 0; to['A'][2] = 1; to['A'][3] = 0;
	to['B'][0] = 1; to['B'][1] = 0; to['B'][2] = 1; to['B'][3] = 1;
	to['C'][0] = 1; to['C'][1] = 1; to['C'][2] = 0; to['C'][3] = 0;
	to['D'][0] = 1; to['D'][1] = 1; to['D'][2] = 0; to['D'][3] = 1;
	to['E'][0] = 1; to['E'][1] = 1; to['E'][2] = 1; to['E'][3] = 0;
	to['F'][0] = 1; to['F'][1] = 1; to['F'][2] = 1; to['F'][3] = 1;
	for(int i = 1;i <= q;i++){
		lastans = solve();
		puts(lastans ? "1" : "0");
	}
}*/
signed main(){
//	work();
	for(int i = 1;i < (1 << 16);i++){
		pc[i] = pc[i ^ (i & (-i))] + 1;
	}
	for(int i = 0;i < 10;i++){
		dy['0' + i] = i;
	}
	for(int i = 'A';i <= 'F';i++){
		dy[i] = i - 'A' + 10;
	}
	int n, m;
	ull a1,a2;
	unsigned short zz = 0,lastans = 0;
	scanf("%d%d%llu%llu",&n,&m,&a1,&a2);
	gen(n,a1,a2);
	while(m--){
		div16 f;
		f.init();
		int kk = 0, tt = 0, flag = 0;
		scanf("%s%d",cc + 1,&kk);
		for(int i = 0;i < 16;i++){
			for(int j = 0;j < 4;j++){
				f.a[i] |= (1 << (3 - j << 2)) * dy[cc[++tt]];
			}
		}
		for(int i = 0;i < 16;i++){
			f.a[i] ^= zz - lastans;
		}
		for(int i = 0;i < 16;i++){
			unsigned short dd = f.a[i];
			for(int j = ind[i][dd];j;j = nxt[j]){
				int cu = zhi[j],he = 0,ff = 1;
				for(int k = 0;k < 16;k++){
					he += pc[(s[cu].a[k]) ^ (f.a[k])];
					if(he > kk){
						ff = 0;
						break;
					}
				}
				if(ff){
					flag = 1;
					break;
				}
			}
			if(flag)break;
		}
		lastans = flag;
		putchar('0' + flag);
		putchar('\n');
	}
	return 0;
}

