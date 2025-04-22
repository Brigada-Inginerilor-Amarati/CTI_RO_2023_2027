`timescale 1ns / 100ps

module automat_tb;

reg clk, rst, enable;

wire [1:0] current_state;

wire out;

automat uut( .clk(clk), .rst(rst), .enable(enable), 
.current_state(current_state), .out(out) );

initial begin
	forever #20 clk = ~clk;
end

initial begin
	clk = 0;
	rst = 1;
	enable = 0;
	#20 rst = 0;

	#200
	enable = 1; // stare 1, output 0
	#60
	enable = 0; // ramane 0, output 1
	#60
	enable = 1; // trece stare 2, output 0
	#60
	enable = 0; // ramane 1, output 1
	#60
	enable = 1; // trece stare 3, output 1
	#60
	enable = 0; //ramane s3, output 1
	#60
	enable = 1; //trece s0, output 1
	#60
	enable = 0; // ramane s0, ouptut 0
	#300
	$stop;
end
endmodule