#pragma once
#include "ErrorHandler.h"



OperationException::OperationException(string msg){
	errorDescription = "������ ����������: " + msg;	
	cout << errorDescription << endl;
}

UserException::UserException(string msg){
	errorDescription = "������ ������ � ����������: " + msg;	
	cout << errorDescription << endl;
}