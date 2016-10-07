#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int> > g;

int start, target;
int d;

vector<bool> mark;
vector<int> q;
vector<int> p;

void input()
{
    ifstream in("input.txt");
    in >> n >> m;

    g.assign(n, vector<int>());

    for (int i=0; i<m; ++i) {
        int u,v;
        in >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

void outg()
{
    for(int u=0; u<n; ++u) {
        cout << u << ": ";
        for(int i=0, adjsz=g[u].size(); i<adjsz; ++i) {
            int v = g[u][i];
            cout << v << " ";
        }
        cout << endl;
    }
}

bool enq(vector<int>& q, int u, int parent)
{
    q.push_back(u);
    mark[u] = true;
    p[u] = parent;

    return u == target;
}

void bfs()
{
    d = 0;
    q.clear();

    mark.assign(n, false);
    p.assign(n, -1);

    if (enq(q, start, -1))
        return;

    while (!q.empty()) {
        ++d;
        vector<int> nextq;

        for(int i=0, qsz = q.size(); i<qsz; ++i) {
            int u = q[i];

            for(int j=0, adjsz = g[u].size(); j<adjsz; ++j) {
                int v = g[u][j];

                if (mark[v])
                    continue;

                if (enq(nextq, v, u))
                    return;
            }
        }

        q.swap(nextq);
    }
}

void printp()
{
//    for(int i=0, sz = p.size(); i<sz; ++i)
//        cout << p[i] << " ";

    int u = target;

    while (u != -1) {
        cout << u << " ";
        u = p[u];
    }

    cout << endl;
}

int main()
{
    input();
    outg();

    for(;;) {
        cin >> start >> target;
        if (start == -1 || target == -1)
            break;

        bfs();
        cout << d << endl;
        printp();
    }
}
