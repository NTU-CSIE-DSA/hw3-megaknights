#include <stdio.h>
#include <string.h>

#define MAXN 200005

int n, m;
int h[MAXN], a[MAXN];
int jmps[MAXN];

struct attack {
    int x, y;
} att[MAXN];

int pos[MAXN], stk[MAXN], top;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", h + i);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &att[i].x, &att[i].y);
    }

    for (int i = 1; i <= n; ++i) pos[i] = i;
    for (int i = 1; i <= m; ++i) {
        int x = att[i].x, y = att[i].y;
        if (h[x] > 0 && h[y] > 0 && pos[x] != pos[y]) {
            int damage = 0, cnt = 0;
            top = 0;
            for (int j = 1; j <= n; ++j) {
                if (pos[j] == pos[x]) {
                    damage += a[j];
                    stk[++top] = j;
                }
            }
            while (top > 0) {
                int j = stk[top--];
                if (h[j] > damage) {
                    h[j] -= damage;
                    ++cnt;
                } else {
                    damage -= h[j];
                    h[j] = 0;
                }
            }
            jmps[x] += cnt;
            pos[x] = pos[y];
        }
    }
    for (int i = 1; i <= n; ++i) printf("%d ", jmps[i]);
    printf("\n");
    return 0;
}

