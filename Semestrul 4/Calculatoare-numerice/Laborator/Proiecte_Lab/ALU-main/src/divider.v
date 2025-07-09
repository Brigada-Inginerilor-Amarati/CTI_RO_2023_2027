`timescale 1ns/1ps
`include "adder.v"
`include "dff.v"
`include "fac.v"
`include "leftshifter.v"
// -------------------------
// Divider Module
// -------------------------
module divider (
    input  wire        clk,
    input  wire        reset_n,
    input  wire        start,
    input  wire [7:0]  a,      // dividend
    input  wire [7:0]  b,      // divisor
    output wire [15:0] o,      // { quotient, remainder }
    output wire        done
);

  // Combined register: {R, Q} initialization:
  wire [15:0] reg_data, reg_data_next;
  wire [15:0] init_val;
  assign init_val = {8'd0, a};

  // 4-bit counter for 8 iterations:
  wire [3:0] count, count_next;
  assign count_next = start ? 4'd8 : (count - 4'd1);

  // One iteration: shift combined register left by one.
  wire [15:0] shifted;
  leftshifter #(.WIDTH(16)) shifter (
      .in(reg_data),
      .serial_in(1'b0),
      .out(shifted)
  );
  
  // Extract remainder and quotient parts.
  wire [7:0] R_sh, Q_sh;
  assign R_sh = shifted[15:8];
  assign Q_sh = shifted[7:0];

  // Compute R_sh - b and R_sh + b.
  wire [8:0] sub_out, add_out;
  adder #(.WIDTH(8)) sub_adder (
      .a(R_sh),
      .b(~b),
      .cin(1'b1),
      .en(1'b1),
      .sum(sub_out)
  );
  adder #(.WIDTH(8)) add_adder (
      .a(R_sh),
      .b(b),
      .cin(1'b0),
      .en(1'b1),
      .sum(add_out)
  );

  // Choose the proper result.
  wire [7:0] R_temp;
  assign R_temp = (R_sh[7] == 1'b0) ? sub_out[7:0] : add_out[7:0];

  // Determine quotient bit.
  wire qbit;
  assign qbit = (R_temp[7] == 1'b0) ? 1'b1 : 1'b0;

  // Form new quotient and remainder.
  wire [7:0] Q_new;
  assign Q_new = { Q_sh[7:1], qbit };
  assign reg_data_next = { R_temp, Q_new };
  
  // Final Correction
  wire [7:0] final_R, final_Q;
  wire [8:0] final_corr;
  assign final_R = reg_data[15:8];
  assign final_Q = reg_data[7:0];
  
  adder #(.WIDTH(8)) final_correction (
      .a(final_R),
      .b(b),
      .cin(1'b0),
      .en(1'b1),
      .sum(final_corr)
  );
  wire [7:0] corrected_R;
  assign corrected_R = (final_R[7] == 1'b1) ? final_corr[7:0] : final_R;

  assign o = { final_Q, corrected_R };
  assign done = (count == 4'd0);

  // Registers for combined data and counter.
  dff #(.WIDTH(16)) reg_data_dff (
      .clk(clk),
      .reset_n(reset_n),
      .d(start ? init_val : reg_data_next),
      .q(reg_data)
  );
  dff #(.WIDTH(4)) count_dff (
      .clk(clk),
      .reset_n(reset_n),
      .d(count_next),
      .q(count)
  );  

endmodule

// -------------------------
// Testbench Module for Divider
// -------------------------
module divider_tb;
  reg         clk;
  reg         reset_n;
  reg         start;
  reg  [7:0]  a, b;
  wire [15:0] o;
  wire        done;
  
  divider uut (
      .clk(clk),
      .reset_n(reset_n),
      .start(start),
      .a(a),
      .b(b),
      .o(o),
      .done(done)
  );
  
  // Clock generation
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // Helper task for testing division
  task test_div(input [7:0] dividend, input [7:0] divisor);
    begin
      reset_n = 0; start = 0;
      #10; reset_n = 1; #5;
      a = dividend; b = divisor;
      start = 1; #10; start = 0;
      wait(done); #5;
      $display("%d ÷ %d: quotient = %d, remainder = %d", dividend, divisor, o[15:8], o[7:0]);
    end
  endtask
  
  // Testbench stimuli with additional tests
  initial begin
    $dumpfile("divider_tb.vcd");
    $dumpvars(0, divider_tb);
    
    // Test Cases
    test_div(8'd15, 8'd3);     // Expected: 5, remainder 0.
    test_div(8'd100, 8'd9);    // Expected: approx. 11, remainder ~1.
    test_div(8'd0, 8'd1);      // Expected: 0, remainder 0.
    test_div(8'd255, 8'd1);    // Expected: 255, remainder 0.
    test_div(8'd1, 8'd255);    // Expected: 0, remainder 1.
    test_div(8'd128, 8'd2);    // Expected: 64, remainder 0.
    test_div(8'd255, 8'd255);  // Expected: 1, remainder 0.
    test_div(8'd5, 8'd2);      // Expected: 2, remainder 1.
    
    // Additional edge cases...
    test_div(8'd250, 8'd5);    // 250 ÷ 5: Expected: 50, remainder 0.
    test_div(8'd37, 8'd7);     // 37 ÷ 7.
    
    $finish;
  end
endmodule
