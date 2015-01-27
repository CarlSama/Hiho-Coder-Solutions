#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<queue>

using namespace std;

/*
 * FBI WARNING
 * We can use randomize the achive 0(n*n)
 */

int level;
/*
 * bonus[i][j] means the ith level's jth room
 */
int bonus[111][111];
int best[111][111];

int solve(){
	for(int i=1;i<=level;i++){
		for(int j=1;j<=i;j++){
				best[i][j] = max(best[i-1][j-1],best[i-1][j]) + bonus[i][j];
		}
	}
}


int show(){
	int ans = 0;
	for(int i=1;i<=level;i++){
		ans = max(ans,best[level][i]);
	}
	return ans;
}

int main(){
	freopen("info","r",stdin);
	cin>>level;
	if(level <= 0){
		printf("%d\n",0);
		return 0;
	}
	for(int i=1;i<=level;i++){
		for(int j=1;j<=i;j++){
			cin>>bonus[i][j];
		}
	}

	solve();
	printf("%d\n",show());

	return 0;
}
	


