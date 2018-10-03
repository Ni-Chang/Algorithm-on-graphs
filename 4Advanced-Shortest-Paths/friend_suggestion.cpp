//
//  main.cpp
//  friend_suggestion
//
//  Created by xiaonizi on 2018/2/11.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

typedef vector<vector<vector<int>>> Adj;

typedef long long Len;

typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    vector<int> workset_;
    vector<bool> visited_;
    
public:
    Bidijkstra(int n, Adj adj, Adj cost)
    : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(n, false)
    { workset_.reserve(n); }
    
    void clear()
    {
        for (int i = 0; i < workset_.size(); ++i)
        {
            int v = workset_[i];
            distance_[0][v] = INFINITY;
            distance_[1][v] = INFINITY;
            visited_[v] = false;
        }
        workset_.clear();
    }
    
    void Relax(int u, int v_num, int side, Queue& q)
    {
        int v=adj_[side][u][v_num];
        if(distance_[side][v]>distance_[side][u]+cost_[side][u][v_num])
        {
            distance_[side][v]=distance_[side][u]+cost_[side][u][v_num];
            q[side].push(make_pair(distance_[side][v], v));
            visited_[v]=true;
            workset_.push_back(v);
        }
    }
    
    void Process(pair<Len, int> u, int side, Queue& q)
    {
        int i;
        for(i=0; i<adj_[side][u.second].size(); i++)
        {
            Relax(u.second, i, side, q);
        }
        workset_.push_back(u.second);
        visited_[u.second]=true;
    }
    
    void visit(Queue& q, int side, int v, Len dist)
    {
        q[side].push(make_pair(dist, v));
        distance_[side][v]=dist;
    }
    
    Len query(int s, int t)
    {
        clear();
        Queue q(2);
        visit(q, 0, s, 0);
        visit(q, 1, t, 0);
        while(!(q[0].empty()&&q[1].empty()))
        {
            if(!q[0].empty())
            {
                
                pair<Len, int> u=q[0].top();
                q[0].pop();
                if(visited_[u.second])
                {
                    Process(u, 0, q);
                    return distance_[0][u.second]+distance_[1][u.second];
                }
                Process(u, 0, q);
            }
            if(!q[1].empty())
            {
                pair<Len, int> v=q[1].top();
                q[1].pop();
                if(visited_[v.second])
                {
                    Process(v, 1, q);
                    return distance_[0][v.second]+distance_[1][v.second];
                }
                Process(v, 1, q);
                
            }
        }
        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }
    
    Bidijkstra bidij(n, adj, cost);
    
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", bidij.query(u-1, v-1));
    }
}

