#pragma once
#include<math.h>
#include<vector>
#include<string>

#include "GoalFunction.h"
using namespace std;

double CDummyGoalFunction::evaluate(const vector<double> &X) const{
	double res = X[0]*X[0] + X[1]*X[1] + X[2]*X[2] + X[3]*X[3] + X[4]*X[4] + X[5]*X[5] 
				- 0.1*cos(3*X[0]) - 0.2*cos(2*X[1]) - 0.3*cos(5*X[2]) - 0.5*cos(X[3]) - 0.1*cos(X[4]) - 0.2*cos(X[5]);
	//double res = sin(X[0]-3.14/4)*cos(X[0]);
	return res;
}

string CDummyGoalFunction::getVarName(int i)const{
	string res = "X[";
	char *c = itoa(i, new char[10], 10);
	res.append(c);
	res.append("]");
	return res;
}

int CDummyGoalFunction::getVarNumber(string s)const{
	return 0;
}

CDummyGoalFunction::CDummyGoalFunction(){
};

int CDummyGoalFunction::getVariablesCount()const{
	return 6;
}