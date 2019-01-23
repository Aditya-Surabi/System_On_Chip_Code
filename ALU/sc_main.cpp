//Testbench driver 

#include <systemc.h>
#include "flipflop.h"
#include "barrelshift.h"
#include "alu.h"

int sc_main(int argc, char* argv[]){
	//Initialize signals for barrel shifter
	sc_trace_file *tf;                  // Create VCD file for tracing
	sc_signal<bool> left_in, right_in;      //Declare signals
	sc_signal<bool> en, left_right;
	sc_signal<sc_int<8> >data_out;
	sc_signal<sc_int<8> > B;
	//alu signals
	//op,output,A	
	sc_signal<sc_int<8> > A;
	sc_signal<sc_int<8> > alu_out;
	sc_signal<bool> op;
	
	

	 sc_clock clk("clk",10,SC_NS,0.5);   //Create a clock signal
	
   	 barrel_shift barrel("barrelshift");            //Create testbench Device Under Test (DUT)
   	 barrel.l_in(left_in);                       // Connect/map the ports to testbench signals
   	 barrel.r_in(right_in);
   	 barrel.clk(clk);
	 barrel.enable(en);
      barrel.left_right(left_right);
	  barrel.din(B);
	 barrel.dout(data_out);
	 
	 //ALU port declaration and initializations
	 alu alu("alu"); // create object
	 alu.a_in(A); 		 // A signal input
	 alu.b_in(data_out); // Barrel Shifter output
	 alu.op_in(op);	 // Op code input
	 alu.clk(clk);		// CLK input
	 alu.dout(alu_out);

       // Create wave file and trace the signals executing
	tf = sc_create_vcd_trace_file("trace_file");
     tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clk, "clk");
	sc_trace(tf, en, "enable");
	sc_trace(tf, op, "opcode");
	sc_trace(tf, A, "A");
	sc_trace(tf, B, "B");
	sc_trace(tf, left_in, "left_data");
	sc_trace(tf, right_in, "right_data");
	sc_trace(tf, left_right, "left_right_signal");
	sc_trace(tf, data_out, "BS_data_out");
	sc_trace(tf, alu_out, "ALU_data_out");
	
	//cout << "\nExecuting 1bit barrel shift example... check .vcd produced"<<endl;

	//start the testbench
	
	//3 Cases
	
	//1) Op = 0, En = 0, l_r = X, Pass Data Through (shifting disabled)
	//2) Op = 1, En = 0, l_r = X, Pass Data Through (shifting disabled)
	//3) Op = 1, En = 1, l_r = 0, Addition, Shift Left
	//4) Op = 0, En = 1, l_r = 0, Subtraction, Shift Left
	//5) Op = 0, En = 1, l_r = 1, Subtraction, Shift Right
	//6) Op = 1, En = 1, l_r = 1, Addition, Shift Right
	
	 
	//initialize:
	
	en.write(0);
	left_in.write(0);
	right_in.write(0);
	left_right.write(0);
	sc_start(9,SC_NS);
	
	//Case 1 
     en.write(0); //Pass through on BS
     op.write(0); //subtraction
	left_in.write(0); right_in.write(0);
	A.write(3);
	B.write(2);
	left_right.write(0); //'x' 
	sc_start(10, SC_NS);

	//Case 2
	en.write(0); //Pass through on BS 
	op.write(1); //Addition
	//left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);

	//Case 3
	en.write(1); //Enable BS
	op.write(1); //Addition
	//left_in.write(1); right_in.write(0);
	left_right.write(0); //Shift left
	sc_start(10, SC_NS);

	//Case 4
	en.write(1); //Enable BS
	op.write(0); //Subtraction
	//left_in.write(1); right_in.write(0);
	left_right.write(0); //Shift left
	sc_start(10, SC_NS);

	//Case 5
	en.write(1); //Enable BS
	op.write(0); //Subtraction
	//left_in.write(1); right_in.write(0);
	left_right.write(1); //Shift Right
	sc_start(10, SC_NS);

	//Case 6
	en.write(1); //Enable BS
	op.write(1); //Addition
	//left_in.write(1); right_in.write(0);
	left_right.write(1); //Shift Right
	sc_start(15, SC_NS);
	
/*
	left_in.write(1); right_in.write(0);
	left_right.write(0);
	sc_start(10, SC_NS);
	
	left_in.write(1); right_in.write(0);
	left_right.write(1);
	sc_start(10, SC_NS);
		
	en.write(0); //not enabled and input scenario
	left_in.write(1); right_in.write(0);
	left_right.write(1);
	sc_start(10, SC_NS);
	
	en.write(1); //enabled
	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);

	left_in.write(0); right_in.write(1);
	left_right.write(1);
	sc_start(10, SC_NS);
*/
   	sc_close_vcd_trace_file(tf);
    return 0;                         
}
