//----------------------------------------------------------------------
// Name: 
// File: hw4_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for DFS and related algorithms
//----------------------------------------------------------------------


#include <iostream>
#include <string>
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

void print_search_tree(const Map& search_tree)
{
  for (pair<int,int> p : search_tree)
    cout << "parent: " << p.second << ", child: " << p.first << endl;
}

void print_path(const list<int>& path)
{
  for (int v : path)
    cout << v << " ";
  cout << endl;
}

void print_ordering(const Map& ordering)
{
  for (pair<int,int> p : ordering)
    cout << p.first << " has order " << p.second << endl;
}


//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

// Basic DFS test over a directed graph
TEST(AdjacencyListTest, BasicDirectedDFS) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(3, 0, 0);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
  // directed dfs from 1
  tree.clear();
  g.dfs(true, 1, tree);
  ASSERT_EQ(4, tree.size());
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[1]);
  ASSERT_EQ(1, tree[0]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
}


// TODO: at least two additional directed graph DFS tets
TEST(AdjacencyListTest, MyBasicDirectedDFS) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 1);
  g.set_edge(3, 0, 0);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(1, tree[2]);
  ASSERT_EQ(2, tree[3]);
}

TEST(AdjacencyListTest, MyBasicDirectedDFS2) {
  AdjacencyList g(2);
  g.set_edge(0, 0, 1);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
}

// Basic undirected graph DFS test
TEST(AdjacencyListTest, BasicUndirectedDFS) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 2);
  ASSERT_EQ(true, g.acyclic(false));
  g.set_edge(3, -1, 2);
  ASSERT_EQ(false, g.acyclic(false));
}


// TODO: at least two additional undirected graph DFS tets
TEST(AdjacencyListTest, MyBasicUndirectedDFS) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  ASSERT_EQ(false, g.acyclic(false));
}

TEST(AdjacencyListTest, MyBasicUndirectedDFS2) {
  AdjacencyList g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 4);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 5);
  ASSERT_EQ(false, g.acyclic(false));
}

// Basic directed cycle check test
TEST(AdjacencyListTest, BasicDFSDirectedCycleCheck) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(0, 0, 3);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(2, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}


// TODO: at least two additional directed graph cycle tests
TEST(AdjacencyListTest, MyBasicDFSDirectedCycleCheck) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}

TEST(AdjacencyListTest, MyBasicDFSDirectedCycleCheck2) {
  AdjacencyList g(2);
  g.set_edge(0, 0, 1);
  ASSERT_EQ(true, g.acyclic(true));
}

// Basic undirected cycle check test
TEST(AdjacencyListTest, BasicDFSUndirectedCycleCheck) {
  AdjacencyList g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  ASSERT_EQ(false, g.acyclic(false));
}

// TODO: at least two additional undirected graph cycle tests
TEST(AdjacencyListTest, MyBasicDFSUndirectedCycleCheck) {
  AdjacencyList g(2);
  g.set_edge(0, 0, 1);
  ASSERT_EQ(true, g.acyclic(false));
}

TEST(AdjacencyListTest, MyBasicDFSUndirectedCycleCheck2) {
  AdjacencyList g(7);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 4);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 6);
  g.set_edge(6, 0, 5);
  g.set_edge(6, 0, 0);
  ASSERT_EQ(false, g.acyclic(false));
}

// Basic directed transitive closure test
TEST(AdjacencyListTest, BasicDirectedUnweightedDFSTransClosure) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(1, 4));
}


// TODO: at least two additional directed graph transitive closure tests
TEST(AdjacencyListTest, MyBasicDirectedUnweightedDFSTransClosure) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 1));
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
}

TEST(AdjacencyListTest, MyBasicDirectedUnweightedDFSTransClosure2) {
  AdjacencyList g(9);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(0, 0, 5);
  g.set_edge(5, 0, 6);
  g.set_edge(6, 0, 7);
  g.set_edge(7, 0, 8);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 5));
  ASSERT_EQ(true, tc_g.has_edge(0, 8));
  ASSERT_EQ(true, tc_g.has_edge(1, 4));
}

// Basic undirected transitive closure test
TEST(AdjacencyListTest, UndirectedUnweightedDFSTransClosure) {
  AdjacencyList g(3);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2) || tc_g.has_edge(2, 0));
}


// TODO: at least two additional undirected graph transitive closure tests
TEST(AdjacencyListTest, MyUndirectedUnweightedDFSTransClosure) {
  AdjacencyList g(7);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  g.set_edge(5, 0, 6);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 6) || tc_g.has_edge(6, 0));
}

