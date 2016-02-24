//Author:Leninkumar
//spoj.com/problems/PIE
//accepted code
#include <bits/stdc++.h>
#define MAX 10008
#define EPS 1e-6
using namespace std;
long double PI = 3.14159265358979323846264338327950;
int t, n, f;
long double vol[MAX];
//predicate for binary search
bool p(double val) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		double temp = vol[i];
		while (temp >= val) {
			temp -= val;
			cnt++;
			if (cnt == f)
				return true;
		}
		if (cnt == f)
			return true;
	}
	return false;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &f);
		f++;
		int r;
		for (int i = 0; i < n; i++) {
			scanf("%d", &r);
			vol[i] = PI * r * r;
		}
		sort(vol, vol + n);
		long double low = 0, high = vol[n - 1];//interval in which ans exists
		//binary search
		while (high - low > EPS) {
			long double mid = low + (high - low) / 2;
			if (p(mid))
				low = mid;
			else
				high = mid;
		}
		printf("%.4Lf\n", low);
	}
	return 0;
}
