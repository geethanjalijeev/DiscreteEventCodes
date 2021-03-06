
/* -------------------------------------------------------------------------
 * This program simulates a simple (s,S) inventory system using demand read  
 * from a text file.  Backlogging is permitted and there is no delivery lag.
 * The output statistics are the average demand and order per time interval
 * (they should be equal), the relative frequency of setup and the time
 * averaged held (+) and short (-) inventory levels.
 *
 * NOTE: use 0 <= MINIMUM < MAXIMUM, i.e., 0 <= s < S.
 *
 * Name              : sis1.c  (Simple Inventory System, version 1)
 * Authors           : Steve Park & Dave Geyer 
 * Language          : ANSI C 
 * Latest Revision   : 8-20-97 
 * Compile with      : gcc sis1.c
 * ------------------------------------------------------------------------- 
*/

#include <stdio.h>  
#include <stdlib.h>                      

#define FILENAME  "sis1.dat"            /* input data file                */
#define MINIMUM   20                    /* 's' inventory policy parameter */
#define MAXIMUM   80                    /* 'S' inventory policy parameter */
#define sqr(x)    ((x) * (x))

/* ======================== */
   long GetDemand(FILE *fp)            
/* ======================== */
{
  long d;

  fscanf(fp, "%ld\n", &d);
  return (d);
}

/* ============== */
   int main(void)
/* ============== */
{
  FILE *fp;                                /* input data file         */
  long index     = 100;                      /* time interval index     */
  long i         = 0;
  int x;
  int y;
  long front;
  long rear;
  long inventory = MAXIMUM;                /* current inventory level */
  long demand;                             /* amount of demand        */
  long order;                              /* amount of order         */
  long dcircular[index]; 
  
  struct vals {                                 /* sum of ...              */
    double setup;                          /*   setup instances       */
    double holding;                        /*   inventory held (+)    */
    double shortage;                       /*   inventory short (-)   */
    double order;                          /*   orders                */
    double demand;                         /*   demands               */
  };

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }
  
  while(!feof(fp)){
     dcircular[i] = GetDemand(fp);
     i++;
     
  }
fclose(fp);

  for(x = 0; x<10; x++){
    struct vals sum = { 0.0, 0.0, 0.0, 0.0, 0.0 };
    
     rear = (rand() % index);
    
     front = ((rear+1)%index);
     
     do {
        
    if (inventory < MINIMUM) {             /* place an order          */
      order         = MAXIMUM - inventory;
      sum.setup++;
      sum.order    += order;
    }
    else                                   /* no order                 */
      order         = 0;                   
    inventory      += order;               /* there is no delivery lag */
    demand          = dcircular[front];   
    sum.demand     += demand;
    if (inventory > demand) 
      sum.holding  += (inventory - 0.5 * demand);
    else {
      sum.holding  += sqr(inventory) / (2.0 * demand);
      sum.shortage += sqr(demand - inventory) / (2.0 * demand);
    }
    inventory      -= demand;
    front = ((front + 1)%index);
  } while (!(front==((rear+1)%index)));
  
  if (inventory < MAXIMUM) {               /* force the final inventory to */
    order           = MAXIMUM - inventory; /* match the initial inventory  */
    sum.setup++;
    sum.order      += order;
    inventory      += order;
  }

  printf("\nfor %ld time intervals ", index);
  printf("with an average demand of %6.2f\n", sum.demand / index);
  printf("and policy parameters (s, S) = (%d, %d)\n\n", MINIMUM, MAXIMUM);
  printf("   average order ............ = %6.2f\n", sum.order / index);
  printf("   setup frequency .......... = %6.2f\n", sum.setup / index);
  printf("   average holding level .... = %6.2f\n", sum.holding / index);
  printf("   average shortage level ... = %6.2f\n", sum.shortage / index);

  }

  return (0);
}
