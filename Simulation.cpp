/*
 *Salman Farooq
 *CSCE 2110
 * Group 2
 * Project 2 - Contagion
 * The Simulation function takes in the database and strategy type and runs through a
 * for-loop which checks to see if certain criteria are met before infected an area
 * or surrouding areas.
 * 
 * Criteria 1:		If there are no Susceptible peple do nothing
 * Criteria 2:		If there are Susceptible people AND the number of Infected people
 * 					mulitplied by the contact rate is over the number of Susceptible 
 * 					people, infect all Susceptible people. This criteria also infects
 * 					an adjacent node if it has not already been infected AND has 
 * 					Susceptible people.
 * Criteria 3:		Infect the Susceptible population by the Infected population 
 * 					multiplied by the contact rate.
 * 
 * At the end of each loop, the current database is displayed and the documentation
 * within Output is updated. The loop stops when there are no more infected people
 * in the entire region
*/

#include "Input.h"
#include "Database.h"
#include "Output.h"
#include <string>
#include <vector>

using namespace std;

void Simulation (Database &d, Output &out, string strategy) {
	//Output out;
	int infectedArea = d.getInfectedArea();			
	vector <int> infectedAreas;						//vector to hold other areas that become infected
	infectedAreas.push_back(d.getInfectedArea());

	int infectedPeriod = d.getInfectiousPeriod();
	int contactRate	= d.getContactRate();
	int numInfected	= 1; //starts at 1
	int days = 0;
	int counter = 0;	//counter used to keep count of infections as they happen in a loop
	int k = 0;
	bool end = false;

	vector <int> S; S.push_back(0);		//used to keep track of health states
	vector <int> I; I.push_back(0);		//while loop runs through 
	vector <int> R; R.push_back(0);		//each area

	//filling vector with vaccine placement for testing purposes only
	//closeness distribution vaccine placement
	/*
	d.setVaccines(2, 6000);
	d.setVaccines(4, 10000);
	d.setVaccines(5, 2000);
	d.setVaccines(6, 5000);
	d.setVaccines(8, 2500);
	*/
	//random distribution vaccine placement
	/*
	d.setVaccines(1, 5000);
	d.setVaccines(2, 6000);
	d.setVaccines(3, 4000);
	d.setVaccines(4, 10000);
	d.setVaccines(5, 500);
	*/
	//equal distribution
	/*
	d.setVaccines(1, 2938);
	d.setVaccines(2, 2938);
	d.setVaccines(3, 2938);
	d.setVaccines(4, 2938);
	d.setVaccines(5, 2000);
	d.setVaccines(6, 2937);
	d.setVaccines(7, 2937);
	d.setVaccines(8, 2937);
	d.setVaccines(9, 2937);
	*/

	//fills database with vaccinated population. keep this loop in final code
	for(int i = 1; i <= d.getNumberOfRegions(); i++) {
		for(int j = 0; j < d.getVaccines(i); j++) {
			d.setStatus(i, j, 'V');
		}
	}

	//set infected area with 1 infected person
	for(int i = 0; i < d.getNumberOfPeople(infectedArea); i++) {
		if(d.getStatus(infectedArea, i) == 'S') {
			d.setStatus(infectedArea, i, 'I');
			break;
		}
	}
  out.setStrategy(strategy);
	out.document(d, strategy, days);
	out.printRegions(d, days);		//prints Day 0
	days++; 
	d.updateInfection();

	for(int b = 0; b < d.getNumberOfPeople(infectedArea); b++) {
		if(d.getStatus(infectedArea, b) == 'S') {S.at(0)++;}
		if(d.getStatus(infectedArea, b) == 'I') {I.at(0)++;}
		if(d.getStatus(infectedArea, b) == 'R') {R.at(0)++;}
	}

	//begin simulation
	do{

		for(int i = 0; i < infectedAreas.size(); i++) {
			infectedArea = infectedAreas.at(i);		//finds infected area
		
		if(S.at(i) == 0) {}

		if((S.at(i) != 0) && (S.at(i) < I.at(i) * contactRate)) {
			numInfected = S.at(i);
			counter = 0;
			k = 0;
			while(counter != numInfected){
				if(d.getStatus(infectedArea, k) == 'S') {
					d.setStatus(infectedArea, k, 'I');
					counter++;
				}
				k++;
			}

			//begin infection of adjacent nodes
			int priorInfectedArea = 0;
			for(int i = 0; i < d.getNumberOfAdjacencies(infectedArea); i++) {
				int adj = d.getAdjacency(infectedArea, i);
				for(int k = 0; k < infectedAreas.size(); k++) {
					if(adj == infectedAreas.at(k)) {
						priorInfectedArea++; 	//checks if the area has been infected before
					}
				}
				if(priorInfectedArea == 0) {
					for(int j = 0; j < d.getNumberOfPeople(adj); j++){
						if(d.getStatus(adj, j) == 'S') {
							d.setStatus(adj, j, 'I');
							infectedAreas.push_back(adj);
							S.push_back(0);
							I.push_back(0);
							R.push_back(0);
							break;
						}		
					}
				}
			}
		
		}
		
		//this loop is before infection period begins
		else {
			if (S.at(i) > 0) {
				if(S.at(i) < (I.at(i) * contactRate)) {
					numInfected = S.at(i);
					counter = 0;
					k = 0;
					while(counter != numInfected){
						if(d.getStatus(infectedArea, k) == 'S') {
							d.setStatus(infectedArea, k, 'I');
							counter++;
						}
						k++;
					}
				}
				else{
				numInfected = (I.at(i) * contactRate);
				counter = 0;
				k = 0;
					while(counter != numInfected){
						if(d.getStatus(infectedArea, k) == 'S') {
							d.setStatus(infectedArea, k, 'I');
							counter++;
						}
						k++;
					}
				}
			}
		}
		//sets health states for everyone in infected area BEFORE update infection function
		S.at(i) = 0; I.at(i) = 0; R.at(i) = 0; 
		for(int b = 0; b < d.getNumberOfPeople(infectedArea); b++) {
			if(d.getStatus(infectedArea, b) == 'S') {S.at(i)++;}
			if(d.getStatus(infectedArea, b) == 'I') {I.at(i)++;}
			if(d.getStatus(infectedArea, b) == 'R') {R.at(i)++;}
		}	
	}

	out.printRegions(d, days);
  cout << endl;
	days++;

	if(out.isInfectious(d) == false) {
		end = true;
	}
	
	out.document(d, strategy, days-1);
	d.updateInfection();
	
	}while(end != true);
  out.totalRecovered(d, strategy);

};