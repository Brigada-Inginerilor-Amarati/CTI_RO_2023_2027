module gates(input in1, input in2, input in3, output out1, output out2);
assign out1 = in1^ in2 ^in3;
assign out2 = (in1 & in2) | (in2 & in3) | (in1 & in3);
endmodule
