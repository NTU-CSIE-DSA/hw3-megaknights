#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,n) for(int i=0; i<(n); ++i)
#define fup(i,a,b) for(int i=(a); i<(b); ++i)
#define fdn(i,a,b) for(int i=(a); i>(b); --i)
#define kN 100005

int n, m, atk[kN], hp[kN], p[kN], ans[kN];
int Find(int x){
	return x==p[x]?x:p[x]=Find(p[x]);
}
void Union(int x, int y){
	if(hp[x]<=0||hp[y]<=0)return;
	x=Find(x), y=Find(y);
	if(x==y)return;
	int tt=0;
	rep(i, n)if(hp[i]>0&&Find(i)==x)tt+=atk[i], ++ans[i];
	rep(i, n)if(Find(i)==y)hp[i]-=tt;
	p[y]=x;
}

signed main(){
	cin>>n>>m;
	rep(i, n)cin>>hp[i], p[i]=i;
	rep(i, n)cin>>atk[i];
	while(m--){
		int x, y;
		cin>>x>>y;
		Union(--x, --y);
	}
	rep(i, n)cout<<ans[i]<<" \n"[i==n-1];
}
