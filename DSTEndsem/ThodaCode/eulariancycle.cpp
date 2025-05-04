#include <iostream>
#include <list>

using namespace std;

class Graph {
int V;
list<int> *adj

public:
  Graph(int V){this->V=V;adj=};
  Graph(Graph &&) = default;
  Graph(const Graph &) = default;
  Graph &operator=(Graph &&) = default;
  Graph &operator=(const Graph &) = default;
  ~Graph();

private:
  
};

Graph::Graph() {
}

Graph::~Graph() {
}
