module ex1b(output out, input a, input b, input c);

assign out = (a & b) | (b & c) | (a & c);

endmodule
