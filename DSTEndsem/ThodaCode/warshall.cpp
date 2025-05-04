#include <iostream>
#include <vector>
#include <climits>

using namespace std; 

void floydwarshall(vector<vector<int>> &dist){
  int V = dist.size();
  // Adding all the vertices one by one
  // to the set of intermediate vertices.
  for(int k = 0;k<V;k++){
    // Picking all the vertices as source one by one
    for(int i = 0;i<V;i++){
      //Pick all vertices as destination
      //for all the above picked sources
      for(int j = 0;j<V;j++){
        // shortest path from
        // i to j
        if(dist[i][k]!= 1e8 && dist[k][j]!=1e8){
          dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
        }
      }
    }
  }
}
 
int main (int argc, char *argv[]) {
  
  return 0;
}
