#pragma once
#include<math.h>
#include<vector>
#include<string>
#include<map>
using namespace std;

// Не интерфейс, а просто класс
class AbstractTreeNode{
protected:
	AbstractTreeNode *left, *right;
public:
	double virtual get_value(const vector<double> &x) =0;
	void virtual print(int) =0;
};

class CTreeNodeBinaryOperation: public AbstractTreeNode{
public:
	static enum BinaryOperation{
		Plus, Minus, Mult, Div
	};
private:
	BinaryOperation type;
public:
	CTreeNodeBinaryOperation(BinaryOperation t, AbstractTreeNode *l, AbstractTreeNode *r);
	double get_value(const vector<double> &x);
	void print(int level);
};

class CTreeNodeUnaryOperation: public AbstractTreeNode{
public:
	static enum UnaryOperation{
		Sin, Cos, Exp, Tan
	};
private:
	UnaryOperation type;
public:
	CTreeNodeUnaryOperation(UnaryOperation t, AbstractTreeNode *l);
	double get_value(const vector<double> &x);
	void print(int level);
};


class CTreeNodeConstant: public AbstractTreeNode{
private:
	double value;
public:
	CTreeNodeConstant(double v);
	double get_value(const vector<double> &x);
	void print(int level);
};

class CTreeNodeVariable: public AbstractTreeNode{
private:
	int number;
public:
	CTreeNodeVariable(int n);
	double get_value(const vector<double> &x);
	void print(int level);
};