struct edge { int dest, bcc, twin; };

int N, M;
vector< vector<edge> > G;
vector<int> visited;
stack<int> vstack, estack;
int cur_bcc, cur_time;

int search(int v) {
    int result = visited[v] = cur_time++;
    for (int i = 0; i < int( G[v].size() ); ++i) if (!G[v][i].bcc) {
        vstack.push(v); estack.push(i);
        int d = G[v][i].dest, t = G[v][i].twin;
        G[d][t].bcc = -1;
        int r = visited[d] ? visited[d] : search(d);
        if (r >= visited[v]) {
            int a,b;
            do {
                a=vstack.top(); vstack.pop(); 
                b=estack.top(); estack.pop();
                G[a][b].bcc  =  G[ G[a][b].dest ][ G[a][b].twin ].bcc  =  cur_bcc;
            } while (a!=v || b!=i);
            ++cur_bcc;
        }
        result = min(result,r);
    }
    return result;
}

int main() {
    int N; cin >> N;
    G.resize(N);
    int M; cin >> M;
    while (M--) {
        int x, y; cin >> x >> y;
        edge e1, e2;
        e1.dest=y; e1.bcc=0; e1.twin=G[y].size();
        e2.dest=x; e2.bcc=0; e2.twin=G[x].size();
        G[x].push_back(e1);
        G[y].push_back(e2);
    }
    cur_bcc = cur_time = 1;
    visited.clear();
    visited.resize(N,0);
    for (int i=0; i<N; ++i) if (!visited[i]) search(i);
}
