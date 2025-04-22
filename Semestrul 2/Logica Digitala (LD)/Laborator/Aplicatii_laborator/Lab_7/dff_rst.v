module dff_rst(
	input clk, d, rst, output reg q);

always @ (posedge clk or negedge rst)
begin
	if(rst == 1'b1)
		q <= 1'b0;
	else
		q <= d;
end
endmodule
