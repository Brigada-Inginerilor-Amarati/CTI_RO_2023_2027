module ex1b_tb;
	reg a, b, t;
	wire out;

ex1b uut(.out(out), .a(a), .b(b), .c(t));

integer k;

initial begin
	{a, b, t} = 0;

for(k = 1; k < 8; k = k + 1)
	#20 {a, b, t} = k; 

	#20;
end
endmodule
