//----------------------------------------------------------------------
// Name: 
// File: hw7_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for list and matrix graph implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <gtest/gtest.h>
#include "graph.h"
#include "adjacency_list.h"
#include "adjacency_matrix.h"


using namespace std;


//----------------------------------------------------------------------
// Helper functions for testing
//----------------------------------------------------------------------

void print_graph(const Graph& g)
{
  int n = g.vertex_count();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (g.has_edge(i,j)) {
        int edge_label;
        g.get_edge(i, j, edge_label);
        cout << "(" << i << "," << edge_label << "," << j << ")" << endl;
      }
    }
  }
}


//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

TEST(AdjacencyListTest, BasicDijkstraShortestPath) {
  AdjacencyList g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 6, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(3, 3, 2);
  g.set_edge(0, 4, 3);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

// TODO: Add two additional shortest path tests
TEST(AdjacencyListTest, MyBasicDijkstraShortestPath) {
  AdjacencyList g(4);
  g.set_edge(0, 7, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 1, 2);
  g.set_edge(1, 1, 3);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 3, 1);
  g.set_edge(3, 1, 0);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(6, path_costs[1]);
  ASSERT_EQ(2, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

TEST(AdjacencyListTest, MyBasicDijkstraShortestPath2) {
  AdjacencyList g(6);
  g.set_edge(0, 10, 1);
  g.set_edge(0, 15, 2);
  g.set_edge(1, 12, 3);
  g.set_edge(1, 15, 5);
  g.set_edge(2, 10, 4);
  g.set_edge(3, 2, 4);
  g.set_edge(3, 1, 5);
  g.set_edge(5, 5, 4);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(10, path_costs[1]);
  ASSERT_EQ(15, path_costs[2]);
  ASSERT_EQ(22, path_costs[3]);
  ASSERT_EQ(24, path_costs[4]);
  ASSERT_EQ(23, path_costs[5]);
}

TEST(AdjacencyListTest, BasicPrimMinSpanningTree) {
  AdjacencyList g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(0, 4, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(2, 5, 3);
  AdjacencyList tree(4);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
}

// TODO: Add two additional tests for Prim's algorithm
TEST(AdjacencyListTest, MyBasicPrimMinSpanningTree) {
  AdjacencyList g(6);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 8, 3);
  g.set_edge(2, 1, 1);
  g.set_edge(2, 4, 4);
  g.set_edge(3, 1, 5);
  g.set_edge(4, 2, 3);
  g.set_edge(4, 7, 5);
  AdjacencyList tree(6);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(2, 1) or tree.has_edge(1, 2));
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
  ASSERT_EQ(true, tree.has_edge(3, 5) or tree.has_edge(5, 3));
}

TEST(AdjacencyListTest, MyBasicPrimMinSpanningTree2) {
  AdjacencyList g(5);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 2);
  g.set_edge(1, 2, 4);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 4);
  g.set_edge(3, 3, 1);
  g.set_edge(4, 1, 3);
  AdjacencyList tree(5);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));  
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
}

TEST(AdjacencyListTest, BasicKruskalMinSpanningTree) {
  AdjacencyList g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 3, 2);
  g.set_edge(1, 5, 3);
  g.set_edge(1, 1, 4);  
  g.set_edge(2, 6, 3);  
  g.set_edge(3, 7, 4);
  AdjacencyList tree(5);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}


// TODO: Add two additional tests for Kruskal's algorithm
TEST(AdjacencyListTest, MyBasicKruskalMinSpanningTree) {
  AdjacencyList g(6);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 8, 3);
  g.set_edge(2, 1, 1);
  g.set_edge(2, 4, 4);
  g.set_edge(3, 1, 5);
  g.set_edge(4, 2, 3);
  g.set_edge(4, 7, 5);
  AdjacencyList tree(6);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(2, 1) or tree.has_edge(1, 2));
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
  ASSERT_EQ(true, tree.has_edge(3, 5) or tree.has_edge(5, 3));
}

TEST(AdjacencyListTest, MyBasicKruskalMinSpanningTree2) {
  AdjacencyList g(5);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 2);
  g.set_edge(1, 2, 4);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 4);
  g.set_edge(3, 3, 1);
  g.set_edge(4, 1, 3);
  AdjacencyList tree(5);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));  
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
}


//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------


// TODO: Add your tests above but for your adjacency matrix
TEST(AdjacencyMatrixTest, BasicDijkstraShortestPath) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(1, 6, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(3, 3, 2);
  g.set_edge(0, 4, 3);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(1, path_costs[1]);
  ASSERT_EQ(6, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

// TODO: Add two additional shortest path tests
TEST(AdjacencyMatrixTest, MyBasicDijkstraShortestPath) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 7, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 1, 2);
  g.set_edge(1, 1, 3);
  g.set_edge(2, 1, 3);
  g.set_edge(3, 3, 1);
  g.set_edge(3, 1, 0);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(6, path_costs[1]);
  ASSERT_EQ(2, path_costs[2]);
  ASSERT_EQ(3, path_costs[3]);
}

