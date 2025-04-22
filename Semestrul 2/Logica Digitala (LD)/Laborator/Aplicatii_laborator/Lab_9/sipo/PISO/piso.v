module piso(input clk, rst, input d, ld, output [0:3] q);

reg [3:0] shift_reg;

always @(posedge clk or posedge rst) begin
    if (rst)
        shift_reg <= 4'b0;
    else if (ld)
        shift_reg <= d;
    else
        shift_reg <= {shift_reg[2:0], 1'b0};
end

assign q = shift_reg;

endmodule
