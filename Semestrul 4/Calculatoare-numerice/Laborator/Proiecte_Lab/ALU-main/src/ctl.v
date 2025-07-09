
// Control Unit micro‑sequencer for ALU
// Generates C0…C16 timing strobes on successive cycles after `start`
module ctl (
    input        clk,
    input        Begin,
    input        Reset,
    input        Count3,
    input        Count7m1,
    input        Count7m2,
    input        BM7,
    input  [2:0] PA_hi,    // P/A[8:6]
    input  [1:0] AQ_lo,    // A/Q[1:0]
    input        Qneg,     // Q[-1]
    input   [1:0] opcode, //operation code 00-add, 01-sub, 10-mul, 11-div
    output       C1,
    output       C2,
    output       C3,
    output       C4,
    output       C5,
    output       C6, 
    output       C7,
    output       C8,
    output       C9,
    output       C10,
    output       C11,
    output       C12,
    output       C13,
    output       C14,
    output       C15
);

// Choose max_phase = number of micro-steps−1
// add/sub: 0  | mul: 3 | div: 7
wire [3:0] max_phase =  opcode==2'b10 ? 4'd5  //multiplication
                           : opcode==2'b11 ? 4'd9  //division
                           :          4'd2;  //addition and subtraction
// Phase counter
  reg [3:0] phase;
  reg       running;
  always @(posedge clk or negedge Reset) begin
    if (!Reset) begin
      phase   <= 0;
      running <= 1'b0;
    end else if (Begin) begin
      phase   <= 0;
      running <= 1'b1;
    end else if (running) begin
      if (phase == max_phase) begin
        running <= 1'b0;
      end else begin
        phase <= phase + 1;
      end
    end
  end

// C1: load B/M from INBUS
assign C1  = Begin && phase == 0;

// C2: add P/A + B/M when in first cycle and low bits indicate +1
assign C2  = (phase == 1 && opcode != 2'b11) || (phase == 3 && opcode == 2'b11);

// C3: subtract P/A - B/M when C2 active
assign C3  = (phase == 1 && opcode == 2'b01) || (phase == 1 && opcode == 2'b10 && ({AQ_lo,Qneg}==3'b100 || {AQ_lo,Qneg}==3'b101 || {AQ_lo,Qneg}==3'b110)) || (phase ==  3 && opcode == 2'b11 && ({PA_hi}==3'b011 || {PA_hi}==3'b001 || {PA_hi}==3'b010)); // opcode 01 for subtraction, 10 for multiplication

// C4: double B/M (shift left) at Count3 phase
assign C4  = phase == 1 && ({AQ_lo,Qneg}==3'b100 || {AQ_lo,Qneg}==3'b011) && opcode == 2'b10; // opcode 10 for multiplication

// C5: arithmetic right shift P/A & A/Q by 2 at Count3 phase
assign C5  = phase==2 && opcode == 2'b10;

// C6: increment COUNT3 flag
assign C6  = phase==3 && Count3==0 && opcode == 2'b10;

// C7: shift left all registers at first COUNT7m2 phase
assign C7  = phase== 1 && BM7== 0 && opcode == 2'b11;

// C8: detailed shift and zeroing at COUNT7m2
assign C8  = phase==2 && BM7==1 && opcode == 2'b11 ;

// C9: set A/Q[0] = 1 after C8
assign C9  = phase==2 && opcode == 2'b11 && ({PA_hi}==3'b011 || {PA_hi}==3'b001 || {PA_hi}==3'b010); // opcode 01 for subtraction, 10 for multiplication;

// C10: set Qneg = 1 after C8
assign C10 = phase==2 && opcode == 2'b11 && ({PA_hi}==3'b100 || {PA_hi}==3'b101 || {PA_hi}==3'b110);

// C11: increment COUNT7-1 flag
assign C11 = phase== 4 && Count7m1==0 && opcode == 2'b11;

// C12: add Qneg + 1 then C2
assign C12 = phase == 5 && Count7m1==1 && PA_hi[2]==1 && opcode == 2'b11 ;

// C13: shift right P/A by one position then zero LSB
assign C13 = phase == 6 && Count7m2 == 1 && opcode == 2'b11;

// C14: subtract Qneg from A/Q
assign C14 = phase == 7 && Count7m2 == 0 && opcode == 2'b11;

// C15: drive P/A onto OUTBUS when higher bits match
assign C15 = (phase == 2 && (opcode== 2'b00 || opcode== 2'b01)) || (phase == 4 && opcode== 2'b10) || (phase == 8 && opcode == 2'b11); 

endmodule