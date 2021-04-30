//----------------------------------------------------------------------
// NAME: Carter Mooring
// FILE: adjacency_list.cpp
// DATE: Feb. 4th, 2021
// DESC: Implements the public and private functions specified in 
//        adjacency_list.h using the provided member variables. Note 
//        that you cannot modify adjacency_list.h.
//----------------------------------------------------------------------

#include "adjacency_list.h"
#include <iostream>

using namespace std;

// specifically for printing cout messages. Controller by a boolean
void alert(string message){
    bool print = false;

    if(print == true){
        cout << "[ALERT] " << message << " started..." << endl;
    }
}

// default constructor
AdjacencyList::AdjacencyList(int vertex_count){
    alert("AdjacencyList constructor");
    // to create the adjaceny lists
    number_of_vertices = vertex_count;
    number_of_edges = 0;

    // linked-list array of out edges (for connected_to)
    adj_list_out = new Node*[number_of_vertices];
    // linked-list array of in edges (for connected_from)
    adj_list_in = new Node*[number_of_vertices];

    //to initialize
    for (int i = 0; i < number_of_vertices; ++i) {
        adj_list_out[i] = nullptr;
        adj_list_in[i] = nullptr;
    }
}

// destructor
AdjacencyList::~AdjacencyList(){
    alert("~AdjacencyList destructor");
    make_empty();
}

// copy constructor
AdjacencyList::AdjacencyList(const AdjacencyList& rhs){
    alert("AdjacencyList copy constructor");
    *this = rhs;
}

// assignment operator
AdjacencyList& AdjacencyList::operator=(const AdjacencyList& rhs){
    alert("operator=");
    number_of_vertices = rhs.number_of_vertices;
    number_of_edges = rhs.number_of_edges;

    adj_list_out = new Node*[number_of_vertices];

    // iterate through for all verticies
    for(int i = 0; i < number_of_vertices; i++){
        Node* curr = rhs.adj_list_out[i];
        // seg fault prevention, if exists check
        if(curr != nullptr) {
            // store values in list_out
            adj_list_out[i] = new Node();
            adj_list_out[i]->edge = curr->edge;
            adj_list_out[i]->vertex = curr->vertex;
            adj_list_out[i]->next = nullptr;
            curr = curr->next;          // keep iterating curr along with adj

            Node* temp = adj_list_out[i]->next;
            
            // Loop through whole list while not at end
            while(curr != nullptr) {
                temp = new Node();
                temp->edge = curr->edge;
                temp->vertex = curr->vertex;
                temp->next = nullptr;
                temp = temp->next;
                curr = curr->next;
            }
        } else {
            // else store nullptr to end
            adj_list_out[i] = nullptr;
        }
    }

    adj_list_in = new Node*[number_of_vertices];

    // iterate through for all verticies
    for(int i = 0; i < number_of_vertices; i++) {
        Node* curr = rhs.adj_list_in[i];

        // seg fault prevention, if exists check
        if(curr != nullptr) {
            adj_list_in[i] = new Node();
            adj_list_in[i]-> edge = curr->edge;
            adj_list_in[i]-> vertex = curr->vertex;
            adj_list_in[i]-> next = nullptr;
            curr = curr->next;

            Node* temp = adj_list_in[i]->next;
            
            // Loop through whole list while not at end
            while(curr != nullptr) {
                temp = new Node();
                temp->edge = curr->edge;
                temp->vertex = curr->vertex;
                temp->next = nullptr;
                temp = temp->next;
                curr = curr->next;
            }
        } else {
            // else store nullptr to end
            adj_list_in[i] = nullptr;
        }
    }
    return *this;
}

