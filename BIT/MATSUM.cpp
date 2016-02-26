//Author:leninkumar
//http://www.spoj.com/problems/MATSUM/
//accepted code
//2D-BIT
#include <bits/stdc++.h>
using namespace std;
int BIT[1025][1025];
int n, t;
//for updating
void update(int x, int y, int val) {
	while (x <= n) {
		int y1=y;
		while (y1 <= n) {
				BIT[x][y1] += val;
				y1 += (y1 & -y1);
			}
		x += (x & -x);
	}
}
//for getting sum
int sum(int x, int y) {
	int res = 0;
	while (x) {
		int temp = y;
		while (temp) {
			res += BIT[x][temp];
			temp -= (temp & -temp);
		}
		x -= (x & -x);
	}
	return res;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		memset(BIT, 0, sizeof(BIT));
		while (1) {
			char str[10];
			scanf("%s",str);
			if (str[1] == 'E') {
				int x, y, val;
				scanf("%d%d%d", &x, &y, &val);
				int change=sum(x+1,y+1)+sum(x,y)-sum(x,y+1)-sum(x+1,y);
				update(x + 1, y + 1, val-change);
			} else if (str[1] == 'U') {
				int x1,y1,x2,y2;
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                int ans=sum(x2+1,y2+1)+sum(x1,y1)-sum(x1,y2+1)-sum(x2+1,y1);
                printf("%d\n",ans);
			} else
				break;
		}
	}
	return 0;
}
