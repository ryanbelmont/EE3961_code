/*
 * Ryan Belmont
 * 11/25/2021
 * belmo057
 * function definitions for the circle_buffer.h library
 */

#include "xc.h"
#include "circle_buffer.h"

# define BUFSIZE 256 // buffersize is 10

int adc_buffer[BUFSIZE]; // initialize the buffer
int front = 0; // front pointer.
                // dont need a back pointer as it overwrites the old data, but takes
                // the average of all relevant data. 

    // function to create the buffer
    void initBuffer()
    {
        int i;
        for(i=0;i<BUFSIZE;i++)
        {
            adc_buffer[i] = 0; // initialize as 0
        }
    }
    
    // function to put new data in buffer
    // inputs new data (newValue)
    void putVal(int newValue)
    {
        adc_buffer[front++] = newValue; // puts the value 
        
        if(front >= BUFSIZE) // rollover 
        {
            front = 0;
        }
    }
    
   
    // function grab the average of the data in the buffer
    // return average value
    int getAvg()
    {
        int sum = 0;
        int avg = 0;
        int i = 0;
        for(i=0; i<BUFSIZE; i++) // for size of buffer
        {
            sum = sum+adc_buffer[i]; // add to sum
            
        }
        avg = sum/BUFSIZE; // find average value
        return avg;
    }
    