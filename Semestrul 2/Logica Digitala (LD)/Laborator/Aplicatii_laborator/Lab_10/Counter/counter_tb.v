module counter_tb;
	reg clk, rst;
	wire clk_1Hz;
	
	localparam WIDTH = 32;
	wire [WIDTH -1 : 0] cnt;

counter #(.COUNT_TARGET(50000000), .WIDTH(WIDTH)) uut(.clk(clk), .rst(rst), .clk_1Hz(clk_1Hz), .cnt(cnt));

initial begin
	rst = 0;
	#50;
	rst = 1;
	clk = 0;
	forever begin
		#10;
		clk = ~clk;
	end
end

endmodule
