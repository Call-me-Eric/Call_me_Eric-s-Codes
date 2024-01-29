#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
const int N = 1e5 * 2 + 10;
char c[N];
char tmp[N];
int p[N];
int clen, m;
int main(){
    scanf("%s",tmp);
    clen = strlen(tmp);
    int i = 0;
    while(i < clen){
        c[i * 2] = '#';
        c[i * 2 + 1] = tmp[i];
        i++;
    }
    c[i * 2] = '#';
    m = i * 2 + 1;
    c[m] = '\0';
    int maxid = -1;
    int id = -1;
    for(int i = 0;i < m;i++){
        p[i] = 1;
        if(maxid > i){
            p[i] = min(p[id * 2 - i],maxid - i);
        }
        while (c[i - p[i]] == c[i + p[i]] && i - p[i] >= 0 && i + p[i] < m){
            p[i] ++;
        }
        if(i + p[i] > maxid){
            id = i;
            maxid = p[i] + i;
        }
    }
    int maxx = -99;
    for(int i = 0;i < m;i++){
        if(maxx < (p[i] - 1)){
            maxx = p[i] - 1;
        }
    }
    printf("%d\n",maxx);
    return 0;
}