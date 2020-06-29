#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include "graph.h"


using namespace std;

// to be implemented
Graph::~Graph() {
    for (auto a : adj_list) {
        delete a; 
    }
}

void Graph::buildGraph(ifstream &input) {
    if (!input.is_open()) {
        throw runtime_error("could not open file");
    }
    string line; 
    list<int> adList; 
    list<int>* adList_ptr; 
    while(getline(input, line)) {
        istringstream iss(line); 
        int vertex; 
        while(iss >> vertex) {
            if (vertex == -1) {
                break;
            }
            Vertex v(vertex); 
            node_list.push_back(v);
            while (vertex != -1) {
                iss >> vertex; 
                if (vertex != -1) 
                { 
                adList.push_back(vertex); 
                }
            } 
        }
        adList_ptr = new list<int>(adList); 
        adj_list.push_back(adList_ptr); 
        adList.clear(); 
    }

}
void Graph::displayGraph() {
    for (int i = 0; i < node_list.size(); i++)
    {
        cout << node_list[i].label << ":";
        for (auto a : *adj_list[i])
        {
            cout << a << " ";
        }
        cout << endl;
    }
}