TEST(AdjacencyListTest, MyUndirectedUnweightedDFSTransClosure2) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyList tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 4) || tc_g.has_edge(4, 0));
  ASSERT_EQ(true, tc_g.has_edge(2, 4) || tc_g.has_edge(4, 2));
}

// Basic topological sort test
TEST(AdjacencyListTest, BasicDFSTopologicalSort) {
  AdjacencyList g1(5);
  g1.set_edge(0, 0, 2);
  g1.set_edge(1, 0, 2);
  g1.set_edge(2, 0, 3);
  g1.set_edge(2, 0, 4);
  g1.set_edge(3, 0, 4);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
  AdjacencyList g2(5);
  g2.set_edge(0, 0, 2);
  g2.set_edge(1, 0, 2);
  g2.set_edge(2, 0, 3);
  g2.set_edge(2, 0, 4);
  g2.set_edge(4, 0, 3);
  vertex_ordering.clear();
  g2.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[4], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
}

// TODO: at least two additional topological sorting tests
TEST(AdjacencyListTest, MyBasicDFSTopologicalSort) {
  AdjacencyList g1(5);
  g1.set_edge(0, 0, 3);
  g1.set_edge(1, 0, 3);
  g1.set_edge(2, 0, 3);
  g1.set_edge(3, 0, 4);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[1]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[4]);
}

TEST(AdjacencyListTest, MyBasicDFSTopologicalSort2) {
  AdjacencyList g1(7);
  g1.set_edge(0, 0, 2);
  g1.set_edge(1, 0, 2);
  g1.set_edge(2, 0, 3);
  g1.set_edge(2, 0, 4);
  g1.set_edge(2, 0, 5);
  g1.set_edge(4, 0, 6);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[5], vertex_ordering[6]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
}

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------


// TODO: Repeat above tests here for adjacency matrix implementation
// Basic DFS test over a directed graph
TEST(AdjacencyMatrixTest, BasicDirectedDFS) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(1, 0, 0);
  g.set_edge(3, 0, 0);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
  // directed dfs from 1
  tree.clear();
  g.dfs(true, 1, tree);
  ASSERT_EQ(4, tree.size());
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[1]);
  ASSERT_EQ(1, tree[0]);
  ASSERT_EQ(0, tree[2]);
  ASSERT_EQ(2, tree[3]);
}


// TODO: at least two additional directed graph DFS tets
TEST(AdjacencyMatrixTest, MyBasicDirectedDFS) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 1);
  g.set_edge(3, 0, 0);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
  ASSERT_EQ(1, tree[2]);
  ASSERT_EQ(2, tree[3]);
}

TEST(AdjacencyMatrixTest, MyBasicDirectedDFS2) {
  AdjacencyMatrix g(2);
  g.set_edge(0, 0, 1);
  Map tree;
  // directed dfs from 0
  g.dfs(true, 0, tree);
  // all nodes found
  ASSERT_EQ(g.vertex_count(), tree.size());
  // check parents
  ASSERT_EQ(-1, tree[0]);
  ASSERT_EQ(0, tree[1]);
}

// Basic undirected graph DFS test
TEST(AdjacencyMatrixTest, BasicUndirectedDFS) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 2);
  ASSERT_EQ(true, g.acyclic(false));
  g.set_edge(3, -1, 2);
  ASSERT_EQ(false, g.acyclic(false));
}


// TODO: at least two additional undirected graph DFS tets
TEST(AdjacencyMatrixTest, MyBasicUndirectedDFS) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  ASSERT_EQ(false, g.acyclic(false));
}

TEST(AdjacencyMatrixTest, MyBasicUndirectedDFS2) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 4);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 5);
  ASSERT_EQ(false, g.acyclic(false));
}

// Basic directed cycle check test
TEST(AdjacencyMatrixTest, BasicDFSDirectedCycleCheck) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(0, 0, 3);
  ASSERT_EQ(true, g.acyclic(true));
  g.set_edge(2, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}


// TODO: at least two additional directed graph cycle tests
TEST(AdjacencyMatrixTest, MyBasicDFSDirectedCycleCheck) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  ASSERT_EQ(false, g.acyclic(true));
}

TEST(AdjacencyMatrixTest, MyBasicDFSDirectedCycleCheck2) {
  AdjacencyMatrix g(2);
  g.set_edge(0, 0, 1);
  ASSERT_EQ(true, g.acyclic(true));
}

// Basic undirected cycle check test
TEST(AdjacencyMatrixTest, BasicDFSUndirectedCycleCheck) {
  AdjacencyMatrix g(4);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 0);
  ASSERT_EQ(false, g.acyclic(false));
}

