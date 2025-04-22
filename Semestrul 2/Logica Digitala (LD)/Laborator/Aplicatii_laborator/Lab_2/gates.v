module gates(
  input in1, in2, in3,
  output out1, out2
);
  
wire nand1, nand2, nand3;
  
assign nand1 = (~in1 & in2);
assign nand2 = (~in1 & in3); 
assign nand3 = (~in2 & in3);
  
assign out1 = nand1 | nand2 | nand3; 
assign out2 = (~in1 & in2) | (in1 & ~in2);
  
endmodule