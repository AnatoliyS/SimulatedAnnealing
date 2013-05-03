#pragma once
#include<math.h>
#include<vector>
#include<time.h>

#include "GoalFunction.h"
using namespace std;

///
/// Class that implements Simulated Annealing algorithm
/// and find the min of any given IGoalFunction
///
class CAnnealer{
private:
	 // ptr to IGoalFunction to find minimum
	 IGoalFunction *function;

	 // Space dimension count (the number of variables in function)
	 int D;
	 // Vector of variable values, which represents the point of minimum 
	 vector<double> A;
	 // Vector of current variable values, and offered values for next step
	 vector<double> X, nextX;
	 // Vector of constraits
	 vector<pair<double, double> > constraits;
	  // Vector of maximum possible delta for each variable
	 vector<double> V;
	 // "Energy"(Min of function): current, on the next step, global minimum of energy
	 double currentE, nextE, minE;
	 // "Temperature": current, origin
	 double t, originT;
	 // Randomly distributed variable (0..1)
	 double alpha;
	 
	 // Default constraits
	 double default_low_bound, default_high_bound;
	 double annealStep;

	 // To eliminate algorithm:
	 int maxSteps;
	 int maxStepsPerGeneration;
	 double minTemperature;

	 // Generate random variable on [-1,1] with Cauchi distribution
	 double rand_cauchi(double t);

	 // Generate new state
	 void Generate(const vector<double> &X, vector<double> &nextX, double t);
	 
	 // Probablistic parameter
	 double h(double dE, double t);

	 // Law of temperature decreasing from step number
	 double T(int k);

public:
	CAnnealer();
	void setGoalFunction(IGoalFunction *f);
	void minimize();
	void setCondition(string, double low, double high);
	void setDefaultCondition(double low, double high);
	double get_minimum();
	vector<pair<string, double> > get_minimum_point();

	// Parameters
	void setMinTemperature(double T);
	void setMaxStepsCount(int steps);
	void setMaxStepsPerGeneration(int steps);
	void setOriginTemperature(double T);
};