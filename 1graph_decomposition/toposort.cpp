//
//  main.cpp
//  toposort
//
//  Created by xiaonizi on 2018/2/3.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

vector<int> order;

struct vertex
{
    int indegree;
    int ver_num;
    vector<int> link;
};

void topo_sort(vector<vertex> adj)
{
    int i, j, k;
    vertex p;
    stack<vertex> temp;

    for(i=0; i<adj.size(); i++)
    {
        if(adj[i].indegree==0)
            temp.push(adj[i]);
    }
    for(i=0; i<adj.size(); i++)
    {
        while(!temp.empty())
        {
            p=temp.top();
            order.push_back(p.ver_num);
            temp.pop();
            for(j=0; j<p.link.size(); j++)
            {
                k=p.link[j];
                adj[k].indegree--;
                if(adj[k].indegree==0)
                {
                    temp.push(adj[k]);
                }
            }
        }
    }
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;
    vector<vertex> adj(n);
    for(int i=0; i<n; i++)
    {
        adj[i].indegree=0;
        adj[i].ver_num=i;
    }
    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].link.push_back(y - 1);
        adj[y - 1].indegree++;
    }
    topo_sort(adj);
    for (size_t i = 0; i<order.size(); i++)
    {
        std::cout << order[i] + 1 << " ";
    }
}
