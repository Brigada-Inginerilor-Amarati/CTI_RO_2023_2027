// This module implements the combinational Booth encoding selection.
module booth_selector(
  input  [2:0]     bits,       // P[2:0]
  input  [8:0]     add_M,      // from add_M_result
  input  [8:0]     add_2M,     // from add_2M_result
  input  [8:0]     sub_M,      // from sub_M_result
  input  [8:0]     sub_2M,     // from sub_2M_result
  input  [8:0]     lower_P,    // Lower 9 bits of P
  input  [17:0]    P,          // Current P in full
  output [17:0]    temp_P_next // Booth–selected output
);

  assign temp_P_next =
      ((bits == 3'b001) || (bits == 3'b010)) ? {add_M, lower_P} :
      (bits == 3'b011)                     ? {add_2M, lower_P} :
      (bits == 3'b100)                     ? {sub_2M, lower_P} :
      ((bits == 3'b101) || (bits == 3'b110)) ? {sub_M, lower_P} :
                                              P;
endmodule