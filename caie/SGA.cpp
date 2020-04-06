/**************************************************
  SGA - Simple Genetic Algorithm
  ------------------------------
  Sin Bowl minimization 2012
    - recent bug fixes:   09/2012 by John Johnson
    - slight mod to rand: 11/2017 by Scott Gordon
  ------------------------------
  SGA Adapted from David Goldberg:
    "Genetic Algorithms in Search, Optimization, and Machine Learning"
     Addison-Wesley, 1989.
  ------------------------------
  Unix version
  Compile with:  g++ sga.c
***************************************************/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
using namespace std;

#define POPULATION_SIZE 20    // population size - number of strings
#define CHROM_LENGTH    40    // binary string length of each individual
#define PMUT            0.05  // probability of flipping each bit
#define MAX_GEN         100 // GA stops after this many generations
#define GEN_REP         5     // report is generated at these intervals
#define ELITE           0     // 1=elitism,  0=no elitism
#define MAXMIN          -1    // -1=minimize, 1=maximize

/***************************************************************
****  random fraction between 0.0 and 1.0                  *****
****************************************************************/
#define fracrand() ((double)rand()/RAND_MAX)

void   initialize_population();
void   crossover(int parent1, int parent2, int child1, int child2);
void   mutation();
void   tselection();
int    decode(int index);
int	   decodey(int index);
void   getpreviousbest();
double evaluate(int x, int y);
double convRange(int raw);
int    flip(double prob);
void   statistics();
void   elite();
void   finalreport();

struct individual
{
  int x,y;
  unsigned char string[CHROM_LENGTH];
  double fitness;
};

struct individual pool[POPULATION_SIZE];
struct individual new_pool[POPULATION_SIZE];
struct individual beststring, verybest;

int selected[POPULATION_SIZE];
int generations;

/*********************************************************/
int main()
{
  cout.setf(ios::fixed); cout.setf(ios::showpoint); cout.precision(4);
  int i;
  generations = 0;
  if (MAXMIN==-1) verybest.fitness = 999999; else verybest.fitness=-999999;

  srand(time(NULL));
  initialize_population();
  generations = 1;

  do
  {
    getpreviousbest();

    /*** SELECTION ***/
    tselection();

    /*** CROSSOVER ***/
    for (i=0; i<POPULATION_SIZE; i=i+2)
      crossover(selected[i],selected[i+1],i,i+1);

    /*** MUTATION ***/
    mutation();

    /*** EVALUATE ***/
    for (i=0; i<POPULATION_SIZE; i++)
    {
      pool[i].x = decode(i);
	  pool[i].y = decodey(i);
      pool[i].fitness = evaluate(pool[i].x,pool[i].y);
    }

    if (ELITE==1)
      elite();

    if (generations % GEN_REP == 0)
      statistics();

  } while (++generations < MAX_GEN);

  finalreport();
  return(0);
}

/*********************************************************
  3-2 Tournament Selection 
**********************************************************/
void tselection()
{ int i;
  for (i=0; i<POPULATION_SIZE; i+=2)
  {
    int r = (int) (fracrand()*POPULATION_SIZE);
    int s = (int) (fracrand()*POPULATION_SIZE);
    int t = (int) (fracrand()*POPULATION_SIZE);

    if ( ((MAXMIN*pool[r].fitness) >= (MAXMIN*pool[s].fitness))
      || ((MAXMIN*pool[r].fitness) >= (MAXMIN*pool[t].fitness)))
    {
      if ((MAXMIN*pool[s].fitness) > (MAXMIN*pool[t].fitness))
        { selected[i] = r; selected[i+1] = s; }
      else
        { selected[i] = r; selected[i+1] = t; }
    }
    else
    {
      if ( ((MAXMIN*pool[s].fitness) >= (MAXMIN*pool[r].fitness))
        || ((MAXMIN*pool[s].fitness) >= (MAXMIN*pool[t].fitness)))
      {
        if ((MAXMIN*pool[r].fitness) > (MAXMIN*pool[t].fitness))
        { selected[i] = s; selected[i+1] = r; }
        else
        { selected[i] = s; selected[i+1] = t; }
      }
      else
      {
        if ( ((MAXMIN*pool[t].fitness) >= (MAXMIN*pool[r].fitness))
          || ((MAXMIN*pool[t].fitness) >= (MAXMIN*pool[s].fitness)))
        {
          if ((MAXMIN*pool[r].fitness) > (MAXMIN*pool[s].fitness))
          { selected[i] = t; selected[i+1] = r; }
          else
          { selected[i] = t; selected[i+1] = s;}
} } } } }

/*********************************************************
  Elitism - copy best string to 0th position of new pool
**********************************************************/
void elite()
{
  if ((MAXMIN*beststring.fitness) > (MAXMIN*evaluate(decode(0),(decodey(0)))))
  {
    pool[0].fitness = beststring.fitness;
    pool[0].x = beststring.x;
	pool[0].y = beststring.y;
    for (int j=0; j<CHROM_LENGTH; j++)
      pool[0].string[j] = beststring.string[j];
  }
}

/*********************************************************
    Initialize pool to random binary values
**********************************************************/
void initialize_population()
{
  for (int i=0; i<POPULATION_SIZE; i++)
  {
    for (int j=0; j<CHROM_LENGTH; j++ )
		pool[i].string[j] = flip(0.5);
	pool[i].x = decode(i);
	pool[i].y = decodey(i);
	pool[i].fitness = evaluate(pool[i].x,pool[i].y);
  }
  statistics();
}

