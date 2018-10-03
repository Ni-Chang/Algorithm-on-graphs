//
//  main.cpp
//  dijkstra
//
//  Created by xiaonizi on 2018/2/8.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> dist;

int ExtractMin(vector<int> &H)
{
    int i, value;
    int temp=dist[H[0]];
    int num=0;
    for(i=1; i<H.size(); i++)
    {
        if(dist[H[i]]<temp)
        {
            temp=dist[H[i]];
            num=i;
        }
    }
    value=H[num];
    H.erase(H.begin()+num);
    return value;
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t)
{
    vector<int> H;
    int u, i;
    dist[s]=0;
    H.push_back(s);
    while(!H.empty())
    {
        u=ExtractMin(H);
        for(i=0; i<adj[u].size(); i++)
        {
            if(dist[adj[u][i]]>(dist[u]+cost[u][i]) || dist[adj[u][i]]==-1)
            {
                dist[adj[u][i]]=(dist[u]+cost[u][i]);
                H.push_back(adj[u][i]);
            }
        }
    }
    return dist[t];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    dist.resize(n, -1);
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    int s, t;
    std::cin >> s >> t;
    s--;
    t--;
    std::cout << distance(adj, cost, s, t);
}

