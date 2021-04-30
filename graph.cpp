//----------------------------------------------------------------------
// Carter Mooring
// HW9
// graph.cpp
// April 29th, 2021
// Dr. Bowers, CPSC450
//----------------------------------------------------------------------

#include "graph.h"
#include <queue>
#include <stack>
#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

// shortened hash-table map name for convenience
typedef std::unordered_map<int,int> Map;
typedef std::set<int> Set;

//----------------------------------------------------------------------
// HW-3 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Breadth-first search from a given source vertex. 
//
// Inputs: 
//   dir -- true if directed
//   src -- the source vertex
// Outputs:
//   tree -- search tree that maps vertices found during bfs from the
//           source to their parent vertices
//----------------------------------------------------------------------
void Graph::bfs(bool dir, int src, Map& tree) const{
    bool discovered[vertex_count()];  // make a list the size of the vertex count
  
    // fill the list with false as the preset
    for(int i = 0; i < vertex_count(); i++) {
        discovered[i] = false;
    }

    // Deal with the head node
    discovered[src] = true;
    tree[src] = -1;

    // Make a queue and place the header in
    queue<int> q;
    q.push(src);

    // While the q is not empty
    while(!q.empty()) {
        int node = q.front(); // grabs the node (u) at the front of the queue
        q.pop(); // pop to remove from queue since we have it stored

        // check if the graph is directed and populate a list accordingly
        list<int> vertices;
        if(dir){
            connected_to(node, vertices); // directed
        } else {
            adjacent(node, vertices); // undirected
        }

        // for child (v) of the node in the list of adjacent vertices
        for(int const& child : vertices){
            // if we have not discovered the current child
            if(!discovered[child]) {
                // set to discovered
                discovered[child] = true;
                tree[child] = node;
                q.push(child);
            }
        }
    }
}

//----------------------------------------------------------------------
// Shortest path length from source to destination vertices.
//
// Conditions:
//   The source and destination vertices must be unique.  
// Inputs:
//   dir -- true if directed
//   src -- the vertex starting the path
//   dst -- the vertex ending the path
// Outputs:
//   path -- sequence of nodes that define the shortest path
//----------------------------------------------------------------------
void Graph::shortest_path_length(bool dir, int src, int dst, std::list<int>& path) const{
    Map imTheMap; //imTheMap imTheMap imTheMap, imTheMap
    bfs(dir,src,imTheMap);

    // if none
    if(imTheMap.count(dst) == 0) {
        path.push_back(src);
        return;
    }

    int curr = dst;
    // while not the last vertex
    while(curr != -1) {
        path.push_front(curr);
        curr = imTheMap[curr];
    }
}

//----------------------------------------------------------------------
// Find connected components based on breadth-first search.
//
// Conditions:
//   Finds strongly connected components in an undirected graph and
//   weakly-connected components in a directed graph.
// Inputs:
//   None
// Outputs: 
//   components -- mapping from each graph vertex to its corresponding
//                 component number where component numbers range from
//                 0 to c-1 (for c components)
//----------------------------------------------------------------------
void Graph::bfs_connected_components(Map& components) const{
    bool discovered[vertex_count()];

    // populate the array with false values
    for(int i = 0; i < vertex_count(); i++){
        discovered[i] = false;
    }

    int component_count = 0;
    bool allDiscovered;

    // for each vertex
    for(int i = 0; i < vertex_count(); i++)
        if(!discovered[i]){
            allDiscovered = false;
        }else{
            allDiscovered = true;
        }

    // while they are not all discovered
    while(!allDiscovered) {
        int src;

        // get next undiscovered index
        for(int i = 0; i < vertex_count(); i++){
            // if undiscovered focus on that position
            if(!discovered[i]) { 
                src = i; 
                break; 
            }
        }

        // make and populate a tree
        Map tree;
        bfs(false, src, tree);

        // for each value in the tree
        for(auto val : tree) {
            if(!discovered[val.first]) {
            components[val.first] = component_count;
            discovered[val.first] = true;
            }
        }
        component_count++;  //increase the component count
    }
}

//----------------------------------------------------------------------
// Determine if the graph is bipartite (i.e., 2-colorable)
//
// Inputs:
//   None
// Outputs:
//   returns  -- true if the graph is bipartite, false otherwise
//   coloring -- mapping from each graph vertex to its corresponding
//               color (either 0 or 1) if graph is bipartite
//----------------------------------------------------------------------
bool Graph::bipartite_graph(Map& coloring) const{
    int color[vertex_count()];

    // for each vertex, populate a array with base color
    for(int i = 0; i < vertex_count(); i++){
        color[i] = -1;
    }

    // color the first position 0 
    color[0] = 0;
    coloring[0] = 0;

    // create a queue
    queue<int> q;
    q.push(0);

    // while the queue is not empty
    while(!q.empty()) {
        int head = q.front();
        q.pop();

        // create a list of the vertecies adjacent to the current one
        list<int> vertices;
        adjacent(head, vertices);

        // for each adjacent vertice
        for(int const& v : vertices){
            // if vertex is uncolored
            if(color[v] == -1) {
            // check the head nodes color and color current adj vertex accordingly
            if(color[head] == 0) {
                color[v] = 1;
                coloring[v] = 1;
            }else {
                color[v] = 0;
                coloring[v] = 0;
            }
                q.push(v);
            }else if(color[v] == color[head]){
            // else if it is colored make sure its not the same as the head, otherwise non bipartite
                return false;
            }
        }

        // if the queue is empty
        if(q.empty()) {
            // for each vertex
            for(int i = 0; i < vertex_count(); i++){
            // find the coloring at that position, if it is the end then push
                if(coloring.find(i) == coloring.end()) {
                q.push(i);
                break;
                }
            }
        }
    }
    return true;
}


