//Author:leninkumar
//http://www.spoj.com/problems/AGGRCOW/
//accepted code
#include <bits/stdc++.h>
#define MAX 100009
using namespace std;
int a[MAX], n, c, t;
//predicate
bool f(int x) {
	int cnt = 1, prev = a[0], j = 1;
	while (j < n) {
		if (a[j] - prev >= x) {
			cnt++;
			prev = a[j];
		}
		if (cnt == c)
			return true;
		j++;
	}
	return false;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &c);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		sort(a, a + n);
		int low = INT_MAX; //first value in interval
		int high = INT_MIN; //second value in interval
		for (int i = 0; i < n; i++) {
			if (a[i] > high)
				high = a[i];
			if (i != n - 1) {
				if (low > a[i + 1] - a[i])
					low = a[i + 1] - a[i];
			}
		}
		//binary search
		while (low < high) {
			int mid = low + (high - low + 1) / 2;
			if (f(mid))
				low = mid;
			else
				high = mid - 1;
		}
		printf("%d\n", low);
	}
	return 0;
}
