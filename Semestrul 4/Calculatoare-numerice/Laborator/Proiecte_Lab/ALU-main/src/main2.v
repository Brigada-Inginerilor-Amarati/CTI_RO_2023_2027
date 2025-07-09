// // main.v
// `timescale 1ns/1ps
// `include "fac.v"
// `include "adder.v"
// `include "subtractor.v"
// `include "ctl.v"

// module main2 (
//     input         clk,
//     input         Begin,     // start pulse
//     input         Reset,     // active-low reset
//     input  [7:0]  a,
//     input  [7:0]  b,
//     input  [1:0]  opcode,    // 00=add,01=sub,10-mul,11-div
//     output [8:0]  result     // 9-bit result (carry/borrow in MSB)
// );

//   // ---------------------------------------------------------
//   // 1) Instantiate Control Unit
//   // ---------------------------------------------------------
//   wire [14:0] control_signals;
//   ctl u_ctl (
//     .clk       (clk),
//     .Begin     (Begin),
//     .Reset     (Reset),
//     // no multi-cycle ops yet:
//     .Count3    (1'b0),
//     .Count7m1  (1'b0),
//     .Count7m2  (1'b0),
//     .BM7       (1'b0),
//     .PA_hi     (3'b000),
//     .AQ_lo     (2'b00),
//     .Qneg      (1'b0),
//     .opcode    (opcode),
//     .C1        (control_signals[0]),
//     .C2        (control_signals[1]),
//     .C3        (control_signals[2]),
//     .C4        (control_signals[3]),
//     .C5        (control_signals[4]),
//     .C6        (control_signals[5]),
//     .C7        (control_signals[6]),
//     .C8        (control_signals[7]),
//     .C9        (control_signals[8]),
//     .C10       (control_signals[9]),
//     .C11       (control_signals[10]),
//     .C12       (control_signals[11]),
//     .C13       (control_signals[12]),
//     .C14       (control_signals[13]),
//     .C15       (control_signals[14])
//   );

//   // ---------------------------------------------------------
//   // 2) Operand registers (load on C1)
//   // ---------------------------------------------------------
//   reg [7:0] Areg, Breg;
//   always @(posedge clk or negedge Reset) begin
//     if (!Reset) begin
//       Areg <= 8'b0;
//       Breg <= 8'b0;
//     end else if (control_signals[0]) begin
//       Areg <= a;
//       Breg <= b;
//     end
//   end

//   // ---------------------------------------------------------
//   // 3) Arithmetic units
//   // ---------------------------------------------------------


//   wire [8:0] add_out, sub_out;

//   adder u_add (
//     .a   (Areg),
//     .b   (Breg),
//     .cin (1'b0),
//     .en  (control_signals[1]),
//     .sum (add_out)
//   );

//   subtractor u_sub (
//     .a  (Areg),
//     .b  (Breg),
//     .en (control_signals[2]),
//     .o  (sub_out)
//   );

//   // ---------------------------------------------------------
//   // 4) Result 
//   // ---------------------------------------------------------
//   reg [8:0] add_reg, sub_reg;
// always @(posedge clk or negedge Reset) begin
//     if (!Reset) begin
//       add_reg <= 0;
//       sub_reg <= 0;
//     end
//     else begin      // add finished
//         if(add_out) begin
//           add_reg <= add_out;
//         end
//         if(sub_out) begin
//           sub_reg <= sub_out;
//         end
//   end
// end

// reg [8:0] result_reg;
//   always @(posedge clk or negedge Reset) begin
//     if (!Reset)
//       result_reg <= 9'd0;
//     else if (control_signals[14]) begin
//       case (opcode)
//         2'b00: result_reg <= add_reg;
//         2'b01: result_reg <= sub_reg;
//         default: result_reg <= 9'd20;  // placeholder for mul/div
//       endcase
//     end
//   end
  

//   assign result = result_reg;

// endmodule


// module main_tb;
//   // Clock and reset
//   reg        clk;
//   reg        Reset;
//   // Control
//   reg        Begin;
//   reg [1:0]  opcode;
//   // Operands
//   reg [7:0]  a, b;
//   // Output
//   wire [8:0] result;

//   // Instantiate DUT
//   main2 uut (
//     .clk    (clk),
//     .Begin  (Begin),
//     .Reset  (Reset),
//     .a      (a),
//     .b      (b),
//     .opcode (opcode),
//     .result (result)
//   );
//   wire [14:0] cs = uut.control_signals;
//   wire [8:0] r = uut.result_reg;
//   // Clock generation: 10ns period
//   initial clk = 0;
//   always #5 clk = ~clk;

//   initial begin
//     // Dump waveforms
//     // $dumpfile("main_tb.vcd");
//     // $dumpvars(0, main_tb);

