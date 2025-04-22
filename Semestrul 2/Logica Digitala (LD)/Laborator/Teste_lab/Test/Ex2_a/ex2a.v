module ex2a(output out, input a, input b, input c, input d);

assign out = (~a & ~c & d) | (~b & ~c & d) | ( a & b & c & d);

endmodule
