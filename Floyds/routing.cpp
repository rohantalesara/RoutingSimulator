#include <iostream>
#include <vector>
#include <map>
#include <limits.h>

using namespace std;

struct vertex {
  int no_of_edges;
  map<int, int> edges;  //from, cost
};

auto read_graph() {
    int N;
    int i, j, temp;
    cin >> N;
    vector< vector< int> > graph(N, vector< int >(N, -1));
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++){
            cin >> temp;
            if(temp != -1)  graph[i][j] = temp;
        }
    }
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) cout << graph[i][j] << " ";
        cout << endl;
    }
  return graph;
}
//works on adjacency list
//modifies edge between two vertices, it no edge make a new edge
auto modify_edge(vector< vertex > vertices, int src, int dst, int cost, int N) {
  if( (src < 0 && src >= N) || (dst < 0 && dst >= N) )return 0;
  auto it = (vertices[src].edges).find(dst);
  if(it == (vertices[src].edges).end()) { //no edge from src to dst
    (vertices[src].edges)[dst] = cost;
  }
  else {
    it->second = cost;
  }
  return 1;
}
//works on adjacency list
//delete edge
auto delete_edge(vector< vertex > vertices, int src, int dst, int N) {
  auto it = (vertices[src].edges).find(dst);
  if(it == (vertices[src].edges).end()) return 0;
  (vertices[src].edges).erase(it);
}

auto read_adj_list() {
  int N;
  int i, j;
  int vertex_index, no_of_edges;
  cin >> N;
  int dest, cost;
  vector< vertex > vertices(N);
  vertex *vert;
  for(i = 0; i < N; i++) {
    vert = new vertex();
    cin >> vertex_index >> no_of_edges;
    vert->no_of_edges = no_of_edges;
    for(j = 0; j < no_of_edges; j++) {
      cin >> dest >> cost;
      vert->edges[dest] = cost;
    }
    vertices[vertex_index] = *vert;
  }
  return vertices;
}

void bellman_ford(vector< vertex > vertices, int src) {

  int distances[vertices.size()]; //make it into a part of global routing table or not
  int shortest_hop[vertices.size()];
  for (int i = 0; i < vertices.size(); i++) 
      distances[i]   = INT_MAX;
  distances[src] = 0;
  for (int i = 1; i < vertices.size(); i++) 
  { 
    for(int j = 0; j <  vertices.size(); j++) {
      for(auto elem : vertices[j].edges) {
        int u = j; 
        int v = elem.first; 
        int weight = elem.second; 
        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) 
          distances[v] = distances[u] + weight;
          shortest_hop[u] = j;
      }
    }
  }
  cout << "weights" << endl;
  for(int j = 0; j < vertices.size(); j++) {
    cout <<distances[j] << " " << shortest_hop[j] << endl;
  }
}

int** make_matrix(vector<vertex> vertices)
{
  int n = vertices.size();
  int i, j;
  int **Matrix=(int**)malloc(sizeof(int*)*n);
  
  for(i=0;i<n;i++)
    Matrix[i]=(int*)malloc(sizeof(int)*n);

  for(i=0; i<n; i++)
  {
    for(j=0; j<n; j++)
    {
      if(i == j)
        Matrix[i][j] = 0;
      else
        Matrix[i][j] = -1;
    }
  }
  for(i=0; i<n; i++)
  {
    for(auto e : vertices[i].edges)
    {
      Matrix[i][e.first] = e.second;
    }
    //Matrix[i][vertices[i].edges.first] = vertices[i].edges.second;
  }
  for(i=0; i<n; i++)
  {
    for(j=0; j<n; j++)
    {
      if(Matrix[i][j] == -1)
        Matrix[i][j] = INT_MAX/2-1;
      cout << Matrix[i][j] << " ";
    }
    cout << endl;
  }
  return Matrix;

}

