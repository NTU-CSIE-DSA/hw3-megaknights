#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define int long long
#define rep(i,n) for(int i=0; i<(n); ++i)
#define fup(i,a,b) for(int i=(a); i<(b); ++i)
#define fdn(i,a,b) for(int i=(a); i>(b); --i)
#define kN 100005

void swap(int *a, int *b){int c=*a; *a=*b, *b=c;}

int n, m, t, p[kN], q[kN], sz[kN], atk[kN], hp[kN], dmg[kN], dmg2[kN*2], left[kN*2], right[kN*2], stk[kN], sum[kN], ns, dead[kN], ans[kN*2], dis[kN*2];
// p, q are the parent of the dsu1 and node of dsu1 in dsu2
bool vis[kN];
int Find(int x){ // return the root of x if x is alive, -1 otherwise
	int tt=hp[x]-dmg[x];
	while(x!=p[x])tt-=dmg[x=p[x]];
	return tt>0?x:-1;
}
void Union(int x, int y){ // x jumps to y
	x=Find(x), y=Find(y);
	if(!~x||!~y||x==y)return;
	left[t]=q[x], right[t]=q[y], dmg[y]+=atk[x], dmg2[q[y]]=atk[x];
	if(sz[x]<sz[y])swap(&x, &y);
	p[y]=x, q[x]=t, sz[x]+=sz[y], atk[x]+=atk[y], dmg[y]-=dmg[x];
}
void dfs0(int x){
	vis[x]=1;
	if(x>=n&&x==left[x])return;
	stk[ns]=x, sum[ns]=ns?sum[ns-1]+dmg2[x]:0, ++ns;
	if(x==left[x]&&sum[ns-1]>=hp[x]){
		int l=1, r=ns-1;
		while(r-l>1){
			int mid=l+r>>1;
			if(sum[ns-1]-sum[mid]<hp[x])r=mid;
			else l=mid;
		}
		++ans[left[stk[l-1]]], dead[x]=stk[l-1];
	}
	if(x!=left[x])dfs0(left[x]), dfs0(right[x]);
	--ns;
}
void dfs1(int x, int d){
	vis[x]=1, dis[x]=d;
	if(x!=left[x])ans[left[x]]+=ans[x], dfs1(left[x], d+1), ans[right[x]]+=ans[x], dfs1(right[x], d);
}

signed main(){
	scanf("%lld%lld", &n, &m);
	rep(i, n)scanf("%lld", hp+i);
	rep(i, n)scanf("%lld", atk+i);
	rep(i, n)p[i]=q[i]=i, dead[i]=-1;
	rep(i, n+m)left[i]=right[i]=i;
	for(t=n; t<n+m; ++t){
		int x, y;
		scanf("%lld%lld", &x, &y), --x, --y;
		Union(x, y);
	}
	return 0;
	fdn(i, m+n-1, n-1)if(!vis[i])dfs0(i);
	rep(i, m+n)vis[i]=0;
	fdn(i, m+n-1, n-1)if(!vis[i])dfs1(i, 0);
	rep(i, n)printf("%lld %lld\n", dis[i]-(~dead[i]?dis[dead[i]]:0), ans[i]-(~dead[i]?ans[dead[i]]:0));
}