//     // Initialize
//     Reset = 0;
//     Begin = 0;
//     a = 0; b = 0; opcode = 2'b00;
//     #20;
//     Reset = 1;
//     #20;

//     $display("Time  opcode  a    b   result");
//     $display("---------------------------------");
//     // Test addition and subtraction
//     for (opcode = 2'b00; opcode <= 2'b01; opcode = opcode + 1) begin
//       for (a = 0; a < 8; a = a + 1) begin
//         for (b = 0; b < 8; b = b + 1) begin
//           // Apply operands and opcode
//           #1;
//           Begin = 1;
//           #10;
//           Begin = 0;
//           // Wait for result propagation
//           #10;
//           $display("%4t   %b      %2d   %2d     %3d  %3d  %b",$time, opcode, a, b, $signed(result),r,cs);
//           #10;
//           $display("%4t   %b      %2d   %2d     %3d  %3d  %b",$time, opcode, a, b, $signed(result),r,cs);
//         end
//       end
//     end

//     $finish;
//   end
// endmodule


// main2.v
`timescale 1ns/1ps
`include "fac.v"
`include "adder.v"
`include "subtractor.v"
`include "ctl.v"

module main2 (
    input         clk,
    input         Begin,     // start pulse
    input         Reset,     // active-low reset
    input  [7:0]  a,
    input  [7:0]  b,
    input  [1:0]  opcode,    // 00=add,01=sub,10-mul,11-div
    output [8:0]  result     // 9-bit result (carry/borrow in MSB)
);

  // 1) Control Unit
  wire [14:0] C;
  ctl u_ctl (
    .clk      (clk),
    .Begin    (Begin),
    .Reset    (Reset),
    .Count3   (1'b0), .Count7m1(1'b0), .Count7m2(1'b0),
    .BM7      (1'b0),
    .PA_hi    (3'b000),
    .AQ_lo    (2'b00),
    .Qneg     (1'b0),
    .opcode   (opcode),
    .C1       (C[0]),   // load operands
    .C2       (C[1]),   // add enable
    .C3       (C[2]),   // sub enable
    .C4       (), .C5(), .C6(), .C7(),
    .C8       (), .C9(), .C10(),.C11(),
    .C12      (), .C13(),.C14(),.C15()
  );

  // 2) Operand registers (load on C1)
  reg [7:0] Areg, Breg;
  always @(posedge clk or negedge Reset) begin
    if (!Reset) begin
      Areg <= 0;
      Breg <= 0;
    end else if (C[0]) begin
      Areg <= a;
      Breg <= b;
    end
  end

  // 3) Arithmetic units
  wire [8:0] add_out, sub_out;
  adder u_add (
    .a   (Areg),
    .b   (Breg),
    .cin (1'b0),
    .en  (C[1]),
    .sum (add_out)
  );

  subtractor u_sub (
    .a  (Areg),
    .b  (Breg),
    .en (C[2]),
    .o  (sub_out)
  );

  // 4) Result register: latch as soon as the unit is done
  reg [8:0] result_reg;
  always @(posedge clk or negedge Reset) begin
    if (!Reset)
      result_reg <= 0;
    else if (C[1])      // add finished this cycle
      result_reg <= add_out;
    else if (C[2])     // sub finished this cycle
      result_reg <= sub_out;
  end

  assign result = result_reg;

endmodule


module main2_tb;
  reg        clk = 0;
  reg        Reset;
  reg        Begin;
  reg [1:0]  opcode;
  reg [7:0]  a, b;
  wire [8:0] result;

  // DUT
  main2 uut (
    .clk    (clk),
    .Begin  (Begin),
    .Reset  (Reset),
    .a      (a),
    .b      (b),
    .opcode (opcode),
    .result (result)
  );

  // cycle clock
  always #5 clk = ~clk;

  initial begin
    // initialize
    Reset = 0; Begin = 0; opcode = 2'b00; a = 0; b = 0;
    #20 Reset = 1;

    $display("Time  opcode  a  b  result");
    $display("-------------------------");

    // Test addition
    opcode = 2'b00;
    for (a = 0; a < 8; a = a + 1) begin
      for (b = 0; b < 8; b = b + 1) begin
        // start op
        #1 Begin = 1; #1 Begin = 0;
        // wait for result latch
        #1;
        $display("%4t   %b      %1d  %1d   %2d", $time, opcode, a, b, $signed(result));
      end
    end

    // Test subtraction
    opcode = 2'b01;
    for (a = 0; a < 8; a = a + 1) begin
      for (b = 0; b < 8; b = b + 1) begin
        #1 Begin = 1; #10 Begin = 0;
        #5;
        $display("%4t   %b      %1d  %1d   %2d", $time, opcode, a, b, $signed(result));
      end
    end

    $finish;
  end
endmodule