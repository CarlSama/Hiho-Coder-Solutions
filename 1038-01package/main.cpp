#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

int num,money;
int need[600];
int value[600];
/*
 * first  : from ith of elem(start from 1, while 0 means none)
 * second : money remain
 */
/*
 * 1) we can use dynamic programming
 * 2) we find only two level has been used !, so using rotate array 
 */
int dp[100001];

int solve(){
	for(int i=0;i<=money;i++){
		dp[i] = 0;
	}

	for(int i=1;i<=num;i++){
		for(int j=money;j>=need[i-1];j--){
			int orig = dp[j];
			dp[j] = max(dp[j] , dp[j-need[i-1]] + value[i-1]);
		}
	}

	return dp[money];
}

int main(){
	freopen("info","r",stdin);
	cin>>num>>money;

	for(int i=0;i<num;i++){
		cin>>need[i]>>value[i];
	}

	printf("%d\n",solve());
	return 0;
}

