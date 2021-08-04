#include "Database.h"
#include <vector>

using namespace std;

Database::Database()
{
    infectedArea = 0;
    infectiousPeriod = 0;
    contactRate = 0;
    totalVaccines = 0;
}

//set people vector
void Database::setRegionPopulation(vector<int> regionPopulation)
{
    //number of regions
    int regions = regionPopulation.size();

    pair<char, int> status = {'S', 0};

    vector<pair<char, int>> region;

    for(int i = 0; i < regions; i++)
    {
        for(int j = 0; j < regionPopulation[i]; j++)
        {
            region.push_back(status);
        }

        people.push_back(region);
        region.clear();

        vaccines.push_back(0); //allocates space for vaccines vector
    }
}

//set adjacency list
void Database::setAdjacencyList(vector<vector<int>> a)
{
    int regions = a.size(); //number of regions
    int adjacencies; //number of adjacent regions
    vector<int> adjacencyLine; //vector of adjacent regions

    //populates adjacency list;
    for(int i = 0; i < regions; i++)
    {
        adjacencies = a[i].size();

        for(int j = 0; j < adjacencies; j++)
        {
            adjacencyLine.push_back(a[i][j]);
        }

        adjacencyList.push_back(adjacencyLine);
        adjacencyLine.clear();
    }
}

//returns the number of regions
int Database::getNumberOfRegions()
{
    return adjacencyList.size();
}

//returns the number of people in a region
int Database::getNumberOfPeople(int region)
{
    return people[region - 1].size();
}

//set status of a person
void Database::setStatus(int region, int index, char status)
{
    people[region - 1][index].first = status;
}

//get status of a person
char Database::getStatus(int region, int index)
{
    return people[region - 1][index].first;
}

//updates infectious status of people
void Database::updateInfection()
{
    for(int i = 0; i < people.size(); i++)
    {
        for(int j = 0; j < people[i].size(); j++)
        {
            if(people[i][j].first == 'I')
            {
                people[i][j].second++;
            }

            if(people[i][j].second >= infectiousPeriod)
            {
                people[i][j].first = 'R';
                people[i][j].second = 0;
            }
        }
    }
}

//returns the number of adjacent regions for a region in the adjacency list
int Database::getNumberOfAdjacencies(int region)
{
    return adjacencyList[region - 1].size();
}

//returns the id of an adjacent region
//region is the region on the adjacency list
//index is the position in the adjacency list
int Database::getAdjacency(int region, int index)
{
    return adjacencyList[region - 1][index];
}

//set vaccines for a given region
void Database::setVaccines(int region, int amount)
{
    vaccines[region - 1] = amount;
}

//get vaccines for a given region
int Database::getVaccines(int region)
{
    return vaccines[region - 1];
}

//set simulation variables
void Database::setSimulationVariables(int area, int period, int rate, int vac)
{
    infectedArea = area;
    infectiousPeriod = period;
    contactRate = rate;
    totalVaccines = vac;
}

//get infected area
int Database::getInfectedArea()
{
    return infectedArea;
}

//get infected period
int Database::getInfectiousPeriod()
{
    return infectiousPeriod;
}

//get contact rate
int Database::getContactRate()
{
    return contactRate;
}

//get total vaccines
int Database::getVaccines()
{
    return totalVaccines;
}