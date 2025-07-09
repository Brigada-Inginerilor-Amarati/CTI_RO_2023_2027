module rightshifter2 #(
    parameter WIDTH = 18  // Ensure WIDTH matches the size of P
)(
    input  [WIDTH-1:0] in,
    output [WIDTH-1:0] out
);
    // Sign extension: Use MSB of `in` for the two most significant bits of `out`
    assign out[WIDTH-1] = in[WIDTH-1];
    assign out[WIDTH-2] = in[WIDTH-1];

    // Shift remaining bits
    genvar i;
    generate
      for (i = 0; i < WIDTH - 2; i = i + 1) begin : bit_shift
        assign out[i] = in[i + 2];
      end
    endgenerate
endmodule