//----------------------------------------------------------------------
// HW-4 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Depth-first search from a given source vertex.
//
// Inputs: 
//   dir -- if true assumes graph is directed
//   src -- the source vertex
// Outputs:
//   tree -- search tree that maps vertices found during dfs to their
//           corresponding parent vertex.
//----------------------------------------------------------------------
void Graph::dfs(bool dir, int src, Map& tree) const{
    bool discovered[vertex_count()];
    // for each vertex set the discovered array position to false
    for(int i = 0; i < vertex_count(); i++){
        discovered[i] = false;
    }

    tree[src] = -1;
    // create a stack
    stack<int> s;
    s.push(src);

    // while the stack is not empty
    while(!s.empty()) {
        int head = s.top();
        // if the node has not been discovered
        if(!discovered[head]) {
            // set to discovered and create a list of adj/connected vertices
            discovered[head] = true;
            list<int> vertices;
            if(dir){
            connected_to(head, vertices);
            }else{
            adjacent(head, vertices);
            }

            // for each adj/connected vertice
            for(int const& v : vertices) {
            if(!discovered[v]) {
                tree[v] = head;
                s.push(v); // push to the stack
            }
            }
        }else{
            s.pop();
        }
    }
}

//----------------------------------------------------------------------
// Determine if the graph is acyclic or not.
//
// Inputs:
//   dir -- if true assumes graph is directed
// Outputs:
//   returns -- true if acyclic
//----------------------------------------------------------------------
bool Graph::acyclic(bool dir) const{
  int coloring[vertex_count()];
  // for each vertices, populate a coloring array with no color
  for(int i = 0; i < vertex_count(); i++){
      coloring[i] = -1;
  }

  //create a stack and tree
  Map tree;
  stack<int> s;

  // for each vertex
  for(int j = 0; j < vertex_count(); j++) {
      // if uncolored push to stack
      if(coloring[j] == -1){
          s.push(j);
      }

      // while the stack is not empty
      while(!s.empty()) {
          int head = s.top();
          // if the coloring is not 0
          if(coloring[head] != 0) {
              coloring[head] = 0; // set to 0
              
              //get a list of adj/connected vertices
              list<int> vertices;
              if(dir){
                  // directed
                  connected_to(head, vertices);
              }else{
                  // undirected
                  adjacent(head, vertices);
              }

              // for each adj/connected vertice
              for(int const& v : vertices) {
                  // check if uncolored
                  if(coloring[v] == -1) {
                    tree[v] = head;
                    s.push(v);
                  } else if(coloring[v] == 0 && (dir || tree[head] != v)){
                    // else same color
                    
                    return false;
                  }
              }
          } else { 
              // else set color to 1 and pop from stack
              s.pop(); 
              coloring[head] = 1; 
          }
      }
  }
  return true;
}

//----------------------------------------------------------------------
// Naive implementation to compute the transitive closure of the
// current graph without consideration of edge weights.
//
// Conditions: Assumes that the given graph (the closed_graph) is a
//             copy of the current graph prior to the call.
// 
// Inputs:
//   dir -- if true assumes graph is directed
// Outputs:
//   closed_graph -- the transitively closed graph, where added
//                   edges have
//----------------------------------------------------------------------
void Graph::unweighted_transitive_closure(bool dir, Graph& closed_graph) const{
    // for each vertex
    for(int j = 0; j < vertex_count(); j++) {
        bool discovered[vertex_count()];

        // populate a discovered array with false values
        for(int i = 0; i < vertex_count(); i++){
            discovered[i] = false;
        }
        // create a tree
        Map tree;
        tree[j] = -1;

        // create a stack
        stack<int> s;
        s.push(j);

        // while hte stack is not empty
        while(!s.empty()) {
            int head = s.top();

            // if it has not been discovered yet
            if(!discovered[head]) {
                discovered[head] = true;
                list<int> vertices;

                // get a list of adj/connected vertices
                if(dir){
                    connected_to(head, vertices);
                }else{
                    adjacent(head, vertices);
                }

                // for each adj/connected vertice
                for(int const& v : vertices) {
                    // if undiscovered
                    if(!discovered[v]) {
                        tree[v] = head;
                        s.push(v);
                    }
                }
            } else {
                s.pop();
            }
        }
        // for each value in the tree
        for(auto val : tree){
            if(val.second != -1){
                closed_graph.set_edge(j, 0, val.first);
            }
        }
    }
}

