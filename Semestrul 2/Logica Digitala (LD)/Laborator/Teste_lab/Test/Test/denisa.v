module circuit (input a,b,c,d, output f);
	assign f = ((~d) &(~b))| (d &b);
endmodule 
