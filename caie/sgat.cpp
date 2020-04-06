/**************************************************
  SGA - Simple Genetic Algorithm
  ------------------------------
  Sin Bowl minimization 2012
    - most recent bug fixes: 09/1012 by John Johnson
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
#define CHROM_LENGTH    20    // binary string length of each individual
#define PMUT            0.03  // probability of flipping each bit
#define MAX_GEN         5000   // GA stops after this many generations
#define GEN_REP         1     // report is generated at these intervals
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
int    decode(int index, int start);
void   getpreviousbest();
double evaluate(int valueX, int valueY);
double convRange(int raw);
int    flip(double prob);
void   statistics();
void   elite();
void   finalreport();

struct individual
{
  int valueX;
  int valueY;
  unsigned char string[CHROM_LENGTH*2];
  double fitness;
};

struct individual pool[POPULATION_SIZE];
struct individual new_pool[POPULATION_SIZE];
struct individual beststring, verybest;

int selected[POPULATION_SIZE];
int generations;
int count;


/*********************************************************/
int main()
{
  srand(time(NULL));
  cout.setf(ios::fixed); cout.setf(ios::showpoint); cout.precision(4);
  int i;
  generations = 0;
  if (MAXMIN==-1) verybest.fitness = 999999; else verybest.fitness=-999999;

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
      pool[i].valueX = decode(i, 1);
      pool[i].valueY = decode(i, 20);
      pool[i].fitness = evaluate(pool[i].valueX, pool[i].valueY);
    }

    if (ELITE==1)
      elite();

    if (generations % GEN_REP == 0)
      statistics();

  } while (++generations < MAX_GEN);

  finalreport();
  return(0);
}
/*
-13.9637 59.9237 -60.69077
-39.2103 59.9763 -60.9393

*/

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
  if ((MAXMIN*beststring.fitness) > (MAXMIN*evaluate(decode(0, 1), decode(0, 16))))
  {
    pool[0].fitness = beststring.fitness;
    pool[0].valueX = beststring.valueX;
    pool[0].valueY = beststring.valueY;
    for (int j=0; j<CHROM_LENGTH * 2; j++)
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
    for (int j=0; j<CHROM_LENGTH*2; j++ )
      pool[i].string[j] = flip(0.5);
    pool[i].valueX = decode(i, 1);
    pool[i].valueY = decode(i, 1);
    pool[i].fitness = evaluate(pool[i].valueX, pool[i].valueY);
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
      beststring.valueX = pool[i].valueX;
      beststring.valueY = pool[i].valueY;
      for (int j=0; j<CHROM_LENGTH*2; j++)
        beststring.string[j] = pool[i].string[j];
      beststring.fitness = pool[i].fitness;
    }
  }   

  if (generations % GEN_REP == 0)
  {
    cout << endl << "   Best string: ";
    for (int j=0;j<CHROM_LENGTH*2;j++)
      cout << (int) beststring.string[j];
    cout << " valueX: " << convRange(beststring.valueX);
    cout << " valueY: " << convRange(beststring.valueY);
    cout << " fitness: " << beststring.fitness << endl; 
  }

  if ((MAXMIN*beststring.fitness) > (MAXMIN*verybest.fitness))
  {
    verybest.valueX = beststring.valueX;
    verybest.valueY = beststring.valueY;
    for (int j=0; j<CHROM_LENGTH*2; j++)
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
  site = (int) (fracrand()*CHROM_LENGTH*2);
  for (i=0; i<CHROM_LENGTH*2; i++)
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
    for (j=0; j<CHROM_LENGTH*2; j++)
      if (flip(PMUT)==1)
        pool[i].string[j] = ~new_pool[i].string[j] & 0x01;
      else
        pool[i].string[j] = new_pool[i].string[j] & 0x01;
  }
}

/*********************************************************
    Convert bitstring to positive integer
**********************************************************/
int decode(int index, int start)
{
  int value = 0;
  start--;
  
  for (int i=0; i<CHROM_LENGTH; i++)
    value += (int) pow(2.0,(double)i) * pool[index].string[(((CHROM_LENGTH*2)-1) - (19 - start))-i];
  return (value);
}

/*********************************************************
   F(X) =sinx +cosy
*********************************************************/
double evaluate(int valueX, int valueY)
{
  double x = convRange(valueX);
  double y = convRange(valueY);
  //double z = (double) ((d * d) - (f * f)) + (500 * sin(d));//(0.1*(fabs(d))-sin(f));
 //  double z = (double) (sin(x)+ cos(y));
 //double z =(double) ((x*cos(pow(x,2) * sin(y))));
   double g = (double) (x * cos(x*x) * (sin(y)));
count++;
  return(g);
}

/*********************************************************
 Convert positive integer to desired floating point range.
 Problem-specific - change for different string lengths
**********************************************************/
double convRange(int raw)
{
  double outval = ((((double)raw)/1048575.0)*20.0)-10;
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
  cout << endl << "\n\tX\ty\t\tz\t\tnew str\tx\ty";
  for (i=0; i<POPULATION_SIZE; i++)
  {
    cout << endl << "   ";
    cout << convRange(pool[i].valueX)<<"\t"<<convRange(pool[i].valueY)<<"\t"<<pool[i].fitness << "\t";
    for (j=0; j<CHROM_LENGTH*2; j++)
      cout << (int) pool[i].string[j];
    cout << "\t" << convRange(decode(i, 1))<< "\t" << convRange(decode(i, 20));
  }
  cout << endl;
}

/*********************************************************
    Report printed at the very end of execution
**********************************************************/
void finalreport()
{
int count=0;
  cout << "=======================================================" << endl;
  cout << "Best result over all generations:" << endl;
  for (int j=0; j<CHROM_LENGTH*2; j++){
    cout << (int) verybest.string[j];
	//count=j;
	}
  cout << endl;
  cout << "Decoded valueX = " << convRange(verybest.valueX);
  cout << "  Decoded valueY = " << convRange(verybest.valueY);
  cout << "  Fitness = " << verybest.fitness << endl;
  //cout << "  Generation = " << count<< endl;
}

