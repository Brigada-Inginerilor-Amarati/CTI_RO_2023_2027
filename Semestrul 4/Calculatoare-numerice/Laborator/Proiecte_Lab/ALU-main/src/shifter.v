// A generic shifter that can shift left or right with a given serial input.
module shifter #(
    parameter WIDTH = 8
)(
    input  [WIDTH-1:0] data_in,
    input              shift_left,   // when high, perform left shift
    input              shift_right,  // when high, perform right shift
    input              serial_in,    // input for the new bit
    output [WIDTH-1:0] data_out
);
  // If shift_left then left shift, else if shift_right then right shift, else pass through
  assign data_out = shift_left ? { data_in[WIDTH-2:0], serial_in } :
                    (shift_right ? { serial_in, data_in[WIDTH-1:1] } :
                     data_in);
endmodule
