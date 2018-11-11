#include <limits.h>
#include <vector>
#include <iostream>
#include "dijkstra.h"
using namespace std;

extern struct vertex;

void dijkstras(vector< vertex > vertices, int *parents, int src) {
	int numNodes=vertices.size();
	int dist[numNodes];
	dist[src]=0;
	vector <int> q;
	int v,minIndex;

	for(v=0;v<numNodes;v++){
		if(v!=src){
			dist[v]=INT_MAX;
		}
		q.push_back(v);
	}

	while(!q.empty()){
		v=q[0];
		for(int i=1; i<q.size(); i++){
			if(dist[q[i]]<dist[v]){
				v=q[i];
				minIndex=i;
			}
		}
		q.erase(q.begin()+minIndex);

		vertex current=vertices[v];
		for(auto elem : current.edges) {
			int u=elem.first;
			int weight=elem.second;

			int alt = dist[v]+weight;
			if(alt < dist[u]){
				dist[u] = alt;
				parents[u]=v;
			}
		}
	}
	for(int i=0;i<numNodes;i++){
		cout<<i<<":"<<dist[i]<<"\n";
	}

}