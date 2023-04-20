#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define int long long
#define rep(i,n) for(int i=0; i<(n); ++i)
#define fup(i,a,b) for(int i=(a); i<(b); ++i)
#define fdn(i,a,b) for(int i=(a); i>(b); --i)
#define left(a) (((a)<<1)+1)
#define right(a) (((a)<<1)+2)
#define parent(a) ((a)-1>>1)
#define kN 1000006

typedef struct heap{int v, id;}heap;
bool cmp(const heap a, const heap b){return a.v<b.v||a.v==b.v&&a.id<b.id;}
void swaph(heap *a, heap *b){heap c=*a; *a=*b, *b=c;}
void swapi(int *a, int *b){int c=*a; *a=*b, *b=c;}
heap toHeap(int v, int id){heap a; return a.v=v, a.id=id, a;}

typedef struct Heap{heap *a; int sz, mxsz;}Heap;
void init(Heap *a){a->a=(heap*)malloc(sizeof(heap)), a->sz=0, a->mxsz=1;}
void ins(Heap *a, const heap b){
	heap *c;
	if(a->sz==a->mxsz)
		c=(heap*)malloc(sizeof(heap)*a->mxsz*2),
		memcpy(c, a->a, sizeof(heap)*a->mxsz),
		free(a->a), a->a=c, a->mxsz<<=1;
	c=a->a, c[a->sz]=b;
	for(int i=a->sz++; i; i=parent(i))
		if(cmp(c[i], c[parent(i)]))swaph(c+i, c+parent(i));
		else return;
}
void del(Heap *a){
	heap *c=a->a;
	c[0]=c[--a->sz];
	for(int i=0; left(i)<a->sz; )
		if(right(i)<a->sz){
			if(cmp(c[i], c[left(i)])&&cmp(c[i], c[right(i)]))return;
			if(cmp(c[left(i)], c[right(i)]))swaph(c+i, c+left(i)), i=left(i);
			else swaph(c+i, c+right(i)), i=right(i);
		}
		else if(cmp(c[left(i)], c[i])){
			swaph(c+i, c+left(i)), i=left(i);
			return;
		}
		else return;
}
void out(Heap *a){for(int i=0; i<a->sz; ++i)printf("%lld%c", a->a[i].v, " \n"[i==a->sz-1]);}

typedef struct node{
	int p, sz, atk0, atk, ans, dg, gg, adj; // gg: default -1, record where it is dead, adj: if dead, adjust the ans
	Heap hp;
}node;

node a[kN];
int n, m, *G[kN], deg[kN], *H[kN], nh[kN]; // H: what is dead there

int Find(int x){return x==a[x].p?x:Find(a[x].p);}
void Union(int x, int y){ // x jump to y
	if(~a[x].gg||~a[y].gg)return;
	x=Find(x), y=Find(y);
	if(x==y)return;
	a[y].dg+=a[x].atk;
	while(a[y].hp.sz&&a[y].hp.a[0].v<=a[y].dg){
		int z=a[y].hp.a[0].id;
		a[y].atk-=a[z].atk0, a[z].gg=y, a[z].adj=a[y].ans, del(&a[y].hp);
	}
	++a[x].ans;
	//if(a[x].sz<a[y].sz)swapi(&x, &y);
	a[y].p=x, a[x].sz+=a[y].sz, a[x].atk+=a[y].atk, a[y].ans-=a[x].ans;
	rep(i, a[y].hp.sz)ins(&a[x].hp, toHeap(a[y].hp.a[i].v-a[y].dg+a[x].dg, a[y].hp.a[i].id));
}

void dfs(int x){
	rep(i, nh[x])a[H[x][i]].adj-=a[x].ans;
	rep(i, deg[x])a[G[x][i]].ans+=a[x].ans, dfs(G[x][i]);
}

signed main(){
	scanf("%lld%lld", &n, &m);
	rep(i, n)a[i].p=i, init(&a[i].hp), a[i].sz=1, a[i].ans=a[i].dg=a[i].adj=0, a[i].gg=-1;
	int hp, x, y;
	rep(i, n)scanf("%lld", &hp), ins(&a[i].hp, toHeap(hp, i));
	rep(i, n)scanf("%lld", &a[i].atk0), a[i].atk=a[i].atk0;
	while(m--)scanf("%lld%lld", &x, &y), Union(--x, --y);
	rep(i, n)a[i].p!=i&&++deg[a[i].p], ~a[i].gg&&++nh[a[i].gg];
	rep(i, n)G[i]=(int*)malloc(sizeof(int)*deg[i]), H[i]=(int*)malloc(sizeof(int)*nh[i]), deg[i]=nh[i]=0;
	rep(i, n)a[i].p!=i&&(G[a[i].p][deg[a[i].p]++]=i), ~a[i].gg&&(H[a[i].gg][nh[a[i].gg]++]=i);
	rep(i, n)if(a[i].p==i)dfs(i);
	rep(i, n)printf("%lld%c", a[i].ans+a[i].adj, " \n"[i==n-1]);
}
