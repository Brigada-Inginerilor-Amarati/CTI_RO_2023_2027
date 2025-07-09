module leftshifter #(
    parameter WIDTH = 8       
)(
    input  [WIDTH-1:0] in,
    input serial_in,
    output [WIDTH-1:0] out
);
    // LSB is zero after shift
    assign out[0] = serial_in;

    // For bit i>0, out[i] gets in[i-1]
    genvar i;
    generate
      for (i = 1; i < WIDTH; i = i + 1) begin : bit_shift
        assign out[i] = in[i-1];
      end
    endgenerate
endmodule
