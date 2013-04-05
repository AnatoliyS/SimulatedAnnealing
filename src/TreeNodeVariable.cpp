#pragma once
#include "TreeNode.h"
#include "ErrorHandler.h"

double CTreeNodeVariable::get_value(const vector<double> &x){
	return x[number];
}

CTreeNodeVariable::CTreeNodeVariable(int n){
	left = right = NULL;
	number = n;
}

void CTreeNodeVariable::print(int level){			
	printf("%*s$%d\n", level-1, "", number);		
}