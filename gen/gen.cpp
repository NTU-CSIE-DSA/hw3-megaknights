#include <bits/stdc++.h>
#include "testlib.h"
#define kN 100005
#define maxn 100000
#define smalln 1000
#define maxhp 1000000000
//#define int long long
#define rep(i,n) for(int i=0; i<(n); ++i)
#define fup(i,a,b) for(int i=(a); i<(b); ++i)
#define fdn(i,a,b) for(int i=(a); i>(b); --i)
using namespace std;

int n, m, p[kN];
int Find(int x){return x==p[x]?x:p[x]=Find(p[x]);}
void Union(int x, int y){p[Find(x)]=Find(y);}

signed main(int argc, char **argv){
	registerGen(argc, argv, 1);
	int t1=atoi(argv[1]), t2=atoi(argv[2]);
	n=rnd.wnext(1, t1==1?smalln:maxn, 10), m=rnd.wnext(1, t1==1?smalln:maxn, 10);
	printf("%d %d\n", n, m);
	fup(i, 1, n+1)p[i]=i;
	rep(i, n)printf("%d%c", rnd.next(t1==2?maxhp/2:1, maxhp), " \n"[i==n-1]);
	rep(i, n)printf("%d%c", rnd.next(1, t1==2?maxhp/n/10:t2&3?maxhp/n:maxhp*10/n), " \n"[i==n-1]);
	rep(i, m){
		int x, y;
		do x=rnd.next(1, n), y=rnd.next(1, n); while(x==y||t2%3&&i<n-1&&rnd.next(1, n)<n-n/200&&Find(x)==Find(y));
		Union(x, y);
		printf("%d %d\n", x, y);
	}
}
