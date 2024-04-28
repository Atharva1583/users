#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

class Graph
{
    int vertices;
    vector<vector<int>> adj;

public:
    Graph(int n)
    {
        vertices = n;
        cout << "Enter number of edges:" << endl;
        adj.resize(n);
        int m;
        cin >> m;
        while (m--)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    void sequentialBfs()
    {
        queue<int> q;
        vector<int> vis(vertices);
        if (vertices == 0)
        {
            return;
        }
        cout << "Enter start Node:" << endl;
        int startNode;
        cin >> startNode;
        q.push(startNode);
        cout << startNode << " ";
        vis[startNode] = 1;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (auto it : adj[node])
            {
                if (!vis[it])
                {
                    cout << it << " ";
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        cout << endl;
    }
    void bfs()
    {
        queue<int> q;
        vector<int> vis(vertices);
        if (vertices == 0)
        {
            return;
        }
        cout << "Enter start node:" << endl;
        int startNode;
        cin >> startNode;
        q.push(startNode);
        cout << startNode << " ";
        vis[startNode] = 1;
        while (!q.empty())
        {
            int node;
#pragma omp critical
            {
                node = q.front();
                q.pop();
            }
#pragma omp parallel for
            for (auto it : adj[node])
            {
                if (!vis[it])
                {
                    cout << it << " ";
                    vis[it] = 1;
#pragma omp critical
                    q.push(it);
                }
            }
        }
        cout << endl;
    }
    void dfs()
    {
        stack<int> st;
        vector<int> vis(vertices);
        if (vertices == 0)
        {
            return;
        }
        cout << "Enter start node:" << endl;
        int startNode;
        cin >> startNode;
        st.push(startNode);
        vis[startNode] = 1;
        while (!st.empty())
        {
            int node;
#pragma omp critical
            {
                node = st.top();
                st.pop();
            }
            cout << node << " ";
#pragma omp parallel for
            for (auto it : adj[node])
            {
                if (!vis[it])
                {
#pragma omp critical
                    st.push(it);
                    vis[it] = 1;
                }
            }
        }
        cout << endl;
    }

    void sequentialDfs()
    {
        stack<int> st;
        vector<int> vis(vertices);
        if (vertices == 0)
        {
            return;
        }
        cout << "Enter start node:" << endl;
        int startNode;
        cin >> startNode;
        st.push(startNode);
        vis[startNode] = 1;
        while (!st.empty())
        {
            int node;

            node = st.top();
            st.pop();

            cout << node << " ";

            for (auto it : adj[node])
            {
                if (!vis[it])
                {

                    st.push(it);
                    vis[it] = 1;
                }
            }
        }
        cout << endl;
    }
};

int main()
{
    int n;

    cout << "Enter number of vertices:" << endl;
    cin >> n;
    Graph g = Graph(n);
    double start = omp_get_wtime();
    g.bfs();
    double end = omp_get_wtime();
    cout<<"Time taken by parallel BFS: "<<(end-start)<<endl;
    start = omp_get_wtime();
    g.sequentialBfs();
    end = omp_get_wtime();
    cout<<"Time taken by Sequential BFS: "<<(end-start)<<endl;
    start = omp_get_wtime();
    g.dfs();
    end = omp_get_wtime();
    cout<<"Time taken by parallel DFS: "<<(end-start)<<endl;
    start = omp_get_wtime();
    g.sequentialDfs();
    end = omp_get_wtime();
    cout<<"Time taken by sequential dFS: "<<(end-start)<<endl;
    return 0;
}