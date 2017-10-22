#include "../base.hpp"

typedef vector <vector<int> > Graph;

/* Recursive function for finding centroid and calculating subtree size.
 * Returns {size, centroid}, where centroid can be -1 if no suitable vertex has
 * been found (happens only if the totcnt parameter is incorrect).
 *
 * Works on trees stored in (bidirectional) adjacency list, father is the
 * already visited neighbour. totcnt should equal to the count of vertices in
 * the tree (if already known). If totcnt is bogus, the function (obviously)
 * returns wrong centroid, but still counts subtree size correctly. */
pair<int, int> _find_centroid(const Graph &G, int v, int father, int totcnt) {
	int ourcnt = 1; // Size of the subtree rooted at v
	int centroid = -1;
	int biggest = 0; // Size of the biggest subtree rooted at some son of v
	for (int s: G[v]) {
		if (s == father)
			continue;

		int subcnt, possible_centroid;
		tie(subcnt, possible_centroid) = _find_centroid(G, s, v, totcnt);
		ourcnt += subcnt;
		biggest = max(subcnt, biggest);
		if (possible_centroid != -1)
			centroid = possible_centroid;
	}

	int above = totcnt - ourcnt;
	if (above <= totcnt / 2 && biggest <= totcnt / 2)
		centroid = v;

	return {ourcnt, centroid};
}

/* Utilises the previous function -- given a forest G and a vertex v, returns
 * the centroid of the tree containing v.
 * Time complexity: O(#visited vertices), memory complexity: O(#visited vertices) */
int find_centroid(const Graph &G, int v) {
	int n = _find_centroid(G, v, -1, 0).first;
	return _find_centroid(G, v, -1, n).second;
}

vector<int> counts; // see the example below

/* Centroid-decomposes the tree. A dummy function, calculates degree of each
 * vertex as an example. Destroys and recreates edges, preserving their order.
 * Time complexity: O(n log n), space complexity: O(n) */
void decompose(Graph &G, int start) {
	int v = find_centroid(G, start);
	// <cut here>
	counts[v] += G[v].size();
	// </cut here>

	for (int s: G[v]) {
		int pos = -1;
		while (G[s][++pos] != v)
			;

		swap(G[s][pos], G[s][G[s].size() - 1]);
		G[s].pop_back();
		decompose(G, s);
		G[s].push_back(v);
		swap(G[s][pos], G[s][G[s].size() - 1]);
	}

	// <cut here>
	for (int s: G[v])
		counts[s]++;
	// </cut here>
}

vector<int> example_decompose(Graph &G) {
	int n = G.size();
	counts = {};
	counts.resize(n);
	decompose(G, 0);
	return counts;
}