int** init_parent(int n, int** Graph)
{
  int i, j;
  int **parent=(int**)malloc(sizeof(int*)*n);
  
  for(i=0;i<n;i++)
    parent[i]=(int*)malloc(sizeof(int)*n);

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
    {
      if(Graph[i][j]!=(INT_MAX/2-1) && Graph[i][j] != 0)
      {
        parent[i][j] = i;
      }
      else
      {
        parent[i][j] = -1;
      }
    }
    return parent;
}

void display(int** Matrix, int n)
{
  int i, j;
  for(i=0; i<n; i++)
  {
    for(j=0; j<n; j++)
    {
      cout << Matrix[i][j] << " ";
    }
    
    cout << endl;
  }
  cout << endl;
}

int** create_next_hop(int n, int** parent)
{
  int i, j;
  int **next_hop=(int**)malloc(sizeof(int*)*n);
  
  for(i=0;i<n;i++)
    next_hop[i]=(int*)malloc(sizeof(int)*n);

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      next_hop[i][j] = parent[j][i];
  return next_hop;
}

int** Floyd_Warshall(vector<vertex> vertices)
{
  int** Graph = make_matrix(vertices);
  int i, j, k, n = vertices.size();
  int** parent = init_parent(n, Graph);
  for(k=0; k<n; k++)
  {
   // cout << "k: " << k << endl;
    for(i=0; i<n; i++)
    {
      for(j=0; j<n; j++)
      {
        /*if(Graph[i][j] < (Graph[i][k] + Graph[k][j]))
        {
          if(Graph[i][j] != (INT_MAX/2-1) && i!=j)
          {
           // display(parent, n);
          }
        }
        else*/ if(Graph[i][j] > (Graph[i][k] + Graph[k][j]))

        {
          Graph[i][j] = Graph[i][k] + Graph[k][j];
          parent[i][j] = parent[k][j];
        //  trial_hop[i][j] = trial_hop[j][k];
        //  display(parent, n);
        //  display(3);

        }
      }

    }
  //  display(Graph, n);
  }
  cout << "Floyd Graph:\n";
      display(Graph, n);

  int** next_hop = create_next_hop(n, parent);
  return next_hop;
}

int dijkstras(vector< vertex > vertices, vector<int> *srcchildren, vector<int> *vestiges, int parents[], int children[], int src) {
  int numNodes=vertices.size();
  int dist[numNodes];
  dist[src]=0;
  vector <int> q;
  int v,minv,minvIndex;

  for(v=0;v<numNodes;v++){
    if(v!=src){
      dist[v]=INT_MAX;
    }
    q.push_back(v);
  }
  int cnt=numNodes;
  int lastvertexVisited=-1;
  int numvisited=0;

  while(!q.empty()){
    minv=q[0];
    minvIndex=0;
    for(int i=1; i<q.size(); i++){
      if(dist[q[i]]<dist[minv]){
        minv=q[i];
        minvIndex=i;
      }
    }
    numvisited++;

    if(lastvertexVisited!=-1){
      if(parents[minv]==src){
        (*srcchildren).push_back(minv);
        if(numvisited>2){
          (*vestiges).push_back(lastvertexVisited);
        }
      }
      else{
        children[lastvertexVisited]=minv;
      }
    }

    cout<<"\nMin cost vertex="<<minv<<"\n";
    q.erase(q.begin()+minvIndex);

    vertex current=vertices[minv];
    for(auto elem : current.edges) {
      int u=elem.first;
      int weight=elem.second;
      cout<<"\nneighbour "<<u<<" weight="<<weight;
      int alt = dist[minv]+weight;
      if(alt < dist[u]){
        cout<<"\nchanging cost of "<<u<<" from "<<dist[u]<<" to "<<alt<<"\n";
        dist[u] = alt;
        parents[u]=minv;
      }
    }
    lastvertexVisited=minv;
  }

  /*
  for(int i=0;i<numNodes;i++){
    cout<<i<<":"<<dist[i]<<"\n";
  }
  */

  (*vestiges).push_back(minv);
  //return minv;  //return the farthest node from src
}

