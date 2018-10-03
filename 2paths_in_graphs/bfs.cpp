//
//  main.cpp
//  bfs
//
//  Created by xiaonizi on 2018/2/7.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> dist;
queue<int> Q;

void BFS(vector<vector<int> > adj, int s)
{
    dist[s]=0;
    Q.push(s);
    int u, i, j;
    while(!Q.empty())
    {
        u=Q.front();
        Q.pop();
        for(i=0; i<adj[u].size(); i++)
        {
            if(dist[adj[u][i]]==-1)
            {
                Q.push(adj[u][i]);
                dist[adj[u][i]]=dist[u]+1;
            }
        }
    }
}

int distance(vector<vector<int> > &adj, int s, int t)
{
    BFS(adj, s);
    return dist[t];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    dist.resize(n, -1);
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--;
    t--;
    std::cout << distance(adj, s, t);
}
