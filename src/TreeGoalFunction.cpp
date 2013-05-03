#pragma once
#include<math.h>
#include<vector>
#include<string>

#include "GoalFunction.h"
#include "ErrorHandler.h"
using namespace std;


double CTreeGoalFunction::evaluate(const vector<double> &x) const{
	return root->get_value(x);
}

// Recursively build a tree of operations form string. We consider [left, right] substring
// and scan it level by level.
// @param 's': string with the function;
// @param 'level': Level of scaning. Can be {1,2,3}. 1 means current area should be considered 
// to have +\- as last operation here. 2 for *,\ and 3 for unaru operations.
// @param 'left': left index of area in the string, which we consider now
// @param 'right': right index of area in the string, which we consider now
// Return: pointer to the root of a tree
AbstractTreeNode* CTreeGoalFunction::build(string &s, int level, int left, int right){
	if(left > right ) 
		return NULL; // This area is empty

	// Node to represent current part of the string
	AbstractTreeNode* current;

	// Current depth of brakets
	int braket_depth = 0;
	bool any = false;

	// If current part of a string is name (treate it as new variable)
	bool isname = true;
	// If curretn part of the string is number
	bool isnumber = true;
	// Position of floating point (if has one)
	int floating_point = -1;
	
	// Check if curetna area is number or var name:
	for(int i = left; i <= right && (isname || isnumber); i++){
		if(isname && !isalpha(s[i])){
			isname = false;
		}
		if(isnumber && !isdigit(s[i]) && s[i] != '.'){
			isnumber = false;
		}
		if(isnumber && s[i] == '.'){
			floating_point = i;
		}
	}
	if(isname){
		string varName = s.substr(left, right - left + 1);
		
		if(varNumbers.find(varName) == varNumbers.end()){
			// If this name appears at first
			varNames.push_back(varName);
			varNumbers.insert(make_pair(varNames[varNames.size()-1], varNames.size()-1));
			current = new CTreeNodeVariable(varNames.size()-1);
		}else{
			// We already have such name
			current = new CTreeNodeVariable(varNumbers[varName]);
		}
		
		// This node is a leaf, so simply return it
		return current;
	}


	if(isnumber){
		// Store value in temp
		double temp = 0;
		// Current radix
		double base = 1;

		if(floating_point == -1){
			for(int i = right; i >= left; i--){
				temp += (s[i]-'0')*base;
				base *= 10;
			}
		}else{
			base = 0.1;
			for(int i = floating_point+1; i <= right; i++){
				temp += (s[i]-'0')*base;
				base /= 10;
			}
			base = 1;
			for(int i = floating_point-1; i >= left; i--){
				temp += (s[i]-'0')*base;
				base *= 10;
			}
		}
		current = new CTreeNodeConstant(temp);

		// This node is a leaf, so simply return it
		return current;
	}

	switch(level){
		 case 1: 
			 // Try to find +\- operation, and check whether it is last operation 
			 // here (braket_depth == 0)
			 for(int i = right; i >= left; i--){
				 if((s[i] == '+' || s[i] == '-') && !braket_depth){
					 // Recursively build binary operation node
					 current = new CTreeNodeBinaryOperation(
						 ((s[i] == '+')? CTreeNodeBinaryOperation::BinaryOperation::Plus
									  : CTreeNodeBinaryOperation::BinaryOperation::Minus),
						 build(s,1, left, i-1),
						 build(s,1, i+1, right));
					 any = true;
					 break;
				 }
				 if(s[i] == '(') braket_depth++;
				 if(s[i] == ')') braket_depth--;
			 }

			 // If we haven't find any last +\- operation here, scan with next level
			 if(!any)
				 build(s,2,left,right);
			 else
				 return current;
			 
		 break;
		 case 2:
			 for(int i = right; i >= left; i--){
				 if((s[i] == '*' || s[i] == '/') && !braket_depth){
					 current = new CTreeNodeBinaryOperation(
						 (s[i] == '*')? CTreeNodeBinaryOperation::BinaryOperation::Mult
									  : CTreeNodeBinaryOperation::BinaryOperation::Div,
						 build(s,2, left, i-1),
						 build(s,2, i+1, right));
					 any = true;
					 break;
				 }
				 if(s[i] == '(') braket_depth++;
				 if(s[i] == ')') braket_depth--;
			 }
			 if(!any)
				 build(s,3,left,right);
			 else
				 return current;
			 
		 break;
		 case 3:
			 if(s[left] == '(' && s[right] == ')'){
				current = build(s,1,left+1, right-1);
			 }else{

				 if(s[right] != ')')
					  throw UserException("Неверная запись выражения");

				 string unary_oper = "";
				 int i = left;
				 for(; i <= right && s[i] != '('; i++){			 
					 unary_oper += s[i];
				 }
				 if(s[i] != '(')
					  throw UserException("Неверная запись выражения");

				 CTreeNodeUnaryOperation::UnaryOperation type;
				 if(unary_oper == "sin")
					 type = CTreeNodeUnaryOperation::UnaryOperation::Sin;
				 else if(unary_oper == "cos")
					 type = CTreeNodeUnaryOperation::UnaryOperation::Cos;
				 else if(unary_oper == "tan")
					 type = CTreeNodeUnaryOperation::UnaryOperation::Tan;
				 else if(unary_oper == "exp")
					 type = CTreeNodeUnaryOperation::UnaryOperation::Exp;
				 else
					  throw UserException("Неверная операция в записи выражения");
				 
				 current = new CTreeNodeUnaryOperation( type, build(s, 1, i+1, right-1)); 
				 return current;
			 }
			 
		 break;
	 }
 }

// String Parser
CTreeGoalFunction::CTreeGoalFunction(string s){
	for(int i = 0; i < s.size(); i++){
		if(!isalpha(s[i]) && !isdigit(s[i])){
			if(s[i] == ' ' || s[i] == '\n' || s[i] == '\r' || s[i] == '\t'){
				s.erase(i,1);
			}else if(s[i] != '(' && s[i] != ')' && s[i] != '.' && s[i] != '-' && s[i] != '+' && s[i] != '*' && s[i] != '/' && s[i] != ','){
				throw UserException("Задана некорректная функция (найдены недопустимые символы)");
			}
		}
	}
	root = build(s,1,0,s.size()-1);
}

int CTreeGoalFunction::getVarNumber(string varName) const {
	if(varNumbers.find(varName) == varNumbers.end()){
		string msg = "Переменной с именем \"";
		msg.append(varName);
		msg.append("\" не существует.");
		throw UserException(msg);
	}else
		return varNumbers.find(varName)->second;
}

string CTreeGoalFunction::getVarName(int i) const {
	if(i < getVariablesCount())
		return varNames[i];
	else
		throw UserException("Номер переменной не корректен");
}

int CTreeGoalFunction::getVariablesCount() const {
	return varNames.size();
}