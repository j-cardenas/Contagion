#ifndef OUTPUT_H
#define OUTPUT_H

#include "Database.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Output
{
    private:
                //key is the distribution stategy
                //first value is peak people infected
                //second value is day of peak infection
                //third value is number of days simulation ran
                //fourth value is total number of people infected
                map<string, vector<int>> Infections;

    public:
                Output();
                
                //prints a chart of the regions' states
                void printRegions(Database d, int day);

                //checks if any person is infectious
                bool isInfectious(Database d);

                //returns the number of people of a given state
                int numberOf(Database d, char state);

                //creates a key for Infections
                //prints current strategy
                void setStrategy(string strategy);

                //keeps track of peak infections
                void document(Database d, string strategy, int day);

                //counts all recovered people
                void totalRecovered(Database d, string strategy);

                //prints conclusion
                void printAnalysis();

};

#endif