#include "iostreams"
#include "string"
#include "queue"

struct event{
   int time; //global time
   int delay; //delay
   int alpha;  //time interval within time unit
   string src; //event src , for debug
   int (*fptr_cb)();        //callback function
}

class scheduler(){
	public:
		int add_event(event & ev){
			queue.add(ev);
			return 0; //if no err
		}
		int pop_event (){
			event = queue.pop(); 
			//if no err, add error catch
			return 0;
		}

	private:
		priority_queue queue; 

}

class cpu (){
	public:
	    int mem_wr(){
        	return 0; 
	    }
	    int mem_rd(){
        	return 0; 
	    }
	private:
	    int addr;
	    int op1;
	    int op2;
	    int result;
}

class mem(){
	public:
	int mem_wr(){
	    mem_data[addr]= wr_data;	
	    return 0;//if no err
		}
	int mem_rd(){
	    rd_data = mem_data[addr];	
	    return 0;//if no err
		}

	private:
	 array<int> mem_data; //dynamic array

}