int** makeroutingtable(int numnodes, int parents[], int children[], int src, vector <int> srcchildren, vector <int> vestiges){
  int i, farthest;
  int **routingtable=(int**)malloc(sizeof(int*)*numnodes);
  
  for(i=0;i<numnodes;i++){
    routingtable[i]=(int*)malloc(sizeof(int)*numnodes);
  }

  for(i=0; i<srcchildren.size(); i++){
    children[src]=srcchildren[i];
    farthest=vestiges[i];

    int rowhop,desthop,row=src, dest;
    while(row!=farthest){
      dest=farthest;
      rowhop=children[row];

      while(dest!=row){
        desthop=parents[dest];
        //cout<<"\nrow="<<row<<"  dest="<<dest<<"\n";
        routingtable[row][dest]=rowhop;
        routingtable[dest][row]=desthop;
        dest=desthop;
      }
      row=rowhop;
    }
  }
  return routingtable;
}

int main() 
{
  auto vertices = read_adj_list();
  for(auto v:vertices)
  {
    for(auto e:v.edges)
      cout << e.first << " " << e.second << endl;
    cout << endl;
  }
  int numnodes=vertices.size();
  int ** next_hop = Floyd_Warshall(vertices);
  int i, j;
  cout << "Next Hop: \n";
  for(i=0; i<numnodes; i++)
  {
    for(j=0; j<numnodes; j++)
      cout << next_hop[i][j] << " ";
    cout << endl;
  }
  /*int src=0;
  int parents[numnodes];
  int children[numnodes];
  vector<int> srcchildren;
  vector<int> vestiges;

  dijkstras(vertices, &srcchildren, &vestiges, parents, children, src);
  
  cout<<"\nParents\n";
  for(int i=1;i<numnodes;i++){
    cout<<i<<" parent="<<parents[i]<<"\n";
  }

  cout<<"\nChildren\n";
  for(int i=0;i<numnodes-1;i++){
    cout<<i<<" child="<<children[i]<<"\n";
  }
  
  cout<<"\nSource Children\n";
  for(int i=0;i<srcchildren.size();i++){
    cout<<i<<" child="<<srcchildren[i]<<"\n";
  }

  cout<<"\nVestiges\n";
  for(int i=0;i<vestiges.size();i++){
    cout<<i<<" child="<<vestiges[i]<<"\n";
  }

  int **routingtable=makeroutingtable(numnodes,parents,children,src, srcchildren, vestiges);
  
  for(int i=0;i<numnodes;i++){
    for(int j=0;j<numnodes;j++){
      if(i==j){
        cout<<" -";
        continue;
      }
      cout<<" "<<routingtable[i][j];
    }
    cout<<"\n";
  }

  //cout << vertices[3].no_of_edges << endl;
  /*
  int N;
  int i, j;
  int vertex_index, no_of_edges;
  cin >> N;
  int dest, cost;
  vector< vertex > vertices;
  vertex *vert;
  for(i = 0; i < N; i++) {
    vert = new vertex();
    cin >> vertex_index >> no_of_edges;
    vert->no_of_edges = no_of_edges;
    for(j = 0; j < no_of_edges; j++) {
      cin >> dest >> cost;
      vert->edges[dest] = cost;
    }
    vertices.push_back(*vert);
  }
  */
  //bellman_ford(vertices, 1);
  // int src = 0;
  // int dist[vertices.size()]; 
  
  //   for (int i = 0; i < vertices.size(); i++) 
  //       dist[i]   = INT_MAX;
  //   dist[src] = 0; 
  //   for (int i = 1; i < vertices.size(); i++) 
  //   { 
  //     for(int j = 0; j <  vertices.size(); j++) {
  //       for(auto elem : vertices[j].edges) {
  //         int u = j; 
  //         int v = elem.first; 
  //         int weight = elem.second; 
  //         if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
  //           dist[v] = dist[u] + weight;
  //       }
  //     }
  //   }
  //   cout << "weights" << endl;
  //   for(int j = 0; j < vertices.size(); j++) {
  //     cout <<dist[j] << endl;
  //   }
  return 0;
}