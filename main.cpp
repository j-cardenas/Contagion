#include <iostream>
#include "Input.h"
#include "Database.h"
#include "Output.h"
#include "Simulation.h"
#include "closeness.h"
#include "centrality.h"
#include "Random.h"
#include "Equal.h"

#include<bits/stdc++.h>

/******Jesus Start*****/
bool sortbyCloseness(const pair<int,int> &a, const pair<int,int> &b)
{ return (a.second < b.second); }

bool sortDegree(const pair<int,int> &a,  const pair<int,int> &b)
{ return (a.second > b.second); }
/********Jesus End****/

using namespace std;

int main()
{

 /******************DO NOT TOUCH*****James Start********************/ 
    Input in;

    //read files
    in.getConfig();

    //print population
    cout << "Regional Population" << endl;
    in.printPopulation();
    cout <<endl;

    //print adjacency list
    cout << "Adjacency List" << endl;
    in.printAdjacencyList();
    cout << endl;

    Database d;
    Database d2 = d;
    Output out;

    string strategy = "default";

    //seting up database
    d.setRegionPopulation(in.getRegionPopulation());
    d.setAdjacencyList(in.getAdjacencyList());
    d.setSimulationVariables(in.passInfectedArea(), in.passInfectiousPeriod(), in.passContactRate(), in.passVaccines());
    /******************DO NOT TOUCH********James End*****************/ 


/******************Jesus Start******************/
   int numRegions = d.getNumberOfRegions(); //number of regions
   int arr[numRegions]; //Region
   int arr1[numRegions]; //Distance
   int arrCloseness[numRegions]; //Order Closeness
   int arrDegree[numRegions]; //Order Degree
   Graph reg(numRegions); //Constructor
  vector< pair <int, int> > pa1r; //Cloness Centrality
  vector< pair <int, int> > pa2r; //Degree Centrality

  //Linked list
  for(int i=0; i<numRegions; i++){

    for(int j= 0; j<d.getNumberOfAdjacencies(i + 1); j++){

      reg.addEdge(i, d.getAdjacency(i + 1, j) - 1);
    }
  }

//populates array with ID and Distance
  for(int i =0; i<numRegions; ++i){
    arr[i] = i;
    arr1[i] = reg.closenessCentrality(i);
  }

//Pushes array into pair
int n = sizeof(arr)/sizeof(arr[0]);
for (int i=0; i<n; i++)
  pa1r.push_back( make_pair(arr[i],arr1[i]) );

//Sorts vector by second element
sort(pa1r.begin(), pa1r.end(), sortbyCloseness);

//Close Centrality Order
    for (int i=0; i<n; i++)
     arrCloseness[i] = pa1r[i].first;

int vac = d.getVaccines();
for(int i = 0; i < numRegions; i++) {
    if(vac - d.getNumberOfPeople(arrCloseness[i] + 1)> 0) {
      d.setVaccines(arrCloseness[i] + 1, d.getNumberOfPeople(arrCloseness[i] + 1));
      vac -= d.getNumberOfPeople(arrCloseness[i] + 1);
    }

    else
    {
      d.setVaccines(arrCloseness[i] + 1, vac);
      vac = 0;
    }
}

/*
cout <<"Order of cloness"<<endl;

       for (int i=0; i<n; i++)
  cout << pa1r[i].first<<"  "<<pa1r[i].second<<endl;

 //closseness
    strategy = "closseness"; 
    Simulation(d, out, strategy);
    d = d2;
*/

  ////////////////////////////////////////////////////////////////
//populates array with ID and Distance
  for(int i =0; i<numRegions; ++i){
  arr[i] = i;
  arr1[i] = reg.degreeCentrality(i);
  }

//Pushes array into pair

 for (int i=0; i<n; i++)
    pa2r.push_back( make_pair(arr[i],arr1[i]) );

//Sorts vector by second element
sort(pa2r.begin(), pa2r.end(), sortDegree);

//Degree Centrality Order
    for (int i=0; i<n; i++)
     arrDegree[i] = pa2r[i].first;
  
  /*
  cout <<"Order of Centrality"<<endl;
   for (int i=0; i<n; i++)
  cout << pa2r[i].first<<"  "<<pa2r[i].second<<endl;*/

vac = d.getVaccines();
for(int i = 0; i < numRegions; i++) {
    if(vac - d.getNumberOfPeople(arrDegree[i] + 1)> 0) {
      d.setVaccines(arrDegree[i] + 1, d.getNumberOfPeople(arrDegree[i] + 1));
      vac -= d.getNumberOfPeople(arrDegree[i] + 1);
    }

    else
    {
      d.setVaccines(arrCloseness[i] + 1, vac);
      vac = 0;
    }
}
/*
 //degree
 strategy = "degree"; 
 Simulation(d, out, strategy);
 d = d2;
 */


/**********************Jesus End************************/
    
    random(d);
    strategy = "random";
    Simulation(d, out, strategy);
    d = d2;
    /*
    equal(d);
    strategy = "equal";
    Simulation(d, out, strategy);
    d = d2;
    */
    out.printAnalysis();
}