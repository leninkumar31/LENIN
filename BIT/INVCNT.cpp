//Author:leninkumar
//http://www.spoj.com/problems/INVCNT/
//accepted code
//coordinate compression+BIT
#include <bits/stdc++.h>
#define MAX 200009
using namespace std;
typedef long long ll;
int t, n;
ll BIT[MAX];
//for update
void update(int x, int val) {
	while (x <= n) {
		BIT[x] += val;
		x += (x & -x);
	}
}
//for sum
ll sum(int x) {
	ll res = 0;
	while (x) {
		res += BIT[x];
		x -= (x & -x);
	}
	return res;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int a[n], b[n];
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		//coordinate compression-O(nlog(n)) time
		for(int i=0;i<n;i++)
			b[i]=a[i];
		sort(b, b + n);
		for (int i = 0; i < n; i++)
			a[i] = int(lower_bound(b, b + n, a[i]) - b) + 1;
		memset(BIT, 0, (n + 1) * sizeof(ll));
		ll ans=0;
        for(int i=n-1;i>=0;i--)
        {
           //for every element from back to front how many elements smaller than
           //the current element already encountered
        	ans+=sum(a[i]);
           //update all elements greater than current element
        	update(a[i]+1,1);
        }
        printf("%lld\n",ans);
	}
	return 0;
}
