

#include <stdio.h>
#include <time.h>
#include <math.h>



#define STOP     10                      /* number of time intervals       */
#define sqr(x)   ((x) * (x))
#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */

static long seed = DEFAULT;    /* seed is the state of the generator        */


double Random()
/* ---------------------------------------------------------------------
 * Random is a Lehmer generator that returns a pseudo-random real number
 * uniformly distributed between 0.0 and 1.0.  The period is (m - 1)
 * where m = 2,147,483,647 amd the smallest and largest possible values
 * are (1 / m) and 1 - (1 / m) respectively.
 * ---------------------------------------------------------------------
 */
{
    const long Q = MODULUS / MULTIPLIER;
    const long R = MODULUS % MULTIPLIER;
    long temp = 0;
    long t;
    
    
    t = MULTIPLIER * (seed % Q) - R * (seed / Q);
    if (t > 0)
        seed = t;
    else
        seed = t + MODULUS;
    
    return ((double) seed / MODULUS);
}


void PutSeed(long x)
/* -------------------------------------------------------------------
 * Use this (optional) procedure to initialize or reset the state of
 * the random number generator according to the following conventions:
 *    if x > 0 then x is the initial seed (unless too large)
 *    if x < 0 then the initial seed is obtained from the system clock
 *    if x = 0 then the initial seed is to be supplied interactively
 * --------------------------------------------------------------------
 */
{
    char ok = 0;
    
    if (x > 0L)
        x = x % MODULUS;                          /* correct if x is too large  */
    if (x < 0L)
        x = ((unsigned long) time((time_t *) NULL)) % MODULUS;
    if (x == 0L)
        while (!ok) {
            printf("\nEnter a positive integer seed (9 digits or less) >> ");
            scanf("%ld", &x);
            ok = (0L < x) && (x < MODULUS);
            if (!ok)
                printf("\nInput out of range ... try again\n");
        }
    
    seed = x;
    
}


void GetSeed(long *x)
/* --------------------------------------------------------------------
 * Use this (optional) procedure to get the current state of the random
 * number generator.
 * --------------------------------------------------------------------
 */
{
    *x = seed;
}


void TestRandom(void)
/* -------------------------------------------------------------------
 * Use this (optional) procedure to test for a correct implementation.
 * -------------------------------------------------------------------
 */
{
    long   i;
    long   x;
    double u;
    
    PutSeed(1);                                /* set initial state to 1 */
    for(i = 0; i < 10000; i++)
        u = Random();
    GetSeed(&x);                               /* get the new state      */
    if (x == CHECK)
        printf("\n The implementation of Random is correct\n");
    else
        printf("\n\a ERROR - the implementation of Random is not correct\n");
}


long Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
    return (a + (long) ((b - a + 1) * Random()));
}

double Uniform(double a, double b)
/* ===========================================================
 * Returns a uniformly distributed real number between a and b.
 * NOTE: use a < b
 * ===========================================================
 */
{
    return (a + (b - a) * Random());
}

double Exponential(double m)
/* =========================================================
 * Returns an exponentially distributed positive real number.
 * NOTE: use m > 0.0
 * =========================================================
 */
{
    //printf("    mu - %6.2f\n",m);
    return (-m * log(1.0 - Random()));
}


int main(void){
    long index = 0,n = 0;
    double a,x;
    while(index<STOP){
    index++;
        a = 0.0;
        n = 0;
    while(a < 50){
        printf("%6.2f\n",a);
        if((a>=0)&&(a<10)){
            x = 1;
        }
        else if((a>=10)&&(a<20)){
            x = (a/10);
        }
        else if((a>=20)&&(a<30)){
            x = 2;
        }
        else if((a>=30)&&(a<40)){
            x = (50 - a)/10;
        }
        else if((a>=40)&&(a<50)){
            x = 1;
        }
        
       /* if((a>=0)&&(a<15)){
            x = 1;
        }
        else if((a>=15)&&(a<35)){
            x = 2;
        }
        else if((a>=35)&&(a<50)){
            x = 1;
        }*/
        
        //printf("x is %6.2f   index - %ld",x,index);
        a += Exponential(1/x);
        n++;
    }
    }
    //printf("ind%ld",index);
}
