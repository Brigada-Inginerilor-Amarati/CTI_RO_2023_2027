module sipo(input clk, rst, input d, output reg [0:3] q);

always @(posedge clk or posedge rst) begin
    if (rst == 1'b0)
        q <= 4'b0;
    else
        q <= {d, q[0:2]};
end

endmodule

