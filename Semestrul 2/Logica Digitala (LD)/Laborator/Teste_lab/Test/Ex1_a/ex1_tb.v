module ex1_tb;
	reg a, b, c;
	wire out;

ex1 uut(.out(out), .a(a), .b(b), .c(c) );

integer k;

initial begin
	{a, b, c} = 0;

	for(k = 1; k < 8; k = k + 1)
		#20 {a, b, c} = k;
	
	#20;
end

endmodule
