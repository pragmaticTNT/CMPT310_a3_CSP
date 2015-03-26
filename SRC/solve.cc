
// Two global variables to count properties discovered by the 
// backtrack routine during its execution. The "checks" variable
// maintains the number of consistency checks performed by the 
// "backtrack" routine. The "count" variable maintains the number 
// of solutions found by the backtrack routine.

// typedef char SOLUTION[100];

// Interface to backtracking routines. The backtracking method 
// used is determined by "method".

void NETWORK::solve(int (NETWORK::*method)(SOLUTION,int,int,int *),SOLUTION solution, int number, int *found)
{
  checks = count = 0;
  method(solution, 1, number, found);
}
