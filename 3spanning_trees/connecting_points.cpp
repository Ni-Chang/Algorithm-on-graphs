//
//  main.cpp
//  connecting_points
//
//  Created by xiaonizi on 2018/2/9.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <iomanip>
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

void randomized_quick_sort (int l, int r)
{
    if (l >= r)
        return;
    int m = partition2(l, r);
    randomized_quick_sort (l, m - 1);
    randomized_quick_sort (m + 1, r);
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

double minimum_distance()
{
    double result = 0.;
    add_edge();
    randomized_quick_sort(0, Edge.size()-1);
    for(int i=0; i<Edge.size(); i++)
    {
        if(Vex[Edge[i].u_num].rank!=Vex[Edge[i].v_num].rank)
        {
            result+=Edge[i].len;
            Union(Edge[i].u_num, Edge[i].v_num);
        }
    }
    return result;
}

int main()
{
    size_t n;
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
    cout << setprecision(10) << minimum_distance() << endl;
}

