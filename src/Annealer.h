#pragma once
#include<math.h>
#include<vector>
#include<time.h>

#include "GoalFunction.h"
using namespace std;

class CAnnealer{
private:
	
	IGoalFunction *function;

	 // Размерность пространства (кол-во переменных)
	 int D;
	 vector<double> A;
	 // Вектор параметров системы (переменных)
	 vector<double> X, nextX;
	 // Вектор ограничений
	 vector<pair<double, double> > constraits;
	  // Вектор шагов для каждой из переменных
	 vector<double> V;
	 // Энергия: текущая, на след. шаге, минимальня
	 double currentE, nextE, minE;
	 // Температура
	 double t, originT;
	 // Случайная величина с равномерным распределением
	 double alpha;
	 
	 double default_low_bound, default_high_bound;
	 double annealStep;

	 // Шаг алгоритма
	 int maxSteps;
	 int maxStepsPerGeneration;
	 double minTemperature;

	 // Сгенерировать случайную величину на [-1,1] с распределением Коши
	 double rand_cauchi(double t);

	 // Сгенерировать новую точку
	 void Generate(const vector<double> &X, vector<double> &nextX, double t);

	 double h(double dE, double t);

	 // Закон изменения температуры (по Коши)
	 double T(int k);

public:
	CAnnealer();
	void setGoalFunction(IGoalFunction *f);
	void minimize();
	void setCondition(string, double low, double high);
	void setDefaultCondition(double low, double high);
	double get_minimum();
	vector<pair<string, double> > get_minimum_point();

	// Parameters
	void setMinTemperature(double T);
	void setMaxStepsCount(int steps);
	void setMaxStepsPerGeneration(int steps);
	void setOriginTemperature(double T);
};