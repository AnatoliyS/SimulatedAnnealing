#pragma once
#define _USE_MATH_DEFINES
#include "Annealer.h"
#include "GoalFunction.h"
#include "ErrorHandler.h"
#include <limits.h>
#include <cstdlib>
#include <cmath>
using namespace std;

CAnnealer::CAnnealer(){
	// TODO: write functions to set this parameters manualy
	default_low_bound = -1e30;
	default_high_bound = 1e30;
	minTemperature = 1e-30;
	maxStepsPerGeneration = 10000;
	maxSteps = 1000;
	annealStep = 0.1;
	originT = 0.03;	
}

void CAnnealer::setGoalFunction(IGoalFunction *f){
	function = f;
	
	// Get dimensions count
	D = function->getVariablesCount();

	// Apply default constraits
	for(int i = 0; i < D; i++)
		constraits.push_back(make_pair(default_low_bound, default_high_bound));

	// Set initial state to random possible state
	A = vector<double>(D,0);
	X = vector<double>(D, ((rand()%2==0)?-1:1)*min(fabs(default_high_bound),fabs(default_low_bound))*rand()/ RAND_MAX);
	nextX = vector<double>(D, 0);
	V = vector<double>(D, annealStep );
	
	// Calc curretn energy
	currentE = function->evaluate(X);
	minE = currentE;
	A = X;
}

// Get random variable with Cauchi distribution on [-1,1]
double CAnnealer::rand_cauchi(double t){
	double a = double( rand() ) / RAND_MAX;
	return t*tan(M_PI*a - M_PI/2.0);
}

void CAnnealer::Generate(const vector<double> &X, vector<double> &nextX, double t){
	for(int i = 0; i < D; i++){
			 nextX[i] = X[i] + V[i]*rand_cauchi(t)/t;
			 while(nextX[i] > constraits[i].second || nextX[i] < constraits[i].first){
				nextX[i] = X[i] + V[i]*rand_cauchi(t)/t;		
			 }
		 }	  
}

double CAnnealer::h(double dE, double t){
	return exp(-dE/t);
}

double CAnnealer::T(int k){
	return originT / pow(double(k), double(1)/D);
}

// Simulating of Annealing
void CAnnealer::minimize(){
	srand(clock());

	int steps;

	for(int i = 1; i <= maxSteps; i++){
		t = T(i);
		if(t < minTemperature) break;
		
		if(currentE < minE){
			minE = currentE;
			A = X;
		}
		steps = 0;
		while(1){
			if(steps > maxStepsPerGeneration) break;
			Generate(X, nextX, t);
			
			nextE = function->evaluate(nextX);

			alpha = double( rand() ) / RAND_MAX;

			if(alpha < h(nextE - currentE, t)){
				X = nextX;
				currentE = nextE;
				break;
			}
			steps++;
		}
	}

}


vector<pair<string, double> > CAnnealer::get_minimum_point(){
	vector<pair<string, double> > answer;
	
	for(int i = 0; i < D; i++){
		answer.push_back(make_pair(function->getVarName(i), A[i]));
	}
	return answer;
}


void CAnnealer::setCondition(string varName, double low, double high){
	try{
		int n = function->getVarNumber(varName);
		constraits[n] = make_pair(low, high);
		X[n] = ((rand()%2==0)?-1:1)*min(fabs(low), fabs(high))*(double(rand())/ RAND_MAX);
	}catch(UserException e){
		throw UserException("Can't put constrait on variable (maybe you made a typo in var name?)");
	}
}

void CAnnealer::setDefaultCondition(double low, double high){	
	default_low_bound = low;
	default_high_bound = high;
}

double CAnnealer::get_minimum(){
	return minE;
}