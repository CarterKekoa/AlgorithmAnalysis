//----------------------------------------------------------------------
// NAME: Carter Mooring
// FILE: adjacency_matrix.cpp
// DATE: Feb. 4th, 2021
// DESC: Implements the public and private functions specified in 
//        adjacency_matrix.h using the provided member variables. Note 
//        that you cannot modify adjacency_matrix.h.
//----------------------------------------------------------------------

#include "adjacency_matrix.h"
#include <iostream>

using namespace std;

// specifically for printing cout messages. Controller by a boolean
void alerts(string message){
    bool print = false;

    // if true then all alerts will print, must be manually changed
    if(print == true){
        cout << "[ALERT] " << message << " started..." << endl;
    }
}

// default constructor
AdjacencyMatrix::AdjacencyMatrix(int vertex_count){
    alerts("AdjacencyMatrix constructor");
    // initialize adjaceny matrix private values
    number_of_edges = 0;
    number_of_vertices = vertex_count;
    
    // create the 2d matrixes size based on number of verticies
    adj_matrix = new int*[vertex_count*vertex_count];
    // for loop to iterate through whole 2d matrix and populate positions
    for(int i = 0; i < vertex_count; i++){
        for(int j = 0; j < vertex_count; j++){
            adj_matrix[index(i,j)] = nullptr;
        }
    }
}

// destructor
AdjacencyMatrix::~AdjacencyMatrix(){
    alerts("~AdjacencyMatrix destructor");
    make_empty();   // simply calls the make empty function
}

// copy constructor
AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& rhs){
    alerts("AdjacencyMatrix copy constructor");
    *this = rhs;
}

// assignment operator
AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& rhs){
    alerts("operator=");
    number_of_vertices = rhs.number_of_vertices;
    number_of_edges = rhs.number_of_edges;

    adj_matrix = new int*[number_of_vertices*number_of_vertices];
    
    // iterate through for all verticies
    for(int i = 0; i < number_of_vertices; i++){
        for(int j = 0; j < number_of_vertices; j++){
            // seg fault prevention, if exists check
            if(rhs.adj_matrix[index(i,j)] != nullptr) {
                adj_matrix[index(i,j)] = new int[1];
                *adj_matrix[index(i,j)] = *rhs.adj_matrix[index(i,j)];
            } else {
                // else store nullptr to end
                adj_matrix[index(i,j)] = nullptr;
            }
        }
    }
    return *this;
}

// add or update an edge between existing vertices in the graph
void AdjacencyMatrix::set_edge(int v1, int edge_label, int v2){
    alerts("set_edge");
    // Check if empty so we can add edge
    if(v1 > number_of_vertices || v2 > number_of_vertices){
        return;
    }else if(adj_matrix[index(v1,v2)] == nullptr){
        number_of_edges += 1;
        adj_matrix[index(v1,v2)] = new int[1];
        *adj_matrix[index(v1,v2)] = edge_label;
    }
    *adj_matrix[index(v1,v2)] = edge_label;
}

// check if the given edge is in the graph
bool AdjacencyMatrix::has_edge(int v1, int v2) const{
    alerts("has_edge");
    // seg fault prevention, if exists check
    if(adj_matrix[index(v1,v2)] != nullptr){
        return adj_matrix[index(v1,v2)];
    }
}

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyMatrix::get_edge(int v1, int v2, int& edge) const{
    alerts("get_edge");
    // seg fault prevention, if exists check
    if(adj_matrix[index(v1,v2)] != nullptr){
        edge = *adj_matrix[index(v1,v2)];
    }
    return adj_matrix[index(v1,v2)];
} 

// remove edge between v1 and v2 if the edge exists
void AdjacencyMatrix::remove_edge(int v1, int v2) {
    if(has_edge(v1, v2)){
        adj_matrix[index(v1, v2)] = nullptr;
        number_of_edges -= 1;
    }
}
  
// get all vertices on an outgoing edge from given vertex
void AdjacencyMatrix::connected_to(int v1, std::list<int>& vertices) const{
    alerts("connected_to");
    // only need to loop through verticies for vertices on edge
    //cout << "number of vertices: " << number_of_vertices << endl;
    for(int i = 0; i < number_of_vertices; i++){
        //cout << "i: " << i << "     v1: " << v1 << endl;
        if(v1 < number_of_vertices && v1 >= 0){
            //cout << "adjmatrix: " << adj_matrix[index(v1,i)] << endl;
            if(adj_matrix[index(v1,i)] != nullptr){
                vertices.push_back(i);
            }
        }
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyMatrix::connected_from(int v2, std::list<int>& vertices) const{
    alerts("connected_from");
    // only need to loop through verticies for vertices on edge
    for(int i = 0; i < number_of_vertices; i++){
        if(adj_matrix[index(i,v2)] != nullptr){
           vertices.push_back(i); 
        }  
    }  
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyMatrix::adjacent(int v, std::list<int>& vertices) const{
    alerts("adjacent");
    connected_to(v,vertices);
    connected_from(v,vertices);
}

// get number of nodes in the graph
int AdjacencyMatrix::vertex_count() const{
    alerts("vertex_count");
    return number_of_vertices;
}

// get number of edges in the graph
int AdjacencyMatrix::edge_count() const{
    alerts("edge_count");
    return number_of_edges;
}

// return the matrix index for edge x->y
int AdjacencyMatrix::index(int x, int y) const{
    alerts("index");
    return (number_of_vertices * x) + y;
}

// delete the adjacency matrix
void AdjacencyMatrix::make_empty(){
    alerts("make_empty");
    // iterate through 2d array and delete each position for entire size
    for(int i = 0; i < number_of_vertices; i++){
        for(int j = 0; j < number_of_vertices; j++){
            delete adj_matrix[index(i,j)];
        }  
    } 
    delete adj_matrix;
}