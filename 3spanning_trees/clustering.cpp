//
//  main.cpp
//  clustering
//
//  Created by xiaonizi on 2018/2/9.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

struct vertex
{
    int x;
    int y;
    int rank;
};

struct edge
{
    int u_num;
    int v_num;
    double len;
};

vector<vertex> Vex;
vector<edge> Edge;

void add_edge()
{
    int i, j;
    double len;
    for(i=0; i<Vex.size()-1; i++)
        for(j=i+1; j<Vex.size(); j++)
        {
            len=sqrt(pow((Vex[i].x-Vex[j].x),2)+pow((Vex[i].y-Vex[j].y),2));
            Edge.push_back({i, j, len});
        }
    return;
}

int partition2(int l, int r) {
    double x = Edge[l].len;
    int j = l;
    for (int i = l + 1; i <= r; i++)
    {
        if (Edge[i].len <= x)
        {
            j++;
            swap(Edge[i], Edge[j]);
        }
    }
    swap(Edge[l], Edge[j]);
    return j;
}

void quick_sort (int l, int r)
{
    if (l >= r)
        return;
    int m = partition2(l, r);
    quick_sort (l, m - 1);
    quick_sort (m + 1, r);
}

void Union(int u, int v)
{
    int min, max, i;
    if(Vex[u].rank >= Vex[v].rank)
    {
        min=Vex[v].rank;
        max=Vex[u].rank;
    }
    else
    {
        max=Vex[v].rank;
        min=Vex[u].rank;
    }
    for(i=0; i<Vex.size(); i++)
        if(Vex[i].rank==max)
            Vex[i].rank=min;
    return;
}

double clustering(int k)
{
    int times=0;
    int i, j, m;
    add_edge();
    quick_sort(0, Edge.size()-1);
    if(Edge.size()==1)
        return Edge[0].len;
    for(i=0; i<Edge.size(); i++)
    {
        if(Vex[Edge[i].u_num].rank!=Vex[Edge[i].v_num].rank)
        {
            Union(Edge[i].u_num, Edge[i].v_num);
            times++;
            if(times==Vex.size()-k)
                break;
        }
    }
    for(j=i+1; j<Edge.size(); j++)
    {
        if(Vex[Edge[j].u_num].rank!=Vex[Edge[j].v_num].rank)
        {
            return Edge[j].len;
        }
    }
    return 0;
}

int main() {
    size_t n;
    int k;
    cin >> n;
    Vex.resize(n);
    for(int i=0; i<n; i++)
    {
        Vex[i].rank=i;
    }
    for (size_t i = 0; i < n; i++)
    {
        cin >> Vex[i].x >> Vex[i].y;
    }
    cin >> k;
    cout << std::setprecision(10) << clustering(k) << std::endl;
}
