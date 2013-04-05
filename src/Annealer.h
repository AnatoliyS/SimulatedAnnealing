#pragma once
#include<math.h>
#include<vector>
#include<time.h>

#include "GoalFunction.h"
using namespace std;

class CAnnealer{
private:
	
	IGoalFunction *function;

	 // ����������� ������������ (���-�� ����������)
	 int D;
	 vector<double> A;
	 // ������ ���������� ������� (����������)
	 vector<double> X, nextX;
	 // ������ �����������
	 vector<pair<double, double> > constraits;
	  // ������ ����� ��� ������ �� ����������
	 vector<double> V;
	 // �������: �������, �� ����. ����, ����������
	 double currentE, nextE, minE;
	 // �����������
	 double t, originT;
	 // ��������� �������� � ����������� ��������������
	 double alpha;
	 
	 double default_low_bound, default_high_bound;
	 double annealStep;

	 // ��� ���������
	 int maxSteps;
	 int maxStepsPerGeneration;
	 double minTemperature;

	 // ������������� ��������� �������� �� [-1,1] � �������������� ����
	 double rand_cauchi(double t);

	 // ������������� ����� �����
	 void Generate(const vector<double> &X, vector<double> &nextX, double t);

	 double h(double dE, double t);

	 // ����� ��������� ����������� (�� ����)
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