/*************************************************************
  - Determine and display best string from previous generation.
  - Maintain very best string from all runs.
**************************************************************/
void getpreviousbest()
{
  cout.setf(ios::fixed); cout.setf(ios::showpoint); cout.precision(4);

  if (MAXMIN==-1) beststring.fitness=999999; else beststring.fitness=-999999;

  for (int i=0; i<POPULATION_SIZE; i++)
  {
    if ((MAXMIN*pool[i].fitness) > (MAXMIN*beststring.fitness))
    {
      beststring.x = pool[i].x;
	  beststring.y = pool[i].y;
      for (int j=0; j<CHROM_LENGTH; j++)
        beststring.string[j] = pool[i].string[j];
      beststring.fitness = pool[i].fitness;
    }
  }   

  if (generations % GEN_REP == 0)
  {
    cout << endl << "   Best string: ";
    for (int j=0;j<CHROM_LENGTH;j++)
      cout << (int) beststring.string[j];
    cout << " Value: " << convRange(beststring.x) << " " << convRange(beststring.y);
    cout << " Fitness: " << beststring.fitness << endl; 
  }

  if ((MAXMIN*beststring.fitness) > (MAXMIN*verybest.fitness))
  {
    verybest.x = beststring.x;
	verybest.y = beststring.y;
    for (int j=0; j<CHROM_LENGTH; j++)
      verybest.string[j] = beststring.string[j];
    verybest.fitness = beststring.fitness;
  }
}

/*********************************************************
      one-point crossover
**********************************************************/
void crossover (int parent1, int parent2, int child1, int child2)
{
  int i, site;
  site = (int) (fracrand()*CHROM_LENGTH);
  for (i=0; i<CHROM_LENGTH; i++)
  {
    if ((i<=site) || (site==0))
    {
      new_pool[child1].string[i] = pool[parent1].string[i];
      new_pool[child2].string[i] = pool[parent2].string[i];
    }
    else
    {
      new_pool[child1].string[i] = pool[parent2].string[i];
      new_pool[child2].string[i] = pool[parent1].string[i];
    }
  }
}

/*********************************************************
    Bitwise mutation  - also transfers strings to pool
**********************************************************/
void mutation()
{
  int i,j;
  for (i=0; i<POPULATION_SIZE; i++)
  {
    for (j=0; j<CHROM_LENGTH; j++)
      if (flip(PMUT)==1)
        pool[i].string[j] = ~new_pool[i].string[j] & 0x01; 
      else
        pool[i].string[j] = new_pool[i].string[j] & 0x01;
  }
}

/*********************************************************
    Convert bitstring to positive integer
**********************************************************/
int decode(int index){
  int value = 0;
  for (int i=0; i < CHROM_LENGTH/2; i++)
    value += (int) pow(2.0,(double)i) * pool[index].string[(CHROM_LENGTH/2)-1-i];
  return (value);
}

int decodey(int index) {
	int value = 0;
	for (int i = 0; i < CHROM_LENGTH/2; i++) {
		value+= (int) pow(2.0,(double)i) * pool[index].string[CHROM_LENGTH -1 - i];
	}
	return (value);
}

/*********************************************************
   F(X) = sin(y^2) + x^2
*********************************************************/
double evaluate(int index, int index2)
{
  double x = convRange(index);
  double y = convRange(index2);
  double g = (double) (3*sin(pow(y,2)) + cos(pow(x,2)));
  return(g);
}

/*********************************************************
 Convert positive integer to desired floating point range.
 Problem-specific - change for different string lengths
**********************************************************/
double convRange(int raw)
{
  double outval = ((((double)raw)/1048575.0)*50.0)-20.0;
  return(outval);
}

/*********************************************************
    Do a biased coin toss based on a probability
**********************************************************/
int flip(double prob)
{
  return((fracrand()<prob)?1:0);
}

/*********************************************************
    Report printed at each generation
**********************************************************/
void statistics()
{
  int i,j;
  cout.setf(ios::fixed); cout.setf(ios::showpoint); cout.precision(4);

  cout << "\nGENERATION: " << generations << endl << "Selected Strings: ";
  for (i=0; i<POPULATION_SIZE; i++) cout << selected[i] << " ";
  cout << endl << "\n\tX\tY\tf(x)\t\t\tnew_str\t\t\t\tX\tY";
  for (i=0; i<POPULATION_SIZE; i++)
  {
    cout << endl << "   ";
    cout << convRange(pool[i].x) << " || " << convRange(pool[i].y) <<"\t" <<pool[i].fitness << "\t";
    for (j=0; j<CHROM_LENGTH; j++)
      cout << (int) pool[i].string[j];
    cout << "  " << convRange(decode(i)) << "||" << convRange(decodey(i));
  }
  cout << endl;
}

/*********************************************************
    Report printed at the very end of execution
**********************************************************/
void finalreport()
{
  cout << "=======================================================" << endl;
  cout << "Best result over all generations:" << endl;
  for (int j=0; j<CHROM_LENGTH; j++)	
    cout << (int) verybest.string[j];
  cout << endl;
  cout << "Decoded value X = " << convRange(verybest.x) << " Y =  "  << convRange(verybest.y);
  cout << "  Fitness = " << verybest.fitness << endl;
}
