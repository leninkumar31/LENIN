//Author:leninkumar
//range update point query
//http://www.spoj.com/problems/UPDATEIT/
//accepted code
#include <bits/stdc++.h>
#define MAX 10009
using namespace std;
typedef long long ll;
int t, n, u,q;
ll BIT[MAX];
//to get sum
ll sum(int x) {
	ll res = 0;
	while (x > 0) {
		res += BIT[x];
		x -= (x & -x);//to get parent node
	}
	return res;
}
//for updates
void update(int x, int val) {
	while (x <= n) {
		BIT[x] += val;
		x += (x & -x);//to get next node
	}
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &u);
		memset(BIT, 0, (n + 1)*sizeof(ll));
		int  l, r,temp;
		while (u--) {
			scanf("%d%d%d", &l, &r,&temp);
				update(l+1,temp);
				update(r+2,-temp);
		}
		scanf("%d",&q);
		while(q--)
		{
			int val;
			scanf("%d",&val);
			printf("%lld\n",sum(val+1));
		}
	}
	return 0;
}
