#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 200000

#define int long long

#define get_sz(x) (heaps[(x)]->sz)
#define get_cap(x) (heaps[(x)]->cap)
#define get_heap_node(id, x) (heaps[(id)]->arr[(x)])
#define get_hp_in_heap(hid, x) (knight[get_heap_node((hid), (x)).id].hp)
#define par(x) ((x) >> 1)
#define alive(x) (knight[(x)].hp > 0)

typedef struct HeapNode {
  int id;
} HeapNode;

typedef struct Vector {
  int cap, sz, atk, dmg_tag, jmp_tag;
  HeapNode *arr;
} Vector;

typedef struct Node {
  int parent, atk, hp;
} Node;

Node knight[MAXN + 1];
Vector *heaps[MAXN + 1];
int ans[MAXN + 1];
int ret[MAXN + 1];

void grow(int heap_id) {
  //assert(get_sz(heap_id) == get_cap(heap_id));

  get_cap(heap_id) <<= 1;
  HeapNode *new_heap = (HeapNode*) malloc(sizeof(HeapNode) * get_cap(heap_id));
  
  for (int i = 0; i < get_sz(heap_id); ++i) {
    new_heap[i] = get_heap_node(heap_id, i);
  }
  //free(heaps[heap_id]->arr);
  heaps[heap_id]->arr = new_heap;
}

void push_up(int heap_id) {
  int curr = get_sz(heap_id);
  while (curr != 1 && get_hp_in_heap(heap_id, curr) < get_hp_in_heap(heap_id, par(curr))) {
    HeapNode tmp = get_heap_node(heap_id, curr);
    get_heap_node(heap_id, curr) = get_heap_node(heap_id, par(curr));
    get_heap_node(heap_id, par(curr)) = tmp;

    curr = par(curr);
  }
}

void push_down(int heap_id, int idx) {
  int lidx = (idx << 1) + 1, ridx = idx << 1;
  lidx = lidx >= get_sz(heap_id) ? idx : lidx;
  ridx = ridx >= get_sz(heap_id) ? idx : ridx;
  int min_idx = (get_hp_in_heap(heap_id, lidx) < get_hp_in_heap(heap_id, ridx) ? lidx : ridx);
  min_idx = (get_hp_in_heap(heap_id, min_idx) < get_hp_in_heap(heap_id, idx) ? min_idx : idx);

  if (min_idx == idx) return;

  HeapNode tmp = get_heap_node(heap_id, idx);
  get_heap_node(heap_id, idx) = get_heap_node(heap_id, min_idx);
  get_heap_node(heap_id, min_idx) = tmp;
  push_down(heap_id, min_idx);
  return;
}

void insert(int heap_id, HeapNode heap_node) {
#ifdef DEBUG
  fprintf(stderr, "id: %lld\n", heap_id);
  fprintf(stderr, "sz: %lld, cap: %lld, iid: %lld\n", heaps[heap_id]->sz, heaps[heap_id]->cap, heap_node.id);
#endif
  heaps[heap_id]->arr[get_sz(heap_id)] = heap_node;
  push_up(heap_id);
  get_sz(heap_id)++;

  if (get_sz(heap_id) == get_cap(heap_id)) {
    grow(heap_id);
  }
}

void pop(int heap_id) {
  get_sz(heap_id)--;
  get_heap_node(heap_id, 1) = get_heap_node(heap_id, get_sz(heap_id));
  push_down(heap_id, 1);
}

int get_root(int tar) {
  while (knight[tar].parent != tar) {
    tar = knight[tar].parent;
  }
  return tar;
}

int szarr[MAXN] = {};

