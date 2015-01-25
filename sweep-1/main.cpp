#include<cstdio>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstring>

using namespace std;

/*
 * 1)Begin from enumarating the state of position 1 (exist or not), the state of rest position(like pos i) can be calculated based on  { width[i-1] - state[i-1] - state[i-2] }. 
 * 2)
 */

int n;
int width[100011];
int ans;
bool isValid[2];
int exist[100011];
int solution[100011];

bool valid(int curr){
	return (width[curr] == exist[curr-1] + exist[curr] + exist[curr+1]);
}

void show_res(){
	vector<int> must_exist,must_not_exist;
	int must_exist_num = 0, must_not_exit_num = 0;

	for(int i=1;i<=n;i++){
		if(solution[i] == 0){
			must_not_exit_num++;
			must_not_exist.push_back(i);
		}else if(solution[i] == 1){
			must_exist_num++;
			must_exist.push_back(i);
		}
	}

	printf("%d ",must_exist_num);
	for(int i=0;i<must_exist_num;i++){
		printf("%d ",must_exist[i]);
	}
	printf("\n");


	printf("%d ",must_not_exit_num);
	for(int i=0;i<must_not_exit_num;i++){
		printf("%d ",must_not_exist[i]);
	}
	printf("\n");
}

void solve(int curr){
	if(n == 1){
		solution[1] = width[1];
		return;
	}

	if(curr > n){
		if(valid(n)){
			if(!ans){
				memcpy(solution,exist,(n+1)*sizeof(int));	
			}else{
				for(int i=1;i<=n;i++){
					if(solution[i] != exist[i]){
						solution[i] = -1;
					}
				}
			}
			ans++;
		}	
		return;
	}

	exist[curr] = 0;
	if(curr==1 || valid(curr-1))
		solve(curr+1);

	exist[curr] = 1;
	if(curr==1 || valid(curr-1))
		solve(curr+1);
}

int main(){
	freopen("info","r",stdin);
	int task;
	cin>>task;

	exist[0] = 0;
	while(task--){
		cin>>n;
		exist[n+1] = 0;

		ans = 0;

		int i=1;
		while(i <= n){
			cin>>width[i];
			i++;
		}

		solve(1);
		show_res();
	}
	return 0;
}
