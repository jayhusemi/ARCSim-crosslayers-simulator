#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct event{
   int time; //global time
   int delay; //delay
   int alpha;  //time interval within time unit
   string src; //event src , for debug
   int (*fptr_cb)();        //callback function
};

class scheduler {
	public:
		int add_event(event & ev){
			queue.add(ev);
			return 0; //if no err
		}
		int pop_event (){
			event ev = queue.pop(); 
			ev.fptr_cb();
			//if no err, add error catch
			return 0;
		}
	   //overwrite event comparator for priority queue
	   operator>(event & x, event &y){
	   if (x.time+x.delay) > (y.time+y.delay) x >y;
	   else x<y;
	   }

	   //run loop
	   int run(){
		   unint_64 g_time=0;
		   unint_64 sim_time;
		   while(g_time++ < sim_time ){
		      if (queue.empty ==0) pop_event();
			   
		   }
	   }

	private:
		priority_queue queue; 

}

class cpu {
	scheduler & sch;
	event ev;
	mem & myMem;
	public:
	    int cpu( scheduler& sch, mem & mem ){
			sch = sch;
			myMem = mem;
		}
	    int mem_wr(){
			ev.time = NOW;
			ev.delay=10;
			ev.alpha=0;
			ev.src="cpu_mem_wr";
			ev.fptr_cb= myMem.mem_wr();
			sch.add_event(ev);
        	return 0; 
	    }
	    int mem_rd(){
			ev.time = NOW;
			ev.delay=10;
			ev.alpha=0;
			ev.src="cpu_mem_wr";
			ev.fptr_cb= myMem.mem_rd();
			sch.add_event(ev);
        	return 0; 
	    }
	private:
	    int addr;
	    int op1;
	    int op2;
	    int result;
}

class mem{
	public:
	int mem_wr(int addr, int wr_data){
	    mem_data[addr]= wr_data;	
	    return 0;//if no err
		}
	int mem_rd(int addr){
	    rd_data = mem_data[addr];	
	    return rd_data;//if no err
		}

	private:
	 array<int> mem_data; //dynamic array

}

void main(){
	mem myMem;
	
	scheduler mySch;
     cpu myCPU(mySch);

	
	myCPU.mem_wr(sch);
	myCPU.mem_rd();
	mySch.run();
	
	
}
