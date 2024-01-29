#include<bits/stdc++.h>
using namespace std;
stack<int> s;
int n;
int a[30020];
int main() {
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        if(s.empty() || s.top() > a[i]){
            s.push(a[i]);
        }
        else{
            while(!s.empty() && s.top() < a[i]){
                
            }
        }
    }

    return 0;
}