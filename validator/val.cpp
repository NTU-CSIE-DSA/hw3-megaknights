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
    registerValidation(argc, argv);
	//int t1=atoi(argv[1]), t2=atoi(argv[2]);
    n=inf.readInt(1, maxn, "n"), inf.readSpace(), m=inf.readInt(1, maxn, "m");
    inf.readEoln();
	rep(i, n){
		inf.readInt(1, maxhp);
		if(i==n-1)inf.readEoln();
		else inf.readSpace();
	}
	rep(i, n){
		inf.readInt(1, maxhp);
		if(i==n-1)inf.readEoln();
		else inf.readSpace();
	}
	fup(i, 1, n+1)p[i]=i;
	while(m--){
		int x, y;
		x=inf.readInt(1, n), inf.readSpace(), y=inf.readInt(1, n), inf.readEoln();
		ensuref(x!=y, "x==y");
		Union(x, y);
	}
	inf.readEof();
}
