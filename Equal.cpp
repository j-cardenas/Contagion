#include <iostream>
#include <vector>
#include "Database.h"
#include "Input.h"
#include "Output.h"
#include <bits/stdc++.h>

using namespace std;

void equal(Database &d)
{

vector<int> pop;		//declaration of local population vectors
vector<int> pop2;
//vector<int> vac;
int totalvac = d.getVaccines();
					//declaration and initialization of totalvac, # of regions, and avg population
int regions = d.getNumberOfRegions();
int avg = 0;

for(int i = 0; i < regions; i++)	//filling population vectors
{
	pop.push_back(d.getNumberOfPeople(i+1));
	pop2.push_back(d.getNumberOfPeople(i+1));
}

avg = totalvac/regions;		//finding average of population in all regions
//int counter = 0;
//int avg2 = 0;

cout << endl;
//test//cout << "Total Vax: " << totalvac << endl;
//test//cout << "AVG Vax in Region: " << avg << endl;
for(int i = 0; i < regions; i++)			//for loop and nested if statements determining which given action should be taken place
{							//depending upon population, avg, and totalvac left after each iteration
	if(pop[i] >= avg && totalvac > 0)
	{
		d.setVaccines(i+1,avg);
		totalvac = totalvac - avg;
	}
	else if(pop[i] < avg && totalvac > 0)
	{
		d.setVaccines(i+1,pop[i]);
		totalvac = totalvac - pop[i];
		//test//counter++;
	}
	else
	{
		d.setVaccines(i+1,0);
	}
	//test//cout << "Current Vax in region " << i+1 << ": " <<  d.getVaccines(i+1) << " Vax Left: " << totalvac << endl;
}
/*//test
if(totalvac > 0)
{
	avg2 = totalvac/counter;
	sort(pop.begin(),pop.end());
	for(int i = 0; i < counter; i++)
	{
		d.setVaccines(i+1,pop[i]+avg);
	}
}
*/
}

