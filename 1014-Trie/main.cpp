#include<iostream>
#include<cstdio>

using namespace std;

struct TrieTreeNode{
	int prefix_word_num;
	TrieTreeNode *next[26];

	TrieTreeNode():prefix_word_num(0){
		for(int i=0;i<26;i++){
			next[i] = 0;
		}
	}
};

class TrieTree{
	private:
		TrieTreeNode *root;
		int char_to_idx;
	public:
		TrieTree();
		virtual ~TrieTree();

		void build(char *str);
		int query(char *str);
};

TrieTree::TrieTree(){
	root = new TrieTreeNode();
}

TrieTree::~TrieTree(){
	//delete all tree
}

void TrieTree::build(char *str){
	int idx = 0;
	TrieTreeNode *curr = root;
	while(str[idx] != '\0'){
		char_to_idx = str[idx] - 'a';
		if(0 == curr->next[char_to_idx]){
			curr->next[char_to_idx] = new TrieTreeNode();
		}
		curr->next[char_to_idx]->prefix_word_num++;
		curr = curr->next[char_to_idx];

		idx++;
	}
}

int TrieTree::query(char *str){
	int idx = 0;
	TrieTreeNode *curr = root;
	while(str[idx] != '\0'){
		char_to_idx = str[idx] - 'a';
		if(0 == curr->next[char_to_idx]){
			return 0;
		}
		curr = curr->next[char_to_idx];
		idx++;
	}

	return curr->prefix_word_num;
}

int main(){
	freopen("info","r",stdin);

	int n;
	cin>>n;
	char str[11];
	TrieTree tt;
	while(n--){
		cin>>str;
		tt.build(str);
	}
	int m;
	cin>>m;
	while(m--){
		cin>>str;
		printf("%d\n", tt.query(str));
	}

	return 0;
}


