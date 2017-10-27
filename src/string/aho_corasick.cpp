#include "../base.hpp"

inline int normalize(char c) { return c - 'a'; }
inline int countBits(int a) { return __builtin_popcount(a); }
void occurence(int i, int id);

struct Trie {
	ll bitmask = 0;  // i-th bit is set IFF there is an edge "'a' + i"
	vector <Trie *> sons = {};  // sorted in alphabetical order
	int end_of = -1;  // index of the needle ending here or -1
	Trie *back = NULL, *output = NULL;  // edges
	char letter = '\0';  // the letter on the edge from parent to here

	Trie (char c) : letter(c) {}
	~Trie() { for (auto a: sons) delete a; }
	inline bool hasChild(char c) { return bitmask & (1 << normalize(c)); }
	inline int childIndex(char c) { return countBits(bitmask % (1 << normalize(c))); }
	inline void createChild(char c) {
		sons.insert(sons.begin() + childIndex(c), new Trie(c));  // maintain ordering
		bitmask |= (1 << normalize(c));
	}
	Trie *childNode(char c) {
		if (!hasChild(c))  createChild(c);
		return sons[childIndex(c)];
	}
};

Trie *ACStep(Trie *state, char c) {
	while (state->back && !state->hasChild(c))
		state = state->back;
	return (state->hasChild(c)) ? state->childNode(c) : state;
}

void insert(Trie *node, string s, int needle_id) {
	for (auto c : s)
		node = node->childNode(c);
	node->end_of = needle_id;
}

Trie *constructAC(vector<string> words) {
	Trie *root = new Trie('\0');
	rep(i, 0, words.size()) insert(root, words[i], i);

	queue<pair<Trie *, Trie*>> q;
	for (auto s : root->sons)  q.push({s, root});
	while (q.size()) {
		Trie *state, *parent;
		tie(state, parent) = q.front(); q.pop();
		state->back = (parent != root) ? ACStep(parent->back, state->letter) : root;
		state->output = (state->back->end_of >= 0) ? state->back : state->back->output;
		for (auto next : state->sons)
			q.push({next, state});
	}
	
	return root;
}

void AC(string str, vector<string> words) {
	Trie *state = constructAC(words);
	rep(i, 0, str.size()) {
		state = ACStep(state, str[i]);
		for (Trie *p = state; p; p = p->output)
			if (p->end_of >= 0)
				occurence(i - words[p->end_of].size() + 1, p->end_of);
	}
}
