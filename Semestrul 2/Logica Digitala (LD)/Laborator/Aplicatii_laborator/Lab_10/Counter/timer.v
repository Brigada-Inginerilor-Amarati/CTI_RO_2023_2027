module timer (
	input rst,
	input clk_1Hz,
	output reg [7:0] time_in_seconds
);

reg [7 : 0] time_reg, [7:0] time_nxt;
reg clk_1Hz_reg, clk_1Hz_nxt;

always @(posedge clk_1Hz or negedge rst) begin
    if (~rst) begin
        time_reg <= 0;
    end else begin
        if (count == 60) begin
            clk_1Hz <= ~clk_1Hz;
            time_in_seconds <= 0;
        end else begin
            time_in_seconds <= time_in_seconds + 1;
        end
    end
end


endmodule