signed main () {
  int n, m;
  scanf("%lld%lld", &n, &m);

  for (int i = 1; i <= n; ++i) {
    heaps[i] = (Vector*) malloc(sizeof(Vector));
    heaps[i]->cap = 2;
    heaps[i]->arr = (HeapNode*)malloc(sizeof(HeapNode) * heaps[i]->cap);
    heaps[i]->sz = 1;
    heaps[i]->dmg_tag = 0;
    heaps[i]->jmp_tag = 0;

    szarr[i] = 2;
  }

  for (int i = 1; i <= n; ++i) {
    int hp;
    scanf("%lld", &hp);
    insert(i, (HeapNode){i});
    knight[i].hp = hp;
  }

  for (int i = 1; i <= n; ++i) {
    int atk;
    scanf("%lld", &atk);
    knight[i] = (Node){i, atk, knight[i].hp};
    heaps[i]->atk = atk;
  }

  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%lld%lld", &x, &y);
#ifdef DEBUG
    fprintf(stderr, "================\n");
#endif

    if (!alive(x) || !alive(y)) {
#ifdef DEBUG
      fprintf(stderr, "not alive\n");
#endif
      continue;
    }

    int x_root = get_root(x), y_root = get_root(y);
#ifdef DEBUG
    fprintf(stderr, "x: %lld, y: %lld\n", x_root, y_root);
#endif
    if (x_root == y_root) {
#ifdef DEBUG
      fprintf(stderr, "same dsu\n");
#endif
      continue;
    }

    int new_root = 0;
#ifdef DEBUG
    fprintf(stderr, "x_size: %lld, y_size: %lld\n", get_sz(x_root), get_sz(y_root));
#endif
    if (get_sz(x_root) < get_sz(y_root)) {
#ifdef DEBUG
      fprintf(stderr, "jmp is smaller\n");
#endif
      heaps[y_root]->dmg_tag += heaps[x_root]->atk;
      while (get_sz(x_root) != 1) {
#ifdef DEBUG
        fprintf(stderr, "mv: %lld\n", get_heap_node(x_root, 1).id);
#endif
        get_hp_in_heap(x_root, 1) += heaps[y_root]->dmg_tag;
        get_hp_in_heap(x_root, 1) -= heaps[x_root]->dmg_tag;
        ans[get_heap_node(x_root, 1).id] += heaps[x_root]->jmp_tag;
        ans[get_heap_node(x_root, 1).id] -= heaps[y_root]->jmp_tag;
        ans[get_heap_node(x_root, 1).id]++;

        knight[get_heap_node(x_root, 1).id].parent = y_root;

        insert(y_root, get_heap_node(x_root, 1));
        szarr[y_root]++;
        szarr[x_root]--;
        pop(x_root);
      }
      heaps[y_root]->atk += heaps[x_root]->atk;


      //free(heaps[x_root]->arr);
      //free(heaps[x_root]);
#ifdef DEBUG
      fprintf(stderr, "free %lld\n", x_root);
#endif
      new_root = y_root;
    }
    else {
#ifdef DEBUG
      fprintf(stderr, "jmp is bigger\n");
#endif
      heaps[x_root]->jmp_tag++;
#ifdef DEBUG
      int cnt = 0;
      int visited[1001] = {};
#endif
      while (get_sz(y_root) != 1) {
#ifdef DEBUG
        fprintf(stderr, "mv: %lld\n", get_heap_node(y_root, 1).id);
#endif
        get_hp_in_heap(y_root, 1) -= heaps[x_root]->atk;
        get_hp_in_heap(y_root, 1) -= heaps[y_root]->dmg_tag;
        get_hp_in_heap(y_root, 1) += heaps[x_root]->dmg_tag;
        ans[get_heap_node(y_root, 1).id] += heaps[y_root]->jmp_tag;
        ans[get_heap_node(y_root, 1).id] -= heaps[x_root]->jmp_tag;

        knight[get_heap_node(y_root, 1).id].parent = x_root;
#ifdef DEBUG
        if (visited[get_heap_node(y_root, 1).id]) {
          fprintf(stderr, "pop same thing\n");
        }
        visited[get_heap_node(y_root, 1).id] = 1;
        cnt++;
#endif

        insert(x_root, get_heap_node(y_root, 1));
        szarr[x_root]++;
        szarr[y_root]--;
        pop(y_root);
      }
#ifdef DEBUG
      fprintf(stderr, "mv cnt: %lld\n", cnt);
#endif
      heaps[x_root]->atk += heaps[y_root]->atk;

      //free(heaps[y_root]->arr);
      //free(heaps[y_root]);
#ifdef DEBUG
      fprintf(stderr, "free %lld\n", y_root);
#endif
      new_root = x_root;
    }

#ifdef DEBUG
    fprintf(stderr, "hp: %lld, dmg: %lld\n", get_hp_in_heap(new_root, 1), heaps[new_root]->dmg_tag);
#endif
    while (get_sz(new_root) > 1 && get_hp_in_heap(new_root, 1) <= heaps[new_root]->dmg_tag) {
#ifdef DEBUG
      fprintf(stderr, "id: %lld, hp: %lld, dmg: %lld\n", get_heap_node(new_root, 1).id, get_hp_in_heap(new_root, 1), heaps[new_root]->dmg_tag);
#endif
      ret[get_heap_node(new_root, 1).id] = ans[get_heap_node(new_root, 1).id] + heaps[new_root]->jmp_tag;
      heaps[new_root]->atk -= knight[get_heap_node(new_root, 1).id].atk;
      get_hp_in_heap(new_root, 1) -= heaps[new_root]->dmg_tag;
      pop(new_root);
      szarr[new_root]--;
    }

    fprintf(stderr, "record sz: %lld, true sz: %lld\n", get_sz(new_root), szarr[new_root]);
    //assert(get_sz(new_root) == szarr[new_root]);

#ifdef DEBUG
    fprintf(stderr, "after: %lld\n", get_sz(new_root));
    
    fprintf(stderr, "hp: ");
    for (int i = 1; i <= n; ++i) {
      fprintf(stderr, "%lld ", knight[i].hp - heaps[get_root(i)]->dmg_tag);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "par: ");
    for (int i = 1; i <= n; ++i) {
      fprintf(stderr, "%lld ", knight[i].parent);
    }
    fprintf(stderr, "\n");
#endif
  }

  for (int i = 1; i <= n; ++i) {
    int root = get_root(i);
    ans[i] += heaps[root]->jmp_tag;

    if (alive(i)) {
      ret[i] = ans[i];
    }

    printf("%lld ", ret[i]);
  }
  printf("\n");

  return 0;
}

