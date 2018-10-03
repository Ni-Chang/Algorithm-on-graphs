//
//  main.cpp
//  components
//
//  Created by xiaonizi on 2018/2/1.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>

using std::vector;
using std::pair;

size_t n;
vector<bool> visited;
vector<int> CCnum;
vector<vector<int> > adj;

void Explore(int v, int cc)
{
    visited[v]=true;
    CCnum[v]=cc;
    int i;
    for(i=0; i<adj[v].size(); i++)
    {
        if(visited[adj[v][i]]==false)
            Explore(adj[v][i], cc);
    }
}

int number_of_components(vector<vector<int> > &adj) {
    int res = 0;
    int v;
    for(v=0; v<adj.size(); v++)
    {
        if(visited[v]==false)
        {
            Explore(v, res);
            res++;
        }
    }
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    visited.resize(n);
    CCnum.resize(n);
    adj.resize(n);
    int i;
    for(i=0; i<n; i++)
    {
        visited[i]=false;
    }
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << number_of_components(adj);
}

