#pragma once
#include<math.h>
#include<vector>
#include<string>

#include "TreeNode.h"

///
/// Interface for various function
///
class IGoalFunction{
public:
	// Calc function on vector of arguments x
	double virtual evaluate(const vector<double> &x) const =0;
	// Get var name by var number (start from 0)
	string virtual getVarName(int i) const =0;
	// Get var name from var number
	int virtual getVarNumber(string s) const =0;
	int virtual getVariablesCount() const =0;
};

///
/// Realization of IGoalFunction, which build a tree of operations to calc function
///
class CTreeGoalFunction: public IGoalFunction{
protected:
	vector<string> varNames;
	map<string, int> varNumbers;
private:
	// Build a tree of operations
	AbstractTreeNode *build(string &s, int level, int left, int right);
	AbstractTreeNode *root;
public:	
	CTreeGoalFunction(string s);
	double evaluate(const vector<double> &x) const;
	int getVarNumber(string s) const;
	string getVarName(int i) const;
	int getVariablesCount() const;
	
};

///
/// Realization of IGoalFunction, for unit testing
///
class CDummyGoalFunction: public IGoalFunction{
public:
	CDummyGoalFunction();
	double evaluate(const vector<double> &x) const;
	string getVarName(int i) const;
	int getVarNumber(string s) const;
	int getVariablesCount() const;
};