// add or update an edge between existing vertices in the graph
void AdjacencyList::set_edge(int v1, int edge_label, int v2){
    alert("set_edge");
    if(v1 > number_of_vertices || v2 > number_of_vertices){
        return;
    } else {
        //for add_edge, has_edge, get_edge, search for v in adj_list_out[u]
        Node* curr = adj_list_out[v1];
        // Loop through whole list while not at end
        while(curr != nullptr){
            if(curr->vertex == v2){
                curr->edge = edge_label;
                curr = adj_list_in[v2];

                // Loop through whole list while not at end
                while(curr != nullptr){
                    // if the vertexes match
                    if(curr->vertex == v1){
                        curr->edge = edge_label;
                    }
                    curr = curr->next;
                }
                return;
            }
            curr = curr->next;
        }

        number_of_edges++;

        // Update adj_list_out with new set_edge
        Node* temp_out = new Node();
        temp_out->edge = edge_label;
        temp_out->vertex = v2;
        temp_out->next = adj_list_out[v1];
        adj_list_out[v1] = temp_out;

        // Update adj_list_out with new set_edge
        Node* temp_in = new Node();
        temp_in->edge = edge_label;
        temp_in->vertex = v1;
        temp_in->next = adj_list_in[v2];
        adj_list_in[v2] = temp_in;
    }
}

// check if the given edge is in the graph
bool AdjacencyList::has_edge(int v1, int v2) const{
    alert("has_edge");
    //for add_edge, has_edge, get_edge, search for v in adj_list_out[u]
    Node* curr = adj_list_out[v1];
    // Loop through whole list while not at end
    while(curr != nullptr){
        // if vertecies match then has
        if(curr->vertex == v2){
            return true;
        }
        curr = curr->next;
    }
    return false;
} 

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyList::get_edge(int v1, int v2, int& edge) const{
    alert("get_edge");
    //for add_edge, has_edge, get_edge, search for v in adj_list_out[u]
    Node* curr = adj_list_out[v1];
    // Loop through whole list while not at end
    while(curr != nullptr){
        if(curr->vertex == v2){
            // if vertecies match then this is the edge we want
            edge = curr->edge;
            return true;
        }
        curr = curr->next;
    }
    return false;
} 

// remove edge between v1 and v2 if the edge exists
void AdjacencyList::remove_edge(int v1, int v2) {
    if(!has_edge(v1, v2)){
        return;
    }
    
    Node* prev_node = nullptr;
    Node* curr_node = adj_list_out[v1];
    while(curr_node) {
        if (curr_node->vertex == v2){
            if(prev_node){
                prev_node->next = curr_node->next;
                delete curr_node;
            }else{
                adj_list_out[v1] = adj_list_out[v1]->next;
            }
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    
    prev_node = nullptr;
    curr_node = adj_list_in[v2];
    while(curr_node) {
        if (curr_node->vertex == v1){
            if(prev_node){
                prev_node->next = curr_node->next;
                delete curr_node;
            }else{
                adj_list_in[v2] = adj_list_in[v2]->next;
            }
            number_of_edges--;
            return;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
}

// get all vertices on an outgoing edge from given vertex
void AdjacencyList::connected_to(int v1, std::list<int>& vertices) const{
    alert("connected_to");
    if (v1 < number_of_vertices && v1 >= 0){
       Node* curr = adj_list_out[v1];
        // Loop through whole list while not at end
        while(curr != nullptr){
            vertices.push_front(curr->vertex);
            curr = curr->next;
        } 
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyList::connected_from(int v2, std::list<int>& vertices) const{
    alert("connected_from");
    if (v2 < number_of_vertices && v2 >= 0){
        Node* curr = adj_list_in[v2];
        // Loop through whole list while not at end
        while(curr != nullptr) {
            vertices.push_back(curr->vertex);
            curr = curr->next;
        }
    }
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyList::adjacent(int v, std::list<int>& vertices) const{
    alert("adjacent");
    connected_to(v, vertices);
    connected_from(v, vertices);
}

// get number of nodes in the graph
int AdjacencyList::vertex_count() const{
    alert("vertex_count");
    return number_of_vertices;
}

// get number of edges in the graph
int AdjacencyList::edge_count() const{
    alert("edge_count");
    return number_of_edges;
}

// helper function to delete adj_list
void AdjacencyList::make_empty(){
    alert("make_empty");
    // iterate through for all verticies
    for(int i = 0; i < number_of_vertices; i++) {
        // first delete the adj_list_in
        Node* curr = adj_list_out[i];
        // Loop through whole list while not at end
        while(curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }

        // second delete the adj_list_in
        curr = adj_list_in[i];
        // Loop through whole list while not at end
        while(curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
}