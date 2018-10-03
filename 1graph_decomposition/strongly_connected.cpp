//
//  main.cpp
//  strongly_connected
//
//  Created by xiaonizi on 2018/2/6.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> visited;
vector<int> rev_visited;
vector<int> postorder;
vector<vector<int> > adj;
vector<vector<int> > rev_adj;
vector<int> num;

void Explore(int v)
{
    visited[v]=true;
    int i;
    for(i=0; i<adj[v].size(); i++)
    {
        if(visited[adj[v][i]]==false)
            Explore(adj[v][i]);
    }
    num.push_back(v);
}

void DFS()
{
    int v;
    for(v=0; v<adj.size(); v++)
    {
        if(visited[v]==false)
        {
            Explore(v);
        }
    }
}

void Explore_rev(int v)
{
    rev_visited[v]=true;
    int i;
    for(i=0; i<rev_adj[v].size(); i++)
    {
        if(rev_visited[rev_adj[v][i]]==false)
            Explore_rev(rev_adj[v][i]);
    }
}

int number_of_strongly_connected_components() {
    int result = 0;
    DFS();
    int v;
    for(v=num.size()-1; v>=0; v--)
    {
        if(rev_visited[num[v]]==false)
        {
            Explore_rev(num[v]);
            result++;
        }
    }
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    visited.resize(n, false);
    rev_visited.resize(n, false);
    postorder.resize(n);
    adj.resize(n);
    rev_adj.resize(n);
    num.resize(n);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        rev_adj[y-1].push_back(x-1);
    }
    std::cout << number_of_strongly_connected_components();
}
