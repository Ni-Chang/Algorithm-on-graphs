//
//  main.cpp
//  shortest_paths
//
//  Created by xiaonizi on 2018/2/8.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

//#define MAX 10000000000000
vector<vector<int> > adj;
vector<vector<int> > cost;
vector<long long> dist;
vector<int> reachable;
vector<int> shortest;
queue<int> nodes;

void Relax(int u, int v)
{
    if(dist[adj[u][v]]>(dist[u]+cost[u][v]))
    {
        dist[adj[u][v]]=(dist[u]+cost[u][v]);
        reachable[adj[u][v]]=1;
    }
}

void VRelax(int u, int v)
{
    if(dist[adj[u][v]]>(dist[u]+cost[u][v]))
    {
        dist[adj[u][v]]=(dist[u]+cost[u][v]);
        nodes.push(u);
    }
}

void BellmanFord(int s)
{
    dist[s]=0;
    int i, j, k;
    for(i=0; i<adj.size()-1; i++)
    {
        for(j=0; j<adj.size(); j++)
        {
            if(dist[j]<LLONG_MAX)
                for(k=0; k<adj[j].size(); k++)
                    Relax(j, k);
        }
    }
    for(j=0; j<adj.size(); j++)
    {
        if(dist[j]<LLONG_MAX)
            for(k=0; k<adj[j].size(); k++)
                VRelax(j, k);
    }
}

void BFS()
{
    int u, i;
    while(!nodes.empty())
    {
        u=nodes.front();
        nodes.pop();
        shortest[u]=0;
        for(i=0; i<adj[u].size(); i++)
        {
            if(shortest[adj[u][i]]==1)
            {
                nodes.push(adj[u][i]);
            }
        }
    }
}

void shortest_paths(int s)
{
    reachable[s]=1;
    BellmanFord(s);
    if(!nodes.empty())
        BFS();
}

int main()
{
    int n, m, s;
    std::cin >> n >> m;
    adj.resize(n);
    cost.resize(n);
    dist.resize(n, LLONG_MAX);
    reachable.resize(n, 0);
    shortest.resize(n, 1);
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    cin >> s;
    s--;
    shortest_paths(s);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            cout << "*\n";
        } else if (!shortest[i]) {
            cout << "-\n";
        } else {
            cout << dist[i] << "\n";
        }
    }
}

