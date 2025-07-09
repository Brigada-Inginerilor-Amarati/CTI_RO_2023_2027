`timescale 1ns/1ps
`include "fac.v"
`include "adder.v"
`include "subtractor.v"
`include "ctl.v"
`include "multiplier.v"
`include "divider.v"
`include "dff.v"
`include "leftshifter.v"
`include "rightshifter2.v"
`include "shifter.v"

module main(
    input         clk,
    input         Begin,     // start pulse
    input         Reset,     // active-low reset
    input  [7:0]  a,
    input  [7:0]  b,
    input  [1:0]  opcode,    // 00=add, 01=sub, 10=mul, 11=div
    output reg [8:0]  PA,    // internal working register (9-bit)
    output reg [7:0]  AQ,    // operand A register
    output reg [7:0]  BM,    // operand B register
    output reg [7:0]  Qp,    // extra register (e.g. quotient part for mul/div)
    output reg        Qneg,  // sign flag (for adjustments)
    output reg [8:0]  outbus // final 9-bit output (for add/sub) 
                             // (for mul/div you might combine hi:lo elsewhere)
);

  // Instantiate control unit; it produces 15 control signals
  wire [14:0] control_signals;
  ctl u_ctl (
    .clk       (clk),
    .Begin     (Begin),
    .Reset     (Reset),
    .Count3    (1'b0),
    .Count7m1  (1'b0),
    .Count7m2  (1'b0),
    .BM7       (1'b0),
    .PA_hi     (3'b000),
    .AQ_lo     (2'b00),
    .Qneg      (1'b0),
    .opcode    (opcode),
    .C1        (control_signals[0]),
    .C2        (control_signals[1]),
    .C3        (control_signals[2]),
    .C4        (control_signals[3]),
    .C5        (control_signals[4]),
    .C6        (control_signals[5]),
    .C7        (control_signals[6]),
    .C8        (control_signals[7]),
    .C9        (control_signals[8]),
    .C10       (control_signals[9]),
    .C11       (control_signals[10]),
    .C12       (control_signals[11]),
    .C13       (control_signals[12]),
    .C14       (control_signals[13]),
    .C15       (control_signals[14])
  );

  // For addition and subtraction we instantiate the adder and subtractor.
  // They produce 9-bit results.
  wire [8:0] add_out, sub_out;
  adder u_add (
      .a(AQ),
      .b(BM),
      .cin(1'b0),
      .en(1'b1), // always enabled when invoked by a control signal
      .sum(add_out)
  );
  subtractor u_sub (
      .a(AQ),
      .b(BM),
      .en(1'b1),
      .o(sub_out)
  );

  // For multiplication and division we assume the dedicated modules handle multi-cycle iterations.
  wire [15:0] mul_out, div_out;
  wire        mul_done, div_done;
  multiplier u_mul (
      .clk(clk),
      .reset_n(Reset),
      .start(control_signals[8]),  // use C9 as the start for multiplication
      .a(a),
      .b(b),
      .o(mul_out),
      .done(mul_done)
  );
  divider u_div (
      .clk(clk),
      .reset_n(Reset),
      .start(control_signals[9]),  // use C10 as the start for division
      .a(a),
      .b(b),
      .o(div_out),
      .done(div_done)
  );

  // Internal pipeline registers for iterative processing of add/sub.
  // We use PA as the working register.
  // Additional iterative actions (shifting, corrections, etc.) are applied
  // according to the control signals.
  always @(posedge clk or negedge Reset) begin
    if (!Reset) begin
      PA     <= 9'd0;
      AQ     <= 8'd0;
      BM     <= 8'd0;
      Qp     <= 8'd0;
      Qneg   <= 1'b0;
      outbus <= 9'd0;
    end else begin
      // C1: Load operands (only for add/sub operations).
      if (control_signals[0]) begin
        AQ <= a;
        BM <= b;
      end

      // C2: Perform addition.
      if (control_signals[1] && (opcode == 2'b00)) begin
        PA <= add_out;
      end
      
      // C3: Perform subtraction.
      if (control_signals[2] && (opcode == 2'b01)) begin
        PA <= sub_out;
      end

      // For multiply (opcode==2'b10) and division (opcode==2'b11)
      // we assume their own modules manage the iterative stages.
      // However, we can still use some control signals for postprocessing.
      
      // The following stages (C4 to C14) exemplify iterative pipelining for adjustments.
      // (You may replace these with your actual micro-operations.)

      // C4: For add/sub, double BM (simulate an iterative scaling step).
      if (control_signals[3] && (opcode < 2'b10)) begin
        BM <= {BM[6:0], 1'b0};   // left-shift BM by one
      end

      // C5: Arithmetic right shift PA by 1 if needed.
      if (control_signals[4] && (opcode < 2'b10)) begin
        PA <= {PA[8], PA[8:1]};  // sign-extend on right shift
      end

      // C6: Increment a pipeline register (e.g. Qp) as a dummy iterative step.
      if (control_signals[5]) begin
        Qp <= Qp + 1;
      end

      // C7: Update Qneg based on the sign of PA.
      if (control_signals[6]) begin
        Qneg <= PA[8];
      end

      // C8: Further left shift PA (simulate an iterative correction).
      if (control_signals[7] && (opcode < 2'b10)) begin
        PA <= {PA[7:0], 1'b0}; 
      end

      // C9: For multiplication/division, capture intermediate results.
      // (Here we simply latch AQ with a dummy mix of signals.)
      if (control_signals[8] && (opcode != 2'b00 && opcode != 2'b01)) begin
        Qp <= AQ;
      end

      // C10: For multiplication/division, we could subtract 1 from PA.
      if (control_signals[9] && (opcode != 2'b00 && opcode != 2'b01)) begin
        PA <= PA - 1;
      end

      // C11: For add/sub, add BM to PA using the adder.
      if (control_signals[10] && (opcode < 2'b10)) begin
        PA <= add_out;
      end

      // C12: Do an additional arithmetic right shift on PA.
      if (control_signals[11] && (opcode < 2'b10)) begin
        PA <= {PA[8], PA[8:1]};
      end

      // C13: Toggle Qneg as a correction.
      if (control_signals[12]) begin
        Qneg <= ~Qneg;
      end

      // C14: Optionally update PA (here we just hold its value).
      if (control_signals[13]) begin
        PA <= PA;
      end

      // C15: Finally, when the operation is done, drive PA onto outbus.
      if (control_signals[14]) begin
         // For add/sub operations, our final result is in PA.
         // For multiplication and division, we rely on mul_done/div_done to update outbus.
         if (opcode == 2'b00 || opcode == 2'b01)
             outbus <= PA;
         else if (opcode == 2'b10 && mul_done)
             outbus <= mul_out[8:0];  // extract lower 9 bits as an example
         else if (opcode == 2'b11 && div_done)
             outbus <= {div_out[15:8]}; // use high part of division result as an example
      end
    end
  end

endmodule

// Testbench for the main module
module main_tb;
  // Clock, reset, and control
  reg        clk = 0;
  reg        Reset;
  reg        Begin;
  reg  [1:0] opcode;
  // Operands
  reg  [7:0] a, b;
  // Outputs from DUT
  wire [8:0] PA;
  wire [7:0] AQ, BM, Qp;
  wire       Qneg;
  wire [8:0] outbus;

  // Instantiate the main module
  main uut (
    .clk    (clk),
    .Begin  (Begin),
    .Reset  (Reset),
    .a      (a),
    .b      (b),
    .opcode (opcode),
    .PA     (PA),
    .AQ     (AQ),
    .BM     (BM),
    .Qp     (Qp),
    .Qneg   (Qneg),
    .outbus (outbus)
  );
   wire [14:0] cs = uut.control_signals;
  // 10 ns clock period
  initial clk = 0;
  always #5 clk = ~clk;

  initial begin
    // Initialize signals
    Reset   = 0;
    Begin   = 0;
    opcode  = 2'b00;
    a       = 8'd0;
    b       = 8'd0;
    #20;
    Reset   = 1;    // release reset
    #10;

    $display("Time | op  a   b |   PA   AQ   BM   Q' Qneg | outbus");
    $display("-------------------------------------------------------");
    $monitor("%4t | %b   %1d   %1d | %4d   %2d   %2d   %2d   %b | %4d | %b ",
            $time, opcode, a, b,
            PA, AQ, BM, Qp, Qneg,
            outbus,
            cs
          );
    // Test addition (opcode = 00) and subtraction (opcode = 01)
    for (opcode = 2'b00; opcode <= 2'b01; opcode = opcode + 1) begin
      for (a = 0; a < 8; a = a + 1) begin
        for (b = 0; b < 8; b = b + 1) begin
          // Apply a, b, and start the operation
          #1 Begin = 1;
          #20 Begin = 0;
          // Allow a couple of cycles for PA to update
          #20;
          // Display the internal registers and output bus
          $display("%4t | %b   %1d   %1d | %4d   %2d   %2d   %2d   %b | %4d | %b ---",
            $time, opcode, a, b,
            $signed(PA), AQ, BM, Qp, Qneg,
            $signed(outbus),
            cs
          );
          // Display the internal registers and output bus
          // $display("%4t | %b   %1d   %1d | %4d   %2d   %2d   %2d   %b | %4d | %b ",
          //   $time, opcode, a, b,
          //   $signed(PA), AQ, BM, Qp, Qneg,
          //   $signed(outbus),
          //   cs
          // );
        end
      end
    end

    $finish;
  end
endmodule
