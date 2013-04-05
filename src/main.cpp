#include<math.h>
#include<vector>
#include<string>
#include<iostream>
#include <iomanip>

#include "Annealer.h"
#include "GoalFunction.h"
#include "ErrorHandler.h"
using namespace std;

int main(){
	//freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
	setlocale(LC_ALL, "Russian");

	cout << "Введите функцию:" << endl;
	string s;
	cin >> s;

	try{
		CAnnealer* Annealer = new CAnnealer();
		Annealer->setDefaultCondition(-200.0, 200.0);

		CTreeGoalFunction f = CTreeGoalFunction(s);

		// Примеры функций:
		//CTreeGoalFunction f = CTreeGoalFunction("x*x+y*y+z*z+a*a+b*b+c*c-0.1*cos(3*x)-0.2*cos(2*y)-0.3*cos(5*z)-0.5*cos(a)-0.1*cos(b)-0.2*cos(c)");
		//CTreeGoalFunction f = CTreeGoalFunction("sin(x - 3.14/4) *cos(x)");
		//CTreeGoalFunction f = CTreeGoalFunction("cos(x*cos(x))");
		//CTreeGoalFunction f = CTreeGoalFunction("2*x*x*x+x*y*y+5*x*x+y*y-1");
		//CTreeGoalFunction f = CTreeGoalFunction("x*x");

		// Функция другая по алгоритму вычисления
		//CDummyGoalFunction f2 = CDummyGoalFunction();

	
		Annealer->setGoalFunction(&f);
		
		cout << "Введите ограничения на переменные в формате - имя нижн.граница верхн.граница (или * для начала работы алгоритма)" << endl;
		while(1){
			cin >> s;
			if(s == "*") break;
			double low, high;
			cin >> low  >> high;
			Annealer->setCondition(s, low, high);
		}
		// Можно задавать ограничения на переменные
		//Annealer->setCondition("x", 10, 200);
		//Annealer->setCondition("y", 0, 200);

		Annealer->minimize();
		vector<pair<string, double> > res = Annealer->get_minimum_point();
	

		cout << "Минимальное значение = " << fixed << setprecision(6) << Annealer->get_minimum() << " В точке:" << endl;
		for(vector<pair<string, double> >::iterator it = res.begin(); it != res.end(); it++){
			cout << it->first << " = " << it->second << endl;
		}


	}catch(exception e){
		cout << "Программма завершена аварийно";
		system("pause");
		return 1;
	};

	system("pause");
	
	return 0;
}