#pragma once
#include<math.h>
#include<vector>
#include<string>
#include<map>
using namespace std;

///
/// Class for basic tree node
///
class AbstractTreeNode{
protected:
	AbstractTreeNode *left, *right;
public:
	// Calc value in this node
	double virtual get_value(const vector<double> &x) =0;
	// For debug
	void virtual print(int) =0;
};

///
/// Class for binary operation
///
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

///
/// Class for unary operation (right always points to NULL)
///
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

///
/// Class for constant value
///
class CTreeNodeConstant: public AbstractTreeNode{
private:
	double value;
public:
	CTreeNodeConstant(double v);
	double get_value(const vector<double> &x);
	void print(int level);
};

///
/// Class for variable
///
class CTreeNodeVariable: public AbstractTreeNode{
private:
	int number;
public:
	CTreeNodeVariable(int n);
	double get_value(const vector<double> &x);
	void print(int level);
};