TEST(AdjacencyMatrixTest, MyBasicDijkstraShortestPath2) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 10, 1);
  g.set_edge(0, 15, 2);
  g.set_edge(1, 12, 3);
  g.set_edge(1, 15, 5);
  g.set_edge(2, 10, 4);
  g.set_edge(3, 2, 4);
  g.set_edge(3, 1, 5);
  g.set_edge(5, 5, 4);  
  Map path_costs;
  g.dijkstra_shortest_path(0, path_costs);
  // check size
  ASSERT_EQ(g.vertex_count(), path_costs.size());
  // check path costs
  ASSERT_EQ(0, path_costs[0]);
  ASSERT_EQ(10, path_costs[1]);
  ASSERT_EQ(15, path_costs[2]);
  ASSERT_EQ(22, path_costs[3]);
  ASSERT_EQ(24, path_costs[4]);
  ASSERT_EQ(23, path_costs[5]);
}

TEST(AdjacencyMatrixTest, BasicPrimMinSpanningTree) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 1, 1);
  g.set_edge(0, 3, 3);
  g.set_edge(0, 4, 2);
  g.set_edge(1, 2, 3);
  g.set_edge(2, 5, 3);
  AdjacencyMatrix tree(4);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
}

// TODO: Add two additional tests for Prim's algorithm
TEST(AdjacencyMatrixTest, MyBasicPrimMinSpanningTree) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 8, 3);
  g.set_edge(2, 1, 1);
  g.set_edge(2, 4, 4);
  g.set_edge(3, 1, 5);
  g.set_edge(4, 2, 3);
  g.set_edge(4, 7, 5);
  AdjacencyMatrix tree(6);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(2, 1) or tree.has_edge(1, 2));
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
  ASSERT_EQ(true, tree.has_edge(3, 5) or tree.has_edge(5, 3));
}

TEST(AdjacencyMatrixTest, MyBasicPrimMinSpanningTree2) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 2);
  g.set_edge(1, 2, 4);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 4);
  g.set_edge(3, 3, 1);
  g.set_edge(4, 1, 3);
  AdjacencyMatrix tree(5);
  g.prim_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));  
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
}


TEST(AdjacencyMatrixTest, BasicKruskalMinSpanningTree) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 3, 2);
  g.set_edge(1, 5, 3);
  g.set_edge(1, 1, 4);  
  g.set_edge(2, 6, 3);  
  g.set_edge(3, 7, 4);
  AdjacencyMatrix tree(5);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));
  ASSERT_EQ(true, tree.has_edge(1, 3) or tree.has_edge(3, 1));
  ASSERT_EQ(true, tree.has_edge(1, 4) or tree.has_edge(4, 1));
}

TEST(AdjacencyMatrixTest, MyBasicKruskalMinSpanningTree) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 4, 1);
  g.set_edge(0, 2, 2);
  g.set_edge(1, 8, 3);
  g.set_edge(2, 1, 1);
  g.set_edge(2, 4, 4);
  g.set_edge(3, 1, 5);
  g.set_edge(4, 2, 3);
  g.set_edge(4, 7, 5);
  AdjacencyMatrix tree(6);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 2) or tree.has_edge(2, 0));  
  ASSERT_EQ(true, tree.has_edge(2, 1) or tree.has_edge(1, 2));
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
  ASSERT_EQ(true, tree.has_edge(3, 5) or tree.has_edge(5, 3));
}

TEST(AdjacencyMatrixTest, MyBasicKruskalMinSpanningTree2) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 2, 1);
  g.set_edge(0, 3, 2);
  g.set_edge(1, 2, 4);
  g.set_edge(1, 1, 2);
  g.set_edge(2, 1, 4);
  g.set_edge(3, 3, 1);
  g.set_edge(4, 1, 3);
  AdjacencyMatrix tree(5);
  g.kruskal_min_spanning_tree(tree);
  // check sizes
  ASSERT_EQ(g.vertex_count(), tree.vertex_count());
  ASSERT_EQ(g.vertex_count() - 1, tree.edge_count());
  // check tree edges
  ASSERT_EQ(true, tree.has_edge(0, 1) or tree.has_edge(1, 0));
  ASSERT_EQ(true, tree.has_edge(1, 2) or tree.has_edge(2, 1));  
  ASSERT_EQ(true, tree.has_edge(2, 4) or tree.has_edge(4, 2));
  ASSERT_EQ(true, tree.has_edge(4, 3) or tree.has_edge(3, 4));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