//----------------------------------------------------------------------
// Computes a topological sort of the current graph based on dfs.
//
// Conditions: Assumes the graph is directed.
//
// Inputs:
//   none
// Outputs:
//   vertex_ordering -- a map from vertex to it's corresponding
//                      order in the topological sort (where nodes
//                      are ordered from 1 to n)
//----------------------------------------------------------------------
void Graph::dfs_topological_sort(Map& vertex_ordering) const{
    int index = 1;
  bool discovered[vertex_count()];

  // for each vertex populate a array position with undiscovered
  for(int i = 0; i < vertex_count(); i++){
    discovered[i] = false;
  }

  // createa a stac
  stack<int> s;

  // for each vertex
  for(int i = 0; i < vertex_count(); i++) {
    // if undiscovered
    if(!discovered[i]){
      s.push(i);
    } 

    // while stack is not empty
    while(!s.empty()) {
      int head = s.top();

      // if undiscovered
      if(!discovered[head]) {
        bool vertexAdd = true;
        list<int> vertices;
        connected_from(head, vertices);

        // for each connected vertice
        for(int const& v : vertices) {
          // if undiscovered
          if(!discovered[v]) {
            vertexAdd = false;
            s.push(v);
          }
        }

        // if another vertex should be added
        if(vertexAdd) {
          // add the vertex
          vertex_ordering[head] = index;
          index++;
          discovered[head] = true;
        }
      }else{
        s.pop();
      }
    }
  }
}


//----------------------------------------------------------------------
// HW-5 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Helper function to caluclate the max index
//----------------------------------------------------------------------
int getMax(int prev, int vals[], int size) {
  // if previous is unset
  if(prev == -1) {
    int maxIndex = 0;
    // for val in size
    for(int i = 0; i < size; i++) {
      // if val is > current max val
      if(vals[i] > vals[maxIndex]){
	      maxIndex = i;
      }
    }
    return maxIndex;
  }else{
    int max = -1;
    int maxIndex;
    // for val in size
    for(int i = 0; i < size; i++) {
      // if less then prev but > max
      if(vals[i] < vals[prev] && vals[i] > max) {
        maxIndex = i;
        max = vals[i];
      }
    }
    return maxIndex;
  }
}

//----------------------------------------------------------------------
// Computes the strongly connected components.
//
// Inputs:
//   none
// Outputs: 
//   components -- mapping from each graph vertex to its corresponding
//                 component number where component numbers range from
//                 0 to c-1 (for c components)
//----------------------------------------------------------------------
void Graph::strongly_connected_components(Map& components) const {
  int clock = 0;
  bool discovered[vertex_count()];
  // for each vertex populate a discovered array with false
  for(int i = 0; i < vertex_count(); i++){
     discovered[i] = false;
  }
  int pre[vertex_count()];
  // for each vertex populate a pre array with -1
  for(int i = 0; i < vertex_count(); i++){ 
    pre[i] = -1;
  }
  int post[vertex_count()];
  // for each vertex populate a post array with -1
  for(int i = 0; i < vertex_count(); i++){
    post[i] = -1;
  }

  // create a tree and stack
  Map tree;
  stack<int> s;
  s.push(0);

  // for each vertex
  for(int i = 0; i < vertex_count(); i++) {
    // if undiscovered
    if(!discovered[i]) {
      tree[i] = -1;
      s.push(i);

      // while the stack is empty
      while(!s.empty()) {
        int head = s.top();
        // if undiscovered
        if(!discovered[head]) {
          // check if pre is unset
          if(pre[head] == -1) {
            // set to clock value
            pre[head] = clock;
            clock++;
          }

          // set as discovered and make a list of connected vertices
          discovered[head] = true;
          list<int> vertices;
          connected_from(head, vertices);

          // for each connected component 
          for(int const& v : vertices) {
            // check if discovered
            if(!discovered[v]) {
              tree[v] = head;
              s.push(v);
            }
          }
        } else {
          // check if post value is unset
          if(post[s.top()] == -1) {
            post[s.top()] = clock;
            clock++;
          }
          s.pop();
        }
      }
    }
  }
  
  // reset discovered array
  for(int i = 0; i < vertex_count(); i++){
    discovered[i] = false;
  }

  int last_max = -1;
  int count = 0;
  
  // for each vertex
  for(int j = 0; j < vertex_count(); j++) {
    // get the max position
    int maxIndex = getMax(last_max, post, vertex_count());
    last_max = maxIndex;
    Map curr_tree;

    // if the maxs index is undiscovered
    if(!discovered[maxIndex]) {
      curr_tree[maxIndex] = -1;
      s.push(maxIndex);

      // while the stack is not empty
      while(!s.empty()) {
        int head = s.top();
        // if undiscovered
        if(!discovered[head]) {
          // grab all connected vertices
          discovered[head] = true;
          list<int> vertices;
          connected_to(head, vertices);

          // for each connected vertice
          for(int const& v : vertices) {
            // if undiscovered
            if(!discovered[v]) {
              curr_tree[v] = head;
              s.push(v);
            }
          }
        } else s.pop();
      }
    }
    // if the tree is not empty
    if(curr_tree.size() > 0) {
      // for each value in the tree
      for(auto index : curr_tree) {
	      components[index.first] = count;
      }
      count++;
    }
  }
}

