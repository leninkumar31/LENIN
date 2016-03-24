//Author:leninkumar
//http://codeforces.com/contest/86/problem/D
//MO's algorithm
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#define MAX 200010
#define N 1000010
using namespace std;
typedef long long int ll;
typedef struct node {
	int L, R, i;
} node;
int a[MAX], cnt[N], bsize;
ll answer = 0;
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
	answer = answer - (ll) (cnt[a[pos]] - 1) * (cnt[a[pos]] - 1) * a[pos]
			+ (ll) (cnt[a[pos]]) * (cnt[a[pos]]) * a[pos];
}
inline void remove(int pos) {
	cnt[a[pos]]--;
	answer = answer - (ll) (cnt[a[pos]] + 1) * (cnt[a[pos]] + 1) * a[pos]
			+ (ll) (cnt[a[pos]]) * (cnt[a[pos]]) * a[pos];
}
int main() {
	int n, t;
	scanf("%d%d", &n, &t);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	node q[t];
	for (int i = 0; i < t; i++) {
		scanf("%d%d", &q[i].L, &q[i].R);
		q[i].L--;
		q[i].R--;
		q[i].i = i;
	}
	bsize = sqrt(n);
	sort(q, q + t, cmp);
	ll ans[t];
	int cL = 0, cR = 0;
	for (int i = 0; i < t; i++) {
		int L = q[i].L, R = q[i].R;
		while (cL < L) {
			remove(cL);
			cL++;
		}
		while (cL > L) {
			add(cL - 1);
			cL--;
		}
		while (cR <= R) {
			add(cR);
			cR++;
		}
		while (cR > R + 1) {
			remove(cR - 1);
			cR--;
		}
		ans[q[i].i] = answer;
	}
	for (int i = 0; i < t; i++)
		cout << ans[i] << "\n";
	return 0;
}
