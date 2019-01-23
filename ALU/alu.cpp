#include "alu.h"

void alu :: alu_method(){

	//Variables to store signals
	sc_int<8> signal_a;
	sc_int<8> signal_b;
	sc_int<8> signal_out;
	
	signal_a = a_in.read();
	signal_b = b_in.read();
	
	//if op code = 0 then subtraction
	if(op_in.read() == 0){
		cout << "Op Code = 0" << endl;
		signal_out = signal_a - signal_b;
		dout.write(signal_out); 
		//dout.write(signal_a - signal_b);
		cout << "A " << signal_a.to_string() << endl;
		cout << "B " << signal_b.to_string() << endl;
		cout << "Dout " << signal_out.to_string() << endl;
	}
	
	//if op code = 1 then addition	
	if(op_in.read() == 1){
		cout << "Op Code = 1" << endl;
		signal_out = signal_a + signal_b; 
		dout.write(signal_out);
		//dout.write(signal_a - signal_b);
		cout << "A " << signal_a.to_string() << endl;
		cout << "B " << signal_b.to_string() << endl;
		cout << "Dout " << signal_out.to_string() << endl;
	}
	
}