//----------------------------------------------------------------------
// Computes the transitive reduction.
//
// Conditions: Assumes that the given graph (the closed_graph) has
//             the same number of nodes as the current graph. But
//             does not have any edges prior to the call
//
// Inputs:
//   none
// Outputs:
//   reduced_graph -- the reduced edges are added to the reduced graph
//----------------------------------------------------------------------
void Graph::transitive_reduction(Graph& reduced_graph) const{
  Map components;
  int componentsCount = 0;
  // get the strongly connected components
  strongly_connected_components(components);

  // for each vertice
  for(int i = 0; i < vertex_count(); i++){
    // check if
    if(components[i] > componentsCount)
        componentsCount = components[i];
  }

  // create a vector to hold the groups of components
  vector<int> component_groups[componentsCount + 1];

  // for each vertex
  for(int i = 0; i < vertex_count(); i++){
    // populate the compinent groups
    component_groups[components[i]].push_back(i);
  }

  // for the amount of components
  for(int i = 0; i < componentsCount+1; i++){
    // for the size of the component group
    for(int j = 0; j < component_groups[i].size()-1; j++){
        reduced_graph.set_edge(component_groups[i][j], 0, component_groups[i][j+1]);
    }
    // if the size is more than 1
    if(component_groups[i].size() > 1){
      reduced_graph.set_edge(component_groups[i][component_groups[i].size()-1], 0, component_groups[i][0]);
    }
  }
  
  // for the amount of components
  for(int i = 0; i < componentsCount+1; i++){
    // for the amount of components
    for(int j = 0; j < componentsCount+1; j++){
      if(i != j){
        Map tree;
        dfs(true, component_groups[i][0], tree);
        
        // if the coponent group is not the end
        if(tree.find(component_groups[j][0]) != tree.end()){
          tree.clear();
          reduced_graph.dfs(true, component_groups[i][0], tree);
          // // if the coponent group is not the end
          if(tree.find(component_groups[j][0]) == tree.end()){
            reduced_graph.set_edge(component_groups[i][0], 0, component_groups[j][0]);
          }
        }
      }
    }
  }

  // for the amount of components
  for(int i = 0; i < componentsCount+1; i++){
    // for the amount of components
    for(int j = 0; j < componentsCount+1; j++){
      // if the graph has the edge
      if(i != j && reduced_graph.has_edge(component_groups[i][0], component_groups[j][0])){
        reduced_graph.remove_edge(component_groups[i][0], component_groups[j][0]);
        Map tree;
        reduced_graph.dfs(true, component_groups[i][0], tree);
        // if the component is at the end
        if(tree.find(component_groups[j][0]) == tree.end()){
          reduced_graph.set_edge(component_groups[i][0], 0, component_groups[j][0]);
        }
      }
    }
  }
}

//----------------------------------------------------------------------
// Check if an eulerian exists in a directed graph, and if so,
// return one.
//
// Conditions: Assumes the graph is not disconnected.
//
// Inputs:
//   none
// Outputs:
//   path -- the path as an ordered list of vertices
//----------------------------------------------------------------------
bool Graph::directed_eulerian_path(std::list<int>& path) const{
    bool sourceFound = false;
  bool sinkFound = false;
  int source = -1;
  int sink = -1;
  
  // for each vertex
  for(int i = 0; i < vertex_count(); i++) {
    list<int> inEdge;
    list<int> outEdge;
    connected_from(i, inEdge);
    connected_to(i, outEdge);

    // if there is 1 for in edge then out edge
    if(inEdge.size() == outEdge.size()-1) {
      if(sourceFound){
        return false;
      }
      sourceFound = true;
      source = i;
    }else if(inEdge.size()-1 == outEdge.size()) {
      // else if there is 1 more out edge than in edge
      if(sinkFound){
        return false;
      }
      sinkFound = true;
      sink = i;
    } else if(inEdge.size() != outEdge.size()){
      return false;
    }
  }

  int edges[vertex_count()];
  // for each vertex
  for(int i = 0; i < vertex_count(); i++) {
    // store the amount of connected components
    list<int> temp;
    connected_to(i, temp);
    edges[i] = temp.size();
  }

  // create a stack
  stack<int> s;
  s.push(source);
  
  // while the stack is not empty
  while(!s.empty()) {
    int head = s.top();
    // if less than 1
    if(edges[head] < 1) {
      path.push_front(head);
      s.pop();
      continue;
    }

    // populate a list of conected components
    list<int> vertices;
    connected_to(head, vertices);

    // for coonected component
    for(int v : vertices) {
      edges[head]--;
      s.push(v);
    }    
  }

  // for value in the path
  for(auto val : path){
    return true;
  }
}


