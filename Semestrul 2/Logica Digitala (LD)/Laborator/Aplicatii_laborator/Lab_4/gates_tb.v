module gates_tb;

reg [3:0]a;
reg [3:0]b;
reg cin;
wire [3:0]sum;
wire cout;

rca uut(.a(a), .b(b), .cin(cin), .sum(sum), .cout(cout));

initial begin
a = 4'b0101;
b = 4'b1010;
cin = 1'b0;
#20;
end
endmodule