// TODO: at least two additional undirected graph cycle tests
TEST(AdjacencyMatrixTest, MyBasicDFSUndirectedCycleCheck) {
  AdjacencyMatrix g(2);
  g.set_edge(0, 0, 1);
  ASSERT_EQ(true, g.acyclic(false));
}

TEST(AdjacencyMatrixTest, MyBasicDFSUndirectedCycleCheck2) {
  AdjacencyMatrix g(7);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 4);
  g.set_edge(2, 0, 5);
  g.set_edge(3, 0, 6);
  g.set_edge(6, 0, 5);
  g.set_edge(6, 0, 0);
  ASSERT_EQ(false, g.acyclic(false));
}

// Basic directed transitive closure test
TEST(AdjacencyMatrixTest, BasicDirectedUnweightedDFSTransClosure) {
  
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
  ASSERT_EQ(true, tc_g.has_edge(1, 4));
}


// TODO: at least two additional directed graph transitive closure tests
TEST(AdjacencyMatrixTest, MyBasicDirectedUnweightedDFSTransClosure) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 1));
  ASSERT_EQ(true, tc_g.has_edge(0, 2));
  ASSERT_EQ(true, tc_g.has_edge(0, 3));
  ASSERT_EQ(true, tc_g.has_edge(0, 4));
}

TEST(AdjacencyMatrixTest, MyBasicDirectedUnweightedDFSTransClosure2) {
  
  AdjacencyMatrix g(9);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(0, 0, 5);
  g.set_edge(5, 0, 6);
  g.set_edge(6, 0, 7);
  g.set_edge(7, 0, 8);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(true, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 5));
  ASSERT_EQ(true, tc_g.has_edge(0, 8));
  ASSERT_EQ(true, tc_g.has_edge(1, 4));
}

// Basic undirected transitive closure test
TEST(AdjacencyMatrixTest, UndirectedUnweightedDFSTransClosure) {
  AdjacencyMatrix g(3);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 2) || tc_g.has_edge(2, 0));
}


// TODO: at least two additional undirected graph transitive closure tests
TEST(AdjacencyMatrixTest, MyUndirectedUnweightedDFSTransClosure) {
  AdjacencyMatrix g(7);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  g.set_edge(5, 0, 6);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 6) || tc_g.has_edge(6, 0));
}

TEST(AdjacencyMatrixTest, MyUndirectedUnweightedDFSTransClosure2) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyMatrix tc_g(g);
  g.unweighted_transitive_closure(false, tc_g);
  ASSERT_EQ(true, tc_g.has_edge(0, 4) || tc_g.has_edge(4, 0));
  ASSERT_EQ(true, tc_g.has_edge(2, 4) || tc_g.has_edge(4, 2));
}

// Basic topological sort test
TEST(AdjacencyMatrixTest, BasicDFSTopologicalSort) {
  AdjacencyMatrix g1(5);
  g1.set_edge(0, 0, 2);
  g1.set_edge(1, 0, 2);
  g1.set_edge(2, 0, 3);
  g1.set_edge(2, 0, 4);
  g1.set_edge(3, 0, 4);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
  AdjacencyMatrix g2(5);
  g2.set_edge(0, 0, 2);
  g2.set_edge(1, 0, 2);
  g2.set_edge(2, 0, 3);
  g2.set_edge(2, 0, 4);
  g2.set_edge(4, 0, 3);
  vertex_ordering.clear();
  g2.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[4], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
}

// TODO: at least two additional topological sorting tests
TEST(AdjacencyMatrixTest, MyBasicDFSTopologicalSort) {
  AdjacencyMatrix g1(5);
  g1.set_edge(0, 0, 3);
  g1.set_edge(1, 0, 3);
  g1.set_edge(2, 0, 3);
  g1.set_edge(3, 0, 4);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[1]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[2], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[3], vertex_ordering[4]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[4]);
}

TEST(AdjacencyMatrixTest, MyBasicDFSTopologicalSort2) {
  AdjacencyMatrix g1(7);
  g1.set_edge(0, 0, 2);
  g1.set_edge(1, 0, 2);
  g1.set_edge(2, 0, 3);
  g1.set_edge(2, 0, 4);
  g1.set_edge(2, 0, 5);
  g1.set_edge(4, 0, 6);
  Map vertex_ordering;
  g1.dfs_topological_sort(vertex_ordering);
  ASSERT_LE(vertex_ordering[5], vertex_ordering[6]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[3]);
  ASSERT_LE(vertex_ordering[1], vertex_ordering[2]);
  ASSERT_LE(vertex_ordering[0], vertex_ordering[2]);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

