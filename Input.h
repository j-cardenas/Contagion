#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Input
{
    private:
                //files
                string configFile;
                string populationFile;
                string regionFile;

                //region setup
                vector<int> regionPopulation;
                vector<vector<int>> adjacencyList;

                //simulation variables
                int infectedArea;
                int infectiousPeriod;
                int contactRate;
                int vaccines;

    public:
                //constructer
                Input();

                //initializes private variables
                void getConfig();

                //prints population of all regions
                void printPopulation();

                //prints adjacency list version of region file
                void printAdjacencyList();

                //get region setup variables
                vector<int> getRegionPopulation();
                vector<vector<int>> getAdjacencyList();

                //passes simulation variables
                int passInfectedArea();
                int passInfectiousPeriod();
                int passContactRate();
                int passVaccines();

};

#endif