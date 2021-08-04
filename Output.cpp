#include "Output.h"
#include <iostream>
#include <string>

using namespace std;

Output::Output()
{
    
}

//prints a chart of the regions' states
void Output::printRegions(Database d, int day)
{
    //prints current day
    cout << "Day: " << day << endl;

    //number of regions
    int regions = d.getNumberOfRegions();

    //status counts
    int s = 0, i = 0, r = 0, v = 0;

    for(int j = 1; j <= regions; j++)
    {
        for(int k = 0; k < d.getNumberOfPeople(j); k++)
        {
            //counts all statuses in a region
            switch(d.getStatus(j,k))
            {
                case 'S':
                            s++;
                            break;
                
                case 'I':
                            i++;
                            break;

                case 'R':
                            r++;
                            break;

                case 'V':
                            v++;
                            break;
            }
        }

        //(region id)  pop: #  S: #  I: #  R: #  V: #
        cout << (j) << "\tPOP: " << d.getNumberOfPeople(j) << "\tS: " << s << "\t\tI: " << i << "\tR: " << r << "\t\tV: " << v << endl;
        
        //resets status counts
        s = 0;
        i = 0;
        r = 0;
        v = 0;
    }
}

//checks if any person is infectious
bool Output::isInfectious(Database d)
{
    for(int i = 1; i <= d.getNumberOfRegions(); i++)
    {
        for(int j = 0; j < d.getNumberOfPeople(i); j++)
        {
            if(d.getStatus(i,j) == 'I')
            {
                return true;
            }
        }
    }

    return false;
}

//returns the number of infected people
int Output::numberOf(Database d, char state)
{
    int total = 0;

    for(int i = 1; i <= d.getNumberOfRegions(); i++)
    {
        for(int j = 0; j < d.getNumberOfPeople(i); j++)
        {
            if(d.getStatus(i,j) == state)
            {
                total++;
            }
        }
    }

    return total;
}

//creates a key for Infections
//prints current strategy
void Output::setStrategy(string strategy)
{
    //map value
    vector<int> item;

    item.push_back(1); //peak infected
    item.push_back(0); //day of peak infection
    item.push_back(0); //number of days simulation ran
    item.push_back(0); //total number of people infected

    Infections.insert(pair<string, vector<int>>(strategy, item));

    cout << strategy << endl;
}

//keeps track of peak infections
void Output::document(Database d, string strategy, int day)
{
    int infectedNow = numberOf(d, 'I');

    if(Infections.at(strategy)[0] < infectedNow)
    {
        Infections.at(strategy)[0] = infectedNow;
        Infections.at(strategy)[1] = day;
    }

    Infections.at(strategy)[2] = day;
}

//counts all recovered people
void Output::totalRecovered(Database d, string strategy)
{
    Infections.at(strategy)[3] = numberOf(d, 'R');
}

//prints conclusion
void Output::printAnalysis()
{
    for(auto item: Infections)
    {
        cout << "Using the "<< item.first << " distribution method, the peak number of infected was "<< item.second[0] << " on day "<< item.second[1] << "." << endl;

        cout << "The outbreak ended on day "<< item.second[2] << " and the total number of infected individuals was "<< item.second[3] <<"." << endl << endl;
    }
}