//----------------------------------------------------------------------
// HW-6 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Returns a Hamiltonian path if one exists in the current graph.
//
// Conditions: Treats the graph as directed.
//
// Outputs:
//   path -- the Hamiltonian path
//
// Returns:
//   true if a Hamiltonian path exists, false otherwise.
//----------------------------------------------------------------------
bool Graph::directed_hamiltonian_path(std::list<int>& path) const{
  // for each vertex in the path
  for(int i = 0; i < vertex_count(); i++) {
    bool discovered[vertex_count()]; // array to track if weve seen the vertex

    // set a second vertex matrix for each vertex in the path
    for(int j = 0; j < vertex_count(); j++) {
      discovered[j] = false;
    }

    path.clear();
    path.push_back(i);
    discovered[i] = true; // set current vertex index to true

    // return if its a directed hamilton path or not
    return directed_hamiltonian_rec(i, path, discovered);
  }
  return false;
}

//----------------------------------------------------------------------
// Find a maximum matched graph using the augmenting paths algorithm
// from the textbook.
//
// Conditions: Finds a matching only if the current graph is bipartite
//
// Output:
//   max_matched_graph -- A graph with same vertices as original
//                        graph, containing the edges in the
//                        matching. The output graph is assumed to
//                        be initialized with the same number of
//                        vertices, but without any edges.
// Returns:
//   true if the current graph is bipartite, false otherwise
//----------------------------------------------------------------------
bool Graph::bipartite_graph_matching(Graph& max_matched_graph) const{
  int track[vertex_count()];

  // for each vertex in the graph, populate an index
  for(int i = 0; i < vertex_count(); i++){
    track[i] = -1;
  }

  Map coloring;
  // if it isn't bipartite return false
  if(!bipartite_graph(coloring)){
    return false;
  }

  // create lists and a queue
  list<int> V;
  list<int> U;
  queue<int> q;

  // for vertex, color pair in the coloring Map
  for(auto vc : coloring){
    // check the vertex, color returned in color
    if(vc.second == 0){
      V.push_back(vc.first);
    }else{
      U.push_back(vc.first);
    } 
  }

  // for each vertice in the V list, push the vertex to the queue
  for(int v : V){
    q.push(v);
  }

  // while the q is not empty
  while(!q.empty()){
    // grab and pop the front vertex
    int curr_v = q.front(); 
    q.pop();
    bool match = false;

    for(int v : V){
      // check if matches any vertex in V list
      if(curr_v == v){
        match=true; 
        break;
      }
    }

    // matches any vertex in V list
    if(match){
      list<int> adj_v;
      adjacent(curr_v, adj_v); // populate a list of the adjacent vertexes

      // for each adjacent vertex in the list
      for(int adj_u : adj_v) {
        list<int> adj;
        max_matched_graph.adjacent(adj_u, adj); // populate a list with the adjacent vertexes, adjacent vertexes

        if(adj.size() == 0){
          max_matched_graph.set_edge(curr_v, 0, adj_u); // set the edge
          int v = curr_v;

          // TODO:
          while(track[v] != -1) {
            adj_u = track[v];
            max_matched_graph.remove_edge(v, adj_u);
            v = track[adj_u];
            max_matched_graph.set_edge(v, 0, adj_u);
          }

          // reset array
          for(int i = 0; i < vertex_count(); i++){
            track[i] = -1;
          }

          q = queue<int>();

          // for each Vertex in the list
          for(int v : V) {
            list<int> adj;
            max_matched_graph.adjacent(v, adj); // populate list of the adjacent vertexes

            // if empty list, add vertex to the queue
            if(adj.size() == 0){
              q.push(v);
            }
          } 
          break;

        } else { 
          // if adj_u does not have an edge with the current original current vertex                                                                                                                                                       	 
          if(!max_matched_graph.has_edge(curr_v, adj_u) && track[adj_u] == -1){
            track[adj_u] = curr_v;
            q.push(adj_u);
          }
        }
      }
    }else{ // curr_v in U (and matched)                                                                                                                                                    	 
      list<int> adj_v;
      max_matched_graph.adjacent(curr_v, adj_v);
      int v;

      // if there is only 1 adj vertex
      if(adj_v.size() == 1){
        v = adj_v.front();
      }

      track[v] = curr_v;
      q.push(v);
    }
  }
  return true;
}

//----------------------------------------------------------------------
// Finds all (maximal) cliques in the graph using the Bron-Kerbosch
// algorithm.
//
// Conditions: Assumes the graph is undirected.
//
// Output:
//   cliques -- a list of list of vertices denoting a maximal clique
//----------------------------------------------------------------------
void Graph::cliques(std::list<Set>& cliques) const{
  Set p;
  Set r;
  Set x;

  // for each vertex in the clique
  for(int i = 0; i < vertex_count(); i++){
    p.insert(i);
  }
  
  cliques_rec(p, r, x, cliques);
}
  
