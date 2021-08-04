#include <iostream>
#include <vector>
#include "Database.h"
#include "Input.h"
#include "Output.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
using namespace std;

void random(Database &d)
{

vector<int> newpop;
vector<int> vac;
vector<int> randpop;
int totalvac = 0;

int regions = d.getNumberOfRegions();


for(int i = 0; i < regions; i++)
{
	newpop.push_back(d.getNumberOfPeople(i+1));
	randpop.push_back(d.getNumberOfPeople(i+1));
	totalvac += d.getNumberOfPeople(i+1);
}


//cout << endl << totalvac << endl;

/*
cout << "Old Region\n";
for(int i = 0; i < regions; i++)
{
	cout << "Number in region" << i + 1 << ": " << newpop[i] << endl;
}
*/


std::random_device rd;
std::default_random_engine rng(rd());
shuffle(randpop.begin(), randpop.end(),rng);



cout << endl;
cout << "Total Vax: " << totalvac << endl;
for(int i = 0; i < regions; i++)
{
	d.setVaccines(i+1,randpop[i]);
	totalvac = totalvac - randpop[i];
	cout << "Vax in region " << i+1 << ": " << d.getVaccines(i+1) <<  "  Vax Left: " << totalvac << endl;
}

}
