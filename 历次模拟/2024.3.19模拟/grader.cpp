#include "city.h"
#include <bits/stdc++.h>

using namespace std;

static int MAXQ = 30000;

static int n, m, q = 0, gold;
static vector<int> u, v;
static vector<bool> goal;

static void wrong_answer() {
    printf("Wrong Answer, too much querys.\n");
    exit(0);
}
static void wrong_answer1() {
    printf("Wrong Answer, invalid query format.\n");
    exit(0);
}

static int bin[505]; 
static int find(int x) {
    return bin[x] == x ? x : bin[x] = find(bin[x]); 
}

static bool is_valid(const vector<int>& r, bool type = 0) {
    if (type) gold = 1; 

    if (gold && int(r.size()) != n - 1){
        printf("too much values %d\n",r.size());
        return false;
    }

    for(int i = 0; i < r.size(); i++)
        if (r[i] < 0 || r[i] >= m){
            printf("out of bound r[%d] = %d\n",i,r[i]);
            return false;
        }
    if (gold) {
        for (int i = 0; i < n; ++i) bin[i] = i; 
        for (int i = 0; i < r.size(); ++i) {
            int x = find(u[r[i]]), y = find(v[r[i]]); 
            if (x == y){
                printf("not tree\n");
                return false;
            }
            bin[x] = y; 
        }
    }

    return true;
}

static int _count_common_roads_internal(const vector<int>& r, bool type = 0) {
    if(!is_valid(r, type)){
        wrong_answer1();
    }

    int common = 0;
    for(int i = 0; i < r.size(); i++) {
        bool is_common = goal[r[i]];
        if (is_common)
            common++;
    }

    return common;    
}

int count_common_roads(const vector<int>& r) {
    q++;
    if(q > MAXQ) wrong_answer();

    return _count_common_roads_internal(r);
}

int main(void) {
    freopen("city.in","r",stdin);
    assert(scanf("%d %d %d", &n, &m, &gold) == 3);

    u.resize(m);
    v.resize(m);

    for(int i = 0; i < m; i++)
        assert(scanf("%d %d", &u[i], &v[i]) == 2);

    goal.resize(m, false);

    for(int i = 0; i < n - 1; i++) {
        int id;
        assert(scanf("%d", &id) == 1);
        goal[id] = true;
    }

    vector<int> res = find_roads(n, gold, u, v);

    if(_count_common_roads_internal(res, 1) != n - 1) return printf("Wrong Answer, incorrect answer."); 

    printf("Accepted, use %d queries.\n", q); 

    return 0;
}