// helper function for directed hamiltonian recursive function
bool Graph::directed_hamiltonian_rec(int v, std::list<int>& path, bool discovered[]) const{
  // if the path is just the graph, then easy true
  if(path.size() == vertex_count()){
      return true;
  }

  list<int> vertices;
  vertices.clear();
  connected_to(v, vertices); // populate a list of the connected -> vertices

  // for each connected vertex
  for(auto const& vertex : vertices){
    // if not discovered, add to path and discover
    if(discovered[vertex] == false){
        discovered[vertex] = true;
        path.push_back(vertex);

      // recursion over DHR
      if (directed_hamiltonian_rec(vertex, path, discovered)) {
        return true;
      } else {
        path.remove(vertex);
      }
    }
  }
 return false;
}

// helper function for finding all cliques
void Graph::cliques_rec(Set& p, Set& r, Set& x, std::list<Set>& cliques) const{
  // if both p and z are empty
  if(p.size() == 0 && x.size() == 0) {
    cliques.push_back(r); // push r as a clique
    return;
  }

  Set p_copy = p;

  // for each vertex in p
  for(auto v : p) {
    // populate the adjacent vertex list
    list<int> adj_v; adjacent(v, adj_v);
    Set adj(adj_v.begin(), adj_v.end());

    // populate a temp list with an intersection
    list<int> temp;
    set_intersection(p_copy.begin(), p_copy.end(), adj.begin(), adj.end(), back_inserter(temp));
    Set newP(temp.begin(), temp.end());

    // set new r value to current vertex since a intersection
    Set newR = r;
    newR.insert(v);

    // populate a second temp list with an intersection
    list<int> temp2;
    set_intersection(x.begin(), x.end(), adj.begin(), adj.end(), back_inserter(temp2));
    Set newX(temp2.begin(), temp2.end());

    cliques_rec(newP, newR, newX, cliques);

    // erase the vertex and reset x
    p_copy.erase(v);
    x.insert(v);
  }
  return;

}

//----------------------------------------------------------------------
// HW-7 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Single-source shortest paths from the given source using
// Dijkstra's algorithm.
//
// Conditions: Assumes graph is directed and maximum weight is
//             numeric_limits<int>::max()
// 
// Input:
//  src -- the source vertex
//
// Output:
//  path_costs -- the minimum path cost from src to each vertex v
//                given as path_costs[v].
//----------------------------------------------------------------------
void Graph::dijkstra_shortest_path(int src, Map& path_costs) const{
  bool edgeFound = true; // checking if we found an edge
  int weight; 
  int minimumDist;
  int minV = -1;
  bool discovered[vertex_count()];

  // for each vertex...
  for(int i = 0; i < vertex_count(); i++){
    discovered[i] = false; // populate the array position with starter value false
    path_costs.emplace(i, -1); // set all distances to infinity
  }
  discovered[src] = true;
  path_costs[src] = 0; // set source distance/cost to 0 since we start there

  // while there is still an edge
  while(edgeFound){
    edgeFound = false;
    // 7. (u1, v1) <- such an edge minimizing dist(s, u) + w(u, v)
    // for each vertex
    for(int u = 0; u < vertex_count(); u++){
      // check if we have seen the current vertice before
      if(discovered[u]){ // if we have seen the vertex, every u prime needs to be in discovered
        // for each vertex
        for(int v = 0; v < vertex_count(); v++){
          // if the 2nd vertex has not been discovered, has an edge with the curr (u) vertex
          // and if the weight + path cost is less than the current minimum
          if(!discovered[v] && get_edge(u, v, weight) && (!edgeFound || weight + path_costs[u] < minimumDist)){
            minimumDist = weight + path_costs[u];
            edgeFound = true; // we have seen this vertex
            minV = v;
          }
        }
      }
    }
    if(edgeFound){
      // shortest path for this vertex is discovered, so set vertex and shortest path
      discovered[minV] = true;
      path_costs[minV] = minimumDist;
    }
  }
}

//----------------------------------------------------------------------
// Compute a minimum spanning tree using Prim's algorithm.
//
// Conditions: Assumes a connected, undirected graph. The spanning
//             tree is represented as a graph, which is initialized
//             with the same vertices as the current graph, but with
//             no edges (on input).
//
// Output:
//  spanning-tree -- A graph containing the minimum spanning tree
//                   edges.
//
//----------------------------------------------------------------------
void Graph::prim_min_spanning_tree(Graph& spanning_tree) const{
  bool moreUndiscovered = true;
  // populate an array with false for each vertex
  bool discovered[vertex_count()];
  for(int i = 0; i < vertex_count(); i++){
    discovered[i] = false;
  }
  discovered[0] = true;

  // while there are still undiscovered vertexs
  while(moreUndiscovered){
    int minWeight = numeric_limits<int>::max();
    int minU;
    int minV;
    int edgeWeight;

    // for each vertex
    for(int u = 0; u < vertex_count(); u++){
      // make sure it is discovered to check
      if(discovered[u]){
        // for each vertex
        for(int v = 0; v <vertex_count(); v++){
          // make sure it is not discovered to check
          if(!discovered[v]){
            // check if it has an edge with original vertex u 
            if(has_edge(u,v)){
              get_edge(u,v,edgeWeight); // get the edge
              // if the edge is less then we have a new shortest path
              if(edgeWeight < minWeight){
                minWeight = edgeWeight; // set the new minimum weight
                minU = u; // store min vertexes temporarily to set after loop
                minV = v;
              }
            }
          }
        }
      }
    }
    discovered[minV] = true; // set vertex as now discovered
    spanning_tree.set_edge(minU, minWeight, minV); // add to spanning tree

    // for each vertex, check if there are still undiscovered vertexes and continue if so
    for(int i = 0; i < vertex_count(); i++){
      if(!discovered[i]){
        moreUndiscovered = true;
        break;
      }else{
        moreUndiscovered = false;
      }
    }
  }
}

