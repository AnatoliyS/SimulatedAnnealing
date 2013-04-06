Simulated Annealing
===================

Class, that implements [Simulated Annealing](http://en.wikipedia.org/wiki/Simulated_annealing/) algorithm 
for finding global minimum of various function

- CAnnealer - class of annealer;
- IGoalFunction - interface represents function;
- CTreeGoalFunction - realisation of IGoalFunction, that builds a tree of operations from string representation of function


Usage
------------------
See Main.cpp for details

	CTreeGoalFunction f = CTreeGoalFunction("cos(x*cos(x))");
	CTreeGoalFunction f = CTreeGoalFunction("2*x*x*x+x*y*y+5*x*x+y*y-1");
	
	Annealer->setGoalFunction(&f);
	
	Annealer->setCondition("x", -5, 10);
	
	Annealer->minimize();

