#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <sys/time.h>

int n,m,i,tp,x,y;

char sp[5] = "(0w)";

char gench()
{
    if (rand()%10 < 8) return sp[rand()%4];
    else return 33+rand()%94;
}

int RAND()
{
    return (rand()<<15)+rand();
}

int main()
{
	timeval tv;
	gettimeofday(&tv,NULL);
	srand((tv.tv_sec * 1000000LL + tv.tv_usec));
	freopen("(0w0)1.in", "w", stdout);

    n = rand()%200+3;
    m = rand()%200+1;
    
    n = 40;
    m = 35; 
    
    printf("%d %d\n", n, m);
    for (i=1; i<=n; ++i) printf("%c", gench());
    printf("\n");
    while (m--)
    {
        x = RAND()%n+1;
        y = RAND()%n+1;
        if (x > y) x ^= y ^= x ^= y;
        tp = 'A'+rand()%3;
        
        
        printf("%c ", tp);
        if (tp == 'A') printf("%d %c\n", x, gench());
        else
        if (tp == 'B')
        {
            while (y-x > sqrt(n))
            {
                x = RAND()%n+1;
                y = RAND()%n+1;
                if (x > y) x ^= y ^= x ^= y;
            }
            printf("%d %d %c\n", x, y, gench());
        } 
        else
        {
            while (y-x < 20)
            {
                x = RAND()%n+1;
                y = RAND()%n+1;
                if (x > y) x ^= y ^= x ^= y;
            }
            printf("%d %d\n", x, y);
        }
    }
	return 0;
}


