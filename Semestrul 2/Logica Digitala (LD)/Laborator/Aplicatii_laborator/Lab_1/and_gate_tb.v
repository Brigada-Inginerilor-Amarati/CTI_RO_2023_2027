module and_gate_tb;
	// inputs
	// we use reg to assign values to variables
	reg a;
	reg b;

	// outputs
	// ?wire links to variable?
	wire o;

	// 'main' is the name of the first module
	// 'uut' stands for unit under test
	and_gate uut(
		.o(o), 
		.a(a),
		.b(b)
	);
	// .o references to 'main' module 'o', 
	// which we link to the 'o' declared here

	initial begin
		a = 0;
		b = 0;
		// we wait 100 nanoseconds to make
		// sure the operations above execute
		#100;
	end
	
	always begin
		#20 a = ~a;
		#30 b = ~b;
	end

endmodule