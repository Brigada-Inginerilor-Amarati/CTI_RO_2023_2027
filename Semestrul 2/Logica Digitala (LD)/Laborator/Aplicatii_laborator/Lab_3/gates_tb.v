module gates_tb;
reg in1, in2, in3;
wire out1, out2;
gates uvt(.in1(in1), .in2(in2), .in3(in3), .out1(out1), .out2(out2));
integer k;
initial begin
{in1, in2, in3} = 0;
for(k = 1; k <= 8; k = k + 1)
	#20 {in1, in2, in3} = k;
	#20;
end
endmodule
