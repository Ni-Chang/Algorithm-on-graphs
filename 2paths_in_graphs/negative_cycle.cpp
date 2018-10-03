//
//  main.cpp
//  negative cycle
//
//  Created by xiaonizi on 2018/2/8.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

#define MAX 10000000

vector<vector<int> > adj;
vector<vector<int> > cost;
vector<int> dist;
vector<int> nodes;

void Relax(int u, int v)
{
    if(dist[adj[u][v]]>(dist[u]+cost[u][v]))
    {
        dist[adj[u][v]]=(dist[u]+cost[u][v]);
    }
}

void VRelax(int u, int v)
{

    if(dist[adj[u][v]]>(dist[u]+cost[u][v]))
    {
        dist[adj[u][v]]=(dist[u]+cost[u][v]);
        nodes.push_back(u);
    }
}

void BellmanFord()
{
    dist[0]=0;
    int i, j, k;
    for(i=0; i<adj.size()-1; i++)
    {
        for(j=0; j<adj.size(); j++)
        {
            for(k=0; k<adj[j].size(); k++)
                Relax(j, k);
        }
    }
    for(j=0; j<adj.size(); j++)
    {
        for(k=0; k<adj[j].size(); k++)
            VRelax(j, k);
    }
}

int negative_cycle()
{
    BellmanFord();
    if(nodes.empty())
        return 0;
    else
        return 1;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    adj.resize(n);
    cost.resize(n);
    dist.resize(n, MAX);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle();
}
