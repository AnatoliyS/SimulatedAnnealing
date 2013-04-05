#pragma once
#include "TreeNode.h"
#include "ErrorHandler.h"

double CTreeNodeUnaryOperation::get_value(const vector<double> &x){
	if(!left)
		throw OperationException("Ошибка построения узла. Строка содержит ошибку.");
	switch(type){
		case Cos:				
			return cos(left->get_value(x));
		case Sin:
			return sin(left->get_value(x));
		case Exp:
			return exp(left->get_value(x));
		case Tan:
			return tan(left->get_value(x));
		break;
	}
}

CTreeNodeUnaryOperation::CTreeNodeUnaryOperation(UnaryOperation t, AbstractTreeNode *l){
	if(!left)
		throw OperationException("Ошибка построения узла. Строка содержит ошибку.");
	left = l;
	right = NULL;
	type = t;
}


void CTreeNodeUnaryOperation::print(int level){
		left->print(level+3);
		char* s = new char[5];
		switch(type){
			case 0: s="sin\0"; break;
			case 1: s="cos\0"; break;
			case 2: s="exp\0"; break;
		}
		printf("%*s\n", level+1, s);
		
	}