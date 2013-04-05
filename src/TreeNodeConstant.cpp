#pragma once
#include "TreeNode.h"
#include "ErrorHandler.h"

double CTreeNodeConstant::get_value(const vector<double> &x){
	return value;
}

CTreeNodeConstant::CTreeNodeConstant(double v){
	left = right = NULL;
	value = v;
}

void CTreeNodeConstant::print(int level){		
	printf("%*s$%.3lf\n", level-1, "", value);		
}