#pragma once
#include<math.h>
#include<vector>
#include<string>

#include "TreeNode.h"

// Интерфейс функции
class IGoalFunction{
public:
	double virtual evaluate(const vector<double> &x) const =0;
	// Получить имя переменной по номеру
	string virtual getVarName(int i) const =0;
	int virtual getVarNumber(string s) const =0;
	int virtual getVariablesCount() const =0;
};

class CTreeGoalFunction: public IGoalFunction{
protected:
	vector<string> varNames;
	map<string, int> varNumbers;
private:
	AbstractTreeNode *build(string &s, int level, int left, int right);
	AbstractTreeNode *root;
public:	
	CTreeGoalFunction(string s);
	double evaluate(const vector<double> &x) const;
	int getVarNumber(string s) const;
	string getVarName(int i) const;
	int getVariablesCount() const;
	
};

class CDummyGoalFunction: public IGoalFunction{
public:
	CDummyGoalFunction();
	double evaluate(const vector<double> &x) const;
	string getVarName(int i) const;
	int getVarNumber(string s) const;
	int getVariablesCount() const;
};