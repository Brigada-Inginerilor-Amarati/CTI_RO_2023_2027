// output is always first
// 'input a' is equivalent to 'input [0:1]a'
// so, by default it will be on one bit

module and_gate(output o, input a, input b);

	assign o=a&b; // or and(o,a,b);
	// where 'and' is a primitive in verilog
endmodule