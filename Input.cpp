#include "Input.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//constructer
Input::Input()
{
    //files
    configFile = "";
    populationFile = "";
    regionFile = "";

    //simulation variables
    infectedArea = 0;
    infectiousPeriod = 0;
    contactRate = 0;
    vaccines = 0;
}

//initializes private variables
void Input::getConfig()
{
    //getting config file name from user
    cout << "Config file: ";
    cin >> configFile;
    cout << endl;

    /*
     * reading config file
     */
    ifstream config;

    //opening config file
    config.open(configFile);

    //testing if file is open
    if(!(config.is_open()))
    {
        cout << "config file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    //reading config file
    string line = "";
    int lineCount = 0;
    while(config.good())
    {
        getline(config, line);

        //initializing file names and simulation variables
        switch(lineCount)
        {
            case 0: //population file
                    populationFile = line.substr(line.find(":") + 1);
                    break;

            case 1: //region file
                    regionFile = line.substr(line.find(":") + 1);
                    break;

            case 3: //infected area
                    infectedArea = stoi(line.substr(line.find(":") + 1));
                    break;

            case 4: //infectious period
                    infectiousPeriod = stoi(line.substr(line.find(":") + 1));
                    break;

            case 5: //contact rate
                    contactRate = stoi(line.substr(line.find(":") + 1));
                    break;

            case 6: //vaccines
                    vaccines = stoi(line.substr(line.find(":") + 1));
                    break;

            default:
                    line = "";
                    break;
        }

        line = "";
        lineCount++;
    }

    config.close();

    /*
     * reading population file
     */
    ifstream population;

    //opening population file
    population.open(populationFile);

    //testing if file is open
    if(!(population.is_open()))
    {
        cout << "population file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    //reading population file
    line = "";
    while(population.good())
    {
        getline(population, line);

        //exits file at empty line
        if(line.length() == 0)
        {
            break;
        }

        regionPopulation.push_back(stoi(line.substr(line.find(":") + 1)));

        line = "";
    }

    population.close();

    /*
     * reading region file
     */
    ifstream region;

    //opening region file
    region.open(regionFile);

    //testing if file is open
    if(!(region.is_open()))
    {
        cout << "region file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    //reading region file
    line = "";
    lineCount = 0;
    while(region.good())
    {
        getline(region, line);

        //skips first line of region file
        if(lineCount == 0)
        {
            line = "";
            getline(region, line);
            lineCount++;
        }

        //exits file at empty line
        if(line.length() == 0)
        {
            break;
        }

        //deletes first comma and everything behind first comma
        line = line.substr(line.find(",") + 1);

        //region specific adjacency list
        vector<int> adjacencyLine;

        //reads and converts adjacency matrix line to adjacency line
        for(int i = 0; i < (line.length()); i += 2)
        {
            if(line[i] == '1')
            {
                adjacencyLine.push_back((i / 2) + 1);
            }
        }
        adjacencyList.push_back(adjacencyLine);

        lineCount++;
    }
}

//prints population of all regions
void Input::printPopulation()
{
    for(int i = 0; i < regionPopulation.size(); i++)
    {
        cout << (i + 1) << " " << regionPopulation[i] << endl;
    }
}

//prints adjacency list version of region file
void Input::printAdjacencyList()
{
    for(int r = 0; r < adjacencyList.size(); r++)
    {
        cout << (r + 1) << ": ";
        for(int c = 0; c < adjacencyList[r].size(); c++)
        {
            cout << adjacencyList[r][c] << " ";
        }
        cout << endl;
    }
}

//get region population vector
vector<int> Input::getRegionPopulation()
{
    return regionPopulation;
}

//get adjacency list
vector<vector<int>> Input::getAdjacencyList()
{
    return adjacencyList;
}

//get infected area
int Input::passInfectedArea()
{
    return infectedArea;
}

//get infectious period
int Input::passInfectiousPeriod()
{
    return infectiousPeriod;
}

//get contact rate
int Input::passContactRate()
{
    return contactRate;
}

//get vaccines
int Input::passVaccines()
{
    return vaccines;
}