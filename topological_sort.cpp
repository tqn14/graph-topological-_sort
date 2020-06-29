// topological sort
#include <vector>
#include <list>
#include <queue>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include "graph.h"

using namespace std; 

class out_of_range : public logic_error {
public:
  explicit out_of_range (char const* msg=nullptr) : logic_error(msg) {}
};
struct cycleGraph : public logic_error {
  explicit cycleGraph(char const* msg=nullptr): logic_error(msg) {}
};
void Graph::compute_indegree()
{ 
    for (int i = 0; i < node_list.size(); i++)
    {   
        int count = 0; 
        for (auto a : adj_list)
        {   
            for (auto b : *a)
            { 
            if (b ==node_list[i].label) 
                count ++; 
            }
        }
        node_list[i].indegree = count; 
        //cout << "indegree:" << node_list[i].indegree << endl;
    }
}
void Graph::makeEmpty(queue<Vertex*> pq) {
    while (!pq.empty()) {
      pq.pop();
    }
}
int Graph::findValue(int& i) 
{   
    vector<Vertex>::iterator it;
    it = find (node_list.begin(), node_list.end(), i);
    if (it != node_list.end()) {
      int d = distance(node_list.begin(), it);
      return d; 
    } else {
      throw std::out_of_range("element is not in the graph");
    }
}
void Graph::topological_sort()
{
    queue<Vertex*> q; 
    int count = 0; 
    makeEmpty(q);
    for (int i = 0; i < node_list.size(); i++) {
      if (node_list[i].indegree == 0) {
        q.push(&node_list[i]);
        //cout << "push: " << node_list[i].label << endl;
      }
    }
    while (!q.empty())
    {
      Vertex *v = q.front();
      //cout << "v.label: "<< v->label << endl;
      q.pop(); 
      v->top_num = count++;
      //cout << "count " << count << endl;
      int j = findValue(v->label);
      //cout << "j index " << j << endl; 
      for (auto a : *adj_list[j]) {
          //cout << "a: " << a << endl;
          int i = findValue(a);
          if (--node_list[i].indegree == 0) {
             q.push(&node_list[i]); 
             //cout << "push2: " << node_list[i].label << endl;
          } 
      }
    }
    if (count != node_list.size()) 
    {
      throw cycleGraph("there are cycles in the graph");
    }
}

void Graph::print_top_sort()
{
    cout << node_list[0].label << " ";
    for (int i = 1; i <= node_list.size(); i++) 
    {
      for (int j =1; j < node_list.size(); j++) 
      {
        //cout << node_list[0].label << " ";
        if (node_list[j].top_num == i)  {
          cout << node_list[j].label << " ";
        }
      }
    }
    //cout << "here:" <<node_list[0].top_num;
    cout << endl;
}
