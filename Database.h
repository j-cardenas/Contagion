#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

using namespace std;

class Database
{
    private:
                vector<vector<pair<char, int>>> people; //stores all people statuses
                vector<vector<int>> adjacencyList; //stores adjacency list
                vector<int> vaccines; //stores vaccines for each region

                //simulation variables
                int infectedArea;
                int infectiousPeriod;
                int contactRate;
                int totalVaccines;

    public:
                Database();
                
                //set private variables
                void setRegionPopulation(vector<int> regionPopulation);
                void setAdjacencyList(vector<vector<int>> adjacencyList);

                //returns the number of regions
                int getNumberOfRegions();

                //returns the number of people in a region
                int getNumberOfPeople(int region);

                //set and get status of a person
                void setStatus(int region, int index, char status);
                char getStatus(int region, int index);

                //updates infectious status of people
                void updateInfection();

                //returns the number of adjacent regions for a region in the adjacency list
                int getNumberOfAdjacencies(int region);

                //returns the id of an adjacent region
                //region is the region on the adjacency list
                //index is the position in the adjacency list
                int getAdjacency(int region, int index);

                //set and get vaccines for a given region
                void setVaccines(int region, int amount);
                int getVaccines(int region);

                //set simulation variables
                void setSimulationVariables(int area, int period, int rate, int vac);

                //get simulation variables
                int getInfectedArea();
                int getInfectiousPeriod();
                int getContactRate();
                int getVaccines();
};

#endif