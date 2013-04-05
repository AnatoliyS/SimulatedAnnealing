#pragma once
#include "TreeNode.h"
#include "ErrorHandler.h"

double CTreeNodeBinaryOperation::get_value(const vector<double> &x){
		if(!left || !right)
			throw OperationException("Ошибка вычисления узла. Строка содержит ошибку.");
		switch(type){
			case Plus:
				return left->get_value(x) + right->get_value(x);
			case Minus:				
				return left->get_value(x) - right->get_value(x);
			case Mult:				
				return left->get_value(x) * right->get_value(x);
			case Div:
				double r_value = right->get_value(x);
				if(fabs(r_value) < 1e-9) throw OperationException("Деление на ноль!");
				return left->get_value(x) / r_value;
			break;
		}
	
}


CTreeNodeBinaryOperation::CTreeNodeBinaryOperation(BinaryOperation t, AbstractTreeNode *l, AbstractTreeNode *r){
	if(!left || !right)
		throw OperationException("Ошибка построения узла. Строка содержит ошибку.");
	left = l;
	right = r;
	type = t;
}

void CTreeNodeBinaryOperation::print(int level){
		left->print(level+3);
		char* s = new char[2];
		switch(type){
			case 0: s="+\0"; break;
			case 1: s="-\0"; break;
			case 2: s="*\0"; break;
			case 3: s="/\0"; break;
		}
		printf("%*s\n", level, s);
		right->print(level+3);
	}