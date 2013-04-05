#pragma once
#include "ErrorHandler.h"



OperationException::OperationException(string msg){
	errorDescription = "Ошибка вычислений: " + msg;	
	cout << errorDescription << endl;
}

UserException::UserException(string msg){
	errorDescription = "Ошибка работы с программой: " + msg;	
	cout << errorDescription << endl;
}