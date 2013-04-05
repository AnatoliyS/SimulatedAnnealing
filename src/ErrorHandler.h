#pragma once
#include<math.h>
#include<iostream>
#include<vector>
#include<string>
#include<exception>

using namespace std;

class OperationException : public exception{
public:
	string errorDescription;
	OperationException(string msg);
};

class UserException : public exception{
public:
	string errorDescription;
	UserException(string msg);
};