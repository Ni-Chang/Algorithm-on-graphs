//
//  main.cpp
//  bipartite
//
//  Created by xiaonizi on 2018/2/7.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> token;
queue<int> Q;

int bipartite(vector<vector<int> > &adj) {
    token[0]=1;
    Q.push(0);
    int u, i;
    while(!Q.empty())
    {
        u=Q.front();
        Q.pop();
        for(i=0; i<adj[u].size(); i++)
        {
            if(token[adj[u][i]]==0)
            {
                Q.push(adj[u][i]);
                token[adj[u][i]]=-token[u];
            }
            else if(token[adj[u][i]]==token[u])
                return 0;
        }
    }
    return 1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    token.resize(n, 0);
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    cout << bipartite(adj);
}