// Helper fucntion to sort by edge weights
void Graph::sortByEdgeWeight(vector<tuple<int,int,int>>& edges, int start, int end) const{
  // if the start vertex is >= the last vertex then just return, helps with recursion
  if(start >= end){
    return;
  }

  // implement a brief merge sort recursive
  int middle = start + (end-start)/2;
  sortByEdgeWeight(edges, start, middle);
  sortByEdgeWeight(edges, middle+1, end);
  merge(edges, start, middle, end);
}

//----------------------------------------------------------------------
// Compute a minimum spanning tree using Kruskal's algorithm.
//
// Conditions: Assumes a connected, undirected graph. The spanning
//             tree is represented as a graph, which is initialized
//             with the same vertices as the current graph, but with
//             no edges (on input).
//
// Output:
//  spanning-tree -- A graph containing the minimum spanning tree
//                   edges.
//
//----------------------------------------------------------------------
void Graph::kruskal_min_spanning_tree(Graph& spanning_tree) const{
  vector<tuple<int,int,int>> edges;
  // for each vertex
  for(int v = 0; v < vertex_count(); v++){
    // for each vertex
	  for(int u = 0; u < vertex_count(); u++){
      // check if there is an edge between the two vertices
      if(has_edge(u,v)){
        // get the edge and weight and store in the edges vector
        int w;
        get_edge(u,v,w);
        edges.push_back(tuple<int,int,int>(u,w,v));
      }
    }
  }

  sortByEdgeWeight(edges, 0, edges.size()-1); // sort the edges by weight
  // for each edge vector
  for(auto e : edges) {
    // add each edge to the spanning tree
    spanning_tree.set_edge(get<0>(e), get<1>(e), get<2>(e));
    // if there is a cycle caused by the current edge, remove it since it can no longer be part of the spanning tree
    if(!spanning_tree.acyclic(false)){
      spanning_tree.remove_edge(get<0>(e), get<2>(e));
    }
  }
}

// Helper Merge function for the sortByEdgeWeight function
void Graph::merge(vector<tuple<int,int,int>>& edges, int start, int middle, int end) const{
  vector<tuple<int,int,int>> LeftSide, RightSide; // create tuples to hold edge values
  // calculate the sizes (amount of vertexes) for both sides
  int leftSize = middle - start + 1;
  int rightSize = end - middle;
  // indexes for edge setting
  int i = 0;
  int j = 0;
  int k = start;

  // populate left and riight tupe with edge values
  for(int i = 0; i < leftSize; i++){
    LeftSide.push_back(edges[start + i]);
  }
  for(int i = 0; i < rightSize; i++){
    RightSide.push_back(edges[middle + i + 1]);
  }

  // while we have not gone through all of the values on both sides
  while(i < leftSize && j < rightSize) {
    // if the first left vertex is <= the first right
    if(get<1>(LeftSide[i]) <= get<1>(RightSide[j])) {
      edges[k] = LeftSide[i]; // set edge to left side
      i++;
    }else{
      // right side first vertex is smaller so set edge to it
      edges[k] = RightSide[j]; 
      j++;
    }
    k++;
  }

  // while there are lefteover vertexes in either side..
  while(i < leftSize) {
    edges[k] = LeftSide[i]; 
    k++; 
    i++;
  }
  while(j < rightSize) {
    edges[k] = RightSide[j]; 
    k++; 
    j++;
  }
}

