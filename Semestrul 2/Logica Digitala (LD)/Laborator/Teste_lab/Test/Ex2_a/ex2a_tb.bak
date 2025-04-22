module ex2a_tb;

reg a, b, c, d;

wire out;

ex2a uut(.out(out), .a(a), .b(b), .c(c), .d(d));

integer k;

initial begin

{a, b, c, d} = 0;

for(k = 1; k < 16; k = k + 1)
	#20 {a, b, c, d} = k;
	#20;
end
endmodule
