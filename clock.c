#include <wiringPi.h>
#include <stdio.h>

#define MODE 0
#define SELECT 1
#define SET 2

unsigned int counter=0;
unsigned int timer=0;

//0 = stopped
//1 = running
int timer_state=0;

//0 = display clock
//1 = display stop watch/timer
//2 = set min
//3 = set hr
int state =0; 

//interrupt functions
void mode_button (void)
{
  //  printf("mode button pressed\n");
  switch (state) //toggle between states
  {
    case 0: //switch to timer
      state=1;
      break;
    case 1: //switch to clock
      state=0;
      break;
    case 2: //switch to set hour
      state=3;
      break;
    case 3: //switch to set min
      state=2;
      break;
  }
}

void select_button(void)
{
  printf("select button pressed\n");
  switch (state)
  {
    case 0: //nothing
      break;
    case 1: //start/stop
      if(timer_state==0)
        timer_state=1;
      else 
        timer_state=0;
      break;
    case 2: //increment min
      //min ++
      break;
    case 3: //increment hr
      //hr ++
      break;
  }
}

void set_button(void)
{
  printf("set button pressed\n");
  switch (state)
  {
    case 0: //set
      state=2;
      break;
    case 1: //Reset
      timer_state=0;
      timer=0;
      break;
    case 2: //exit
      state=0;
      break;
    case 3: //exit
      state=0;
      break;
  }
}

//convert counter to clock format
int display_clock(int counter)
{

  int ms=counter%1000;
  int sec=(counter/1000)%60;
  int min=(counter/60000)%60;
  int hour=(counter/3600000)%24;

  printf("current timer is: %02i:%02i:%02i:%03i\n",hour,min,sec,ms);

  return 0;
}

int main (void)
{
  if (wiringPiSetup()<0)
  {
    fprintf(stderr,"Fail to set up wiringPi");
    return 1;
  }

  //ISR setup
  if ((wiringPiISR(MODE,INT_EDGE_FALLING, &mode_button))<0)
  {
    fprintf(stderr,"fail to set up mode ISR\n");
    return 1;
  }

  if ((wiringPiISR(SELECT,INT_EDGE_FALLING, &select_button))<0)
  {
    fprintf(stderr,"fail to set up select ISR\n");
    return 1;
  }

  if ((wiringPiISR(SET,INT_EDGE_FALLING, &set_button))<0)
  {
    fprintf(stderr,"fail to set up set ISR\n");
    return 1;
  }

  while (1)
  {
    //    delay(1); //add to countere every 1ms
    //    counter++;

    counter=millis();
    delay(1000);
    timer=timer+1000;
    /*if(timer_state==0)
    {
      unsigned int previous=counter;
      unsigned int n=
      if (n>0)
        timer= timer+n;
    }*/

    switch (state)
    {
      case 0: //Display clock
        //        printf("millis accurate time: %i\n",millis());
        //        printf("counter time: %i\n",counter);
        /*        if (counter==millis())
                  {
                  printf("nope\n");
                  printf("counter is: %i\n",counter);
                  printf("milis is: %i\n",millis());
                  }*/

        //        printf("Mode 0\n");
        display_clock(counter);
        display_clock(millis());
        printf("t ");
        display_clock(timer);
        break;
      case 1: //Dispaly stopwatch/timer
        //        printf("Mode 1\n");
        break;
      case 2: //Display set min
        break;
      case 3: //Display set hr
        break;
    }

  }
  return 0;
}
