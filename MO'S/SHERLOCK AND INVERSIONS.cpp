//Author:leninkumar
//https://www.codechef.com/problems/IITI15
//MO's+BIT
#include <bits/stdc++.h>
#define MAX 20010
using namespace std;
typedef struct node {
	int L, R, i;
} node;
typedef long long ll;
int bsize, n, m;
ll BIT[MAX], answer = 0;
bool cmp(node a, node b) {
	int x = a.L / bsize;
	int y = b.L / bsize;
	if (x != y)
		return x < y;
	return a.R < b.R;
}
void update(int x, int val) {
	while (x <= n) {
		BIT[x] += val;
		x += (x & -x);
	}
}
ll sum(int x) {
	ll res = 0;
	while (x) {
		res += BIT[x];
		x -= (x & -x);
	}
	return res;
}
int main() {
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int b[n];
	for (int i = 0; i < n; i++)
		b[i] = a[i];
	sort(b, b + n);
	for (int i = 0; i < n; i++)
		a[i] = 1 + (lower_bound(b, b + n, a[i]) - b);
	scanf("%d", &m);
	node q[m];
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &q[i].L, &q[i].R);
		q[i].L--;
		q[i].R--;
		q[i].i = i;
	}
	bsize = sqrt(n);
	sort(q, q + m, cmp);
	ll ans[m];
	int cL = 0, cR = 0;
	for (int i = 0; i < m; i++) {
		int L = q[i].L, R = q[i].R;
		while (cL < L) {
			answer -= sum(a[cL] - 1);
			update(a[cL], -1);
			cL++;
		}
		while (cL > L) {
			answer += sum(a[cL - 1] - 1);
			update(a[cL - 1], 1);
			cL--;
		}
		while (cR <= R) {
			answer += sum(n) - sum(a[cR]);
			update(a[cR], 1);
			cR++;
		}
		while (cR > R + 1) {
			answer -= sum(n) - sum(a[cR - 1]);
			update(a[cR - 1], -1);
			cR--;
		}
		ans[q[i].i] = answer;
	}
	for (int i = 0; i < m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