//----------------------------------------------------------------------
// HW-8 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Single-source shortest paths from the given source using
// Bellman-Ford's algorithm.
//
// Conditions: Assumes graph is directed and maximum weight is
//             numeric_limits<int>::max()
// 
// Input:
//  src -- the source vertex
//
// Output:
//  path_costs -- the minimum path cost from src to each vertex v
//                given as path_costs[v].
//
// Returns: true if there is not a negative cycle, and false
//          otherwise
//----------------------------------------------------------------------
bool Graph::bellman_ford_shortest_path(int src, Map& path_costs) const{
  // for each vertex in the graph
  for(int i = 0; i < vertex_count(); i++){
    path_costs[i] = numeric_limits<int>::max(); // set each path cost for each vertex at the maximum integer value for that type (int). aka 2147483647
  }
  path_costs[src] = 0; // set the first vertex path cost to 0 since we start there

  // for each vertex in the graph
  for(int j = 0; j < vertex_count()-1; j++){
    // for each vertex in the graph, for each vertex
    for(int u = 0; u < vertex_count(); u++){
      // for each vertex in the graph, for each vertex, for each vertex
      for(int v = 0; v < vertex_count(); v++){
        // if there is an edge between the two vertexes
        if(has_edge(u,v)){
          int edge;
          get_edge(u,v,edge); // get the edge weight between the two

          // if the path to the second vertex is greater than the path from the current vertex plus the weight between the two
          if(path_costs[v] > path_costs[u] + edge){
            path_costs[v] = path_costs[u] + edge; // set the new path weight to the smaller path cost
          }
        }
      }
    }
  }

  // for each vertex in the graph
  for(int u = 0; u < vertex_count(); u++){
    // for each vertex in the graph, for each vertex
    for(int v = 0; v < vertex_count(); v++){
      // if there is an edge between the two vertexes
      if(has_edge(u,v)){
        int edge;
        get_edge(u,v,edge); // get the edge weight between the two

        // if the path to the second vertex is greater than the path from the current vertex plus the weight between the two
        if(path_costs[v] > path_costs[u] + edge){
          return false;
        }
      }
    }
  }
  return true;
}

//----------------------------------------------------------------------
// HW-9 graph operations
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Finds a maximum-weight independent set for a path graph using
// dynamic programming.
//
// Conditions: Assumes the graph is a path-graph starting at vertex 0 and
//             ending at vertex n-1, that is, E = {(v0,v1), (v1,v2), ...,
//             v(n-1,vn)}
//
// Input:
//  vertex_weights -- weights for each of the n vertices in the graph
//
// Output:
//  S -- set of vertices representing the maximum independent set
//
// Returns: true if the graph is a path graph, false otherwise
//----------------------------------------------------------------------
bool Graph::path_max_independent_set(int vertex_weights[], Set& S) const{
  bool zero_cf, zero_ct;
  for (int i = 0; i < vertex_count(); i++) {
    zero_cf = false;
    zero_ct = false;
    list<int> ct, cf;
    connected_to(i, ct);
    connected_from(i, cf);

    if (ct.size() > 1 || cf.size() > 1) {
      // can't be connected to or from by more than 1 node
      return false;
    }

    if (ct.size() == 0) {
      // end of the path
      if (zero_ct) {
        // already saw an end, not path graph
        return false;
      }
      zero_ct = true; // mark that we've seen the end
    }

    if(cf.size() == 0){
      // start of the path
      if(zero_cf){
        // already saw a start, not path graph
        return false;
      }
      zero_cf = true; // mark that we've seen the start
    }
  }
  
  int A[vertex_count() + 1];
  A[0] = 0;
  A[1] = vertex_weights[0];

  for(int i = 2; i < vertex_count(); i++){
    A[i] = max(A[i-1], A[i-2] + vertex_weights[i - 1]);
  }

  int i = vertex_count();
  while(i >= 1){
    if(A[i] == A[i-1]){
      i--;
    }else{
      S.insert(i-1);
      i-=2;
    }
  }
  return true;
}

//----------------------------------------------------------------------
// Finds all-pairs shortest paths using the Floyd-Warshall algorithm.
//
// Conditions: Assumes weights is an uninitialized "n x n" matrix
//             represented as a vector of vectors (to be completely
//             filled in with all-pairs shortest path weights)
//
// Output:
//   weights -- shortest path weights from u to v given by weights[u][v]
//              for all u,v in the graph's vertices
//
// Returns: true if there is not a negative cycle, and false
//          otherwise
//----------------------------------------------------------------------
bool Graph::all_pairs_shortest_paths(vector<vector<int>>& weights) const{
  int v_count = vertex_count();
  int A[v_count + 1][v_count][v_count];

  for (int u = 0; u < v_count; u++) {
    for (int v = 0; v < v_count; v++) {
      int edge;
      if (u == v){
        A[0][u][v] = 0;
      }else if (get_edge(u, v, edge)) {
        A[0][u][v] = edge;
      }else{
        A[0][u][v] = numeric_limits<int>::max();
      }
    }
  }

  for (int k = 2; k < v_count + 1; k++) {
      for (int u = 0; u < v_count; u++) {
          for (int v = 0; v < v_count; v++) {
              if (A[k-2][u][k-1] == numeric_limits<int>::max() || A[k-2][k-1][v] == numeric_limits<int>::max()) {
                  A[k-1][u][v] = min(A[k-2][u][v], numeric_limits<int>::max());
              }
              else {
                  A[k-1][u][v] = min(A[k-2][u][v], A[k-2][u][k-1] + A[k-2][k-1][v]);
              }
          }
      }
  }


  for (int u = 0; u < v_count; u++) {
      if (A[v_count - 1][u][u] < 0) {
          return false;
      }
  }

  vector<int> temp;
  for (int u = 0; u < v_count; u++) {
      temp.clear();
      for (int v = 0; v < v_count; v++) {
          temp.push_back(A[v_count - 1][u][v]);
      }
      weights.push_back(temp);
  }
  return true;
}