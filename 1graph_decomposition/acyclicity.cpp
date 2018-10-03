//
//  main.cpp
//  acyclicity
//
//  Created by xiaonizi on 2018/2/2.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int> > adj;
int res=0;
stack<int> mark;

bool is_finish()
{
    int i;
    for(i=0; i<adj.size(); i++)
    {
        if(!adj[i].empty())
            return false;
    }
    return true;
}

void del(int i)
{
    mark.pop();
    if(!adj[i].empty())
    {
        if(!mark.empty())
            del(mark.top());
        else
            res=1;
        return;
    }
    for(int j=0; j<adj.size(); j++)
    {
        for(int k=0; k<adj[j].size(); k++)
        {
            if(adj[j][k]==i)
            {
                mark.push(j);
                adj[j].erase(adj[j].begin()+k);
                break;
            }
        }
    }
    if(is_finish())
    {
        return;
    }
    if(!mark.empty())
        del(mark.top());
    else
        res=1;
    return;
}

int acyclic()
{
    int i;
    for(i=0; i<adj.size(); i++)
    {
        if(adj[i].empty())
            mark.push(i);
    }
    if(mark.empty())
    {
        res=1;
        return res;
    }
    del(mark.top());
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    adj.resize(n);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic();
}

