
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

// ********************************************************************
// Type definition for the two types of timer available in the program.
// ********************************************************************
typedef enum type_timer {REAL, VIRTUAL} TIMER_TYPE;

const int VARS = 39;
const int DOMS = VARS; 
const int N    = VARS+1;

typedef char SOLUTION[N];
SOLUTION SOL_1; 

unsigned int checks, count;

// ***********************************************************************
// Data structures to hold the required information.  See the accompanying
// research articles for complete descriptions of the structures.
// ***********************************************************************

int jump_place[N];
int mcl[N][DOMS];
int mbl[N];

// *************************************************************************
// Data structures to hold the required information.  See the accompanying
// research articles for complete descriptions of the structures.  The
// "domains" structure works as follows.  If an entry contains a 0, then the
// value is still allowed.  Otherwise, it contains the variable whose
// instantiation eliminated it.  Note that this data structure has no
// information from preprocessing (which is kept directly in the "C" matrix).
// **************************************************************************
int domains[N][DOMS];
int checking[N][N];


// ************************************************************************
// Data structures to hold the required information.  See the accompanying
// research articles for complete descriptions of the structures.
// ************************************************************************
int conflicts[N][N];


#include "stack.cc"
#include "stack_two.cc"
#include "constraint.cc"
#include "network.cc"
#include "timer.cc"
#include "timer_2.cc"
#include "limit.cc"
#include "process.cc"
#include "show.cc"
#include "sfs.cc"

#include "generate_Q.cc"
#include "generate_R.cc"
#include "generate_S.cc"
#include "solve.cc"
#include "BT.cc"
#include "BJ.cc"
#include "BM.cc"
#include "FC.cc"
#include "CBJ.cc"
#include "BM-BJ.cc"
#include "FC-BJ.cc"
#include "arc.cc"
#include "path.cc"



