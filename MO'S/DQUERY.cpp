//Author:leninkumar
//http://www.spoj.com/problems/DQUERY/
//MO'S algorithm
#include <bits/stdc++.h>
#define MAXN 30011
#define MAXQ 200011
#define N 1000011
using namespace std;
struct node {
	int L, R, i;
} q[MAXQ];
int cnt[N], a[MAXN],ans[MAXQ], answer = 0, bsize;
bool cmp(node a, node b) {
	int x = a.L / bsize;
	int y = b.L / bsize;
	if (x != y) {
		return x < y;
	}
	return a.R < b.R;
}
inline void add(int pos) {
	cnt[a[pos]]++;
	if (cnt[a[pos]] == 1)
		answer++;
}
inline void remove(int pos) {
	cnt[a[pos]]--;
	if (cnt[a[pos]] == 0)
		answer--;
}
int main() {
	int n, m;
	scanf("%d", &n);
	bsize = sqrt(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &q[i].L, &q[i].R);
		q[i].L--;
		q[i].R--;
		q[i].i = i;
	}
	sort(q, q + m, cmp);
	int currentL = 0, currentR = 0;
	for (int i = 0; i < m; i++) {
		int L = q[i].L, R = q[i].R;
		while (currentL < L) {
			remove(currentL);
			currentL++;
		}
		while (currentL > L) {
			add(currentL - 1);
			currentL--;
		}
		while (currentR <= R) {
			add(currentR);
			currentR++;
		}
		while (currentR > R + 1) {
			remove(currentR - 1);
			currentR--;
		}
		ans[q[i].i] = answer;
	}
	for (int i = 0; i < m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
