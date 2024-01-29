#include<bits/stdc++.h>
using namespace std;
int n, m, i, a[150], num;
int main()
{
    cin >> n >> m;
    i = 0;
    int j;
    while(num < n){ 
	    for(j = 1; j <= n; j++)
	        if(a[j] == 0){
	            i++;
	            if(i%m==0) {
		            cout<<j<<" ";
		            a[j] = 1;
		            num++;    
	            } 
        	} 
    } 
    return 0;
}
