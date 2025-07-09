module dff #(parameter WIDTH = 1)(
  input              clk,
  input              reset_n,
  input  [WIDTH-1:0] d,
  output [WIDTH-1:0] q
);
  reg [WIDTH-1:0] q_reg;
  assign q = q_reg;
  always @(posedge clk or negedge reset_n) begin
    if (!reset_n)
      q_reg <= {WIDTH{1'b0}};
    else
      q_reg <= d;
  end
endmodule