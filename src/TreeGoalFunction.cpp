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

AbstractTreeNode* CTreeGoalFunction::build(string &s, int level, int left, int right){
	if(left > right ) 
		return NULL;

	AbstractTreeNode* current;

	int braket_depth = 0;
	bool any = false;

	bool isname = true;
	bool isnumber = true;
	int floating_point = -1;
	
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
			varNames.push_back(varName);
			varNumbers.insert(make_pair(varNames[varNames.size()-1], varNames.size()-1));
			current = new CTreeNodeVariable(varNames.size()-1);
		}else{
			current = new CTreeNodeVariable(varNumbers[varName]);
		}
		
		return current;
	}
	if(isnumber){
		double temp = 0;
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
		return current;
	}

	switch(level){
		 case 1:
			 for(int i = right; i >= left; i--){
				 if((s[i] == '+' || s[i] == '-') && !braket_depth){
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