module ex1(
	output out,
	input a, b, c
);
	
assign out = (~a&b) | (~c);

endmodule
