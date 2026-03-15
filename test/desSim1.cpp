#include "iostreams"
#include "string"

struct event{
   int time; //global time
   int delay; //delay
   int alpha;  //time interval within time unit
   string src; //event src , for debug
   function dstCall;        //callback function
}

