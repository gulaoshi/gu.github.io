/////////////////////////////////////////////////////////////////////////
//  Create threads in Nachos
//

//#include "list.h"
#include "list2.h"
#include "system.h"
#include "synch.h"
//#include "testcase.h"
#include <unistd.h>

// Keep busy for some time. Recommend that t values from 1 to 10
// The unit is approximately 0.1 second
// Do NOT modify this function
void busy_for_some_time(int t)
{
	int j;
	int timetask=0;
	for (j = 0 ; j < 10000000 * t ; j ++)
	{
		timetask++;
	}
	currentThread->Yield();
}

Thread *th1;
Thread *th2;

//wait for the busy thread
//DO NOT modify this function except commenting out one line
void wait_for_busy_thread(int arg)
{
	// Store current thread name to var threadname. Do NOT modify.
	char * threadname = currentThread->getName();

	printf("Hello,my name is %s\n", threadname);

	/* Note: Delete or comment out this line to see a different result. */
        //th1->Join();

	printf("%s ends\n",threadname);
}


void busy_thread(int arg)
{
	// Store current thread name to var threadname. Do NOT modify.
	char * threadname = currentThread->getName();

	printf ("Hello, my name is %s\n", threadname);

	// Project 1 : add your code here


	printf("%s will keep busy for a time slot of %d\n",threadname,arg);
		busy_for_some_time(arg);

	printf ("%s ends\n",threadname);
}

void ThreadTestSimple()
{
    printf("Running ThreadTestSimple: starting 2 threads, Thread2 waits for Thread1 to finish. \n");
    th1 = new Thread("Thread1");
    th1->Fork(busy_thread, 3);

	//Project 1: add your code here
  
    th2 = new Thread("Thread2");
    th2->Fork(wait_for_busy_thread, 1);

}


//project1 changes start here
extern List2 * arguementlist;
//flag=1 if the current word starts with a vow, let thread vow run; 
//flag=0 if the current word starts with a consonant, let thread con run;
//flag=2 if all arguments have been processed.
int flag=-1;
char *word;
void vow(int which)
{
	while(!(arguementlist->IsEmpty()))
	{
		flag=1;
		word=(char *)arguementlist->Remove();
		char c=word[0];
		if(c=='a'||c=='A'||c=='e'||c=='E'||c=='i'||c=='I'||c=='o'||c=='O'||c=='u'||c=='U')
		{
			printf("vow:        %s\n",word);
		}else
		{
			flag=0;
			currentThread->Yield();
		}
	}
	flag=2;
	currentThread->Finish();
}
void con(int which)
{
	while(1)
	{
		if(flag==0)
		{
			printf("con:        %s\n",word);
			currentThread->Yield();
			
		}else if(flag==2)
		{
			currentThread->Finish();
		}else
		{
			currentThread->Yield();
		}
	}
	
		
}
//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------
void
ThreadTest()
{
    printf("Running ThreadTest: starting 2 threads, One prints out all vows, and the other prints out all cons. \n");
    Thread *t1 = new Thread("vow");
    Thread *t2 = new Thread("con");
     
    t1->Fork(vow, 1);
    t2->Fork(con, 2);
}
//project 1 changes end here

