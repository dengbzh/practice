#include<iostream>
#include<stdio.h>
#define MAX_COST 100000.0
#define GCOST 1.0
#define BCOST 5.0
#define OK  0
#define ERR -1
#define MIN(x,y) ((x)<(y) ?(x):(y))


int maxLeftPackage(int numOfPackage,int numOfSlot,int slotNum)
{
    return (numOfSlot - slotNum) > numOfPackage ? numOfPackage : (numOfSlot - slotNum);
}
int lestLeftPackage(int numOfPackage,int slotNum)
{
    return slotNum >= numOfPackage ? 0 : (numOfPackage - slotNum);
}
void initMetric(int len,double *stateMetric)
{
    //int len = (numOfSlot*numOfPackage) << 1;
    while(len--)
    {
      stateMetric[len] = MAX_COST;
    }
}
void PrintState(int len,double *stateMetric)
{
	printf("\n");
    for (size_t i = 0; i < len; i++) {
      /* code */
      printf("%f ", stateMetric[i]);
    }
    printf("\n");
}
int constructor(int numOfState,int numOfSlot,double Pg, double *stateMetric)
{
    if(numOfSlot < ((numOfState>>1)-1) || numOfSlot <= 0 || numOfState <= 0)
      return ERR;
    if(Pg < 0 || Pg > 1)
      return ERR;
    if(stateMetric == NULL)
      return ERR;

	initMetric(numOfSlot*numOfState, stateMetric);
	int left;
	double Pb = 1.0 - Pg;
	double cost;
	double temp;
    double *oldState = stateMetric + (numOfSlot-1)*numOfState;
    double *newState = oldState - numOfState;


	//PrintState(numOfSlot*numOfState, stateMetric);

    for(int i = 0; i < numOfState; ++i)
    {
        int left = i/2;
        if(left == 0)
        {
            oldState[i] = 0.0;

        }else if(left == 1)
        {
            if(i%2 == 0)
            {//in good condition
              oldState[i] = GCOST;
            }
            else
            {
              oldState[i] = BCOST;
            }

        }
        else
        {
            break;
        }
    }
	//PrintState(numOfState, oldState);
    for(int i = numOfSlot - 2; i >= 0; --i)
    {
        int maxleft = maxLeftPackage((numOfState>>1)-1,numOfSlot,i);
        int lestleft = lestLeftPackage((numOfState>>1)-1,i);
        for(int j = 0; j < numOfState; ++j)
        {
            left = j/2;
            cost = MAX_COST;
            if(left < maxleft)
            {//think about transmisstion
                if(left < lestleft)
                {
                    //newState[j] = MAX_COST;
                    continue;
                }
                else
                {
                    if(left == 0)
                    {//no need to tramsmit
                      cost = 0.0;
                    }
                    else
                    {
                      if(j%2 == 0)
                      {//in a good channel best stratige is transmisstion
                        cost = oldState[(left-1)*2]*Pg + oldState[left*2-1]*Pb + GCOST;
                      }
                      else
                      {//in a bad channel
                        //cost of no transmisstion
                        cost = oldState[left*2]*Pg + oldState[left*2+1]*Pb;
                        //cost of transmisstion
                        temp = oldState[(left-1)*2]*Pg + oldState[left*2-1]*Pb + BCOST;

                        cost = MIN(cost,temp);
                      }
                    }
                }
            }
            else if(left == maxleft)
            {//must tramsmit
              if(j%2 == 0)
              {
                cost= oldState[(left-1)*2]*Pg + oldState[left*2-1]*Pb + GCOST;
              }
              else
              {
                cost = oldState[(left-1)*2]*Pg + oldState[left*2-1]*Pb + BCOST;
              }
            }
            else
            {//cost max
               break;
            }
            newState[j] = MIN(cost,newState[j]);
        }
       // PrintState(numOfState,newState);
        oldState -= numOfState;
        newState -= numOfState;
    }
    return OK;
}
double  makedesision(int numOfState,int numOfSlot,int *action,int *channel,double *stateMetric,double Pg)
{
    int start_s = (numOfState -1)>>1;
    double Pb = 1.0 - Pg;
    double *nextState = stateMetric + numOfState;
    double cost = 0.0;
    for(int i = 0; i < numOfSlot; ++i)
    {
  		if (start_s > 0)
  		{
          if(channel[i] == 1)
          {//good channel
    				action[i] = 1;
    				cost += GCOST;
    				start_s -= 1;
          }
          else if(i != numOfSlot-1)
          {
            double notSent = nextState[start_s*2]*Pg + nextState[start_s*2+1]*Pb;
            double send =  nextState[(start_s-1)*2]*Pg + nextState[start_s*2-1]*Pb + BCOST;
            if(send > notSent)
            {//not send
              action[i] = 0;
            }
            else
            {//send
              action[i] = 1;
              start_s--;
              cost += BCOST;
            }
          }
		  else
		  {
			  action[i] = 1;
			  start_s--;
			  cost += BCOST;
		  }
  		}
  		else
  		{
  			action[i] = 0;
  		}
        nextState += numOfState;
    }
	return cost;
}

int main()
{
  int numOfSlot = 10;
  int numOfPackage = 5;
  double Pg = 0.7;
  int *action = new int[numOfSlot];
  int numOfState = (numOfPackage + 1) << 1;
  double *stateMetric =  new double[numOfSlot*numOfState];
  int *channel = new int[numOfSlot];
  for(int i = 0; i < numOfSlot; ++i)
  {
	  int q = rand();
      if(rand()%10 >= 7)
      {
        channel[i] = 0;
      }
      else
      {
        channel[i] = 1;
      }
  }

  if(constructor(numOfState,numOfSlot,Pg, stateMetric) == OK)
  {
      double cost = makedesision(numOfState,numOfSlot,action,channel,stateMetric,Pg);

	  printf("channel condition: ");
	  for (int i = 0; i < numOfSlot; i++) {
		  /* code */
		  printf("%d ", channel[i]);
	  }
	  printf("\n");
      printf("stratige: ");
      for (int i = 0; i < numOfSlot; i++) {
        /* code */
        printf("%d ",action[i]);
      }
      printf("\n");
	  printf("Total comsumption:%f\n", cost);
  }
  else
  {
    printf("Fail to find the solution!!!\n");
  }
  return 0;
}
