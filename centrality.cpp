#include "centrality.h"
#include "closeness.h"
#include<bits/stdc++.h>


int Graph::degreeCentrality(int s)
{
  int totalDistance =0; 
   region[s].visitation = FOUND; //automatically finds s
   region[s].distance = 0;
   queue<structRegion> q;
   q.push(region[s]);
   while (!q.empty())
   {
      auto u = q.front();
      q.pop();
      for (const auto& v : adjList[u.id])
      {
         if (region[v].visitation == NOTVISITED)
         {
            region[v].visitation = FOUND;
            region[v].distance = u.distance + 1; //Increments distance by each edge
            q.push(region[v]);
         }
      }
      u.visitation = VISITED;
     
     //Test to only obtain Level 1 edges
      if (region[u.id].distance==1)
      totalDistance = totalDistance + 1;
    
   }
   
   //resetting all nodes back to NOTVISITED to run program again
   for(int i =0; i<totalRegions; ++i){
   region[i].visitation = NOTVISITED;}

   //int return with total distance
  return totalDistance;

}
