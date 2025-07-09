module multiplier (
  input         clk,
  input         reset_n,
  input         start,
  input  [7:0]  a,
  input  [7:0]  b,
  output [15:0] o,
  output        done
);

  // Wires for registers (datapath)
  wire [8:0]  M_reg, M_next;
  wire [17:0] P_reg, P_init, P_mux, P_next, P_shifted;
  wire [2:0]  count_reg, count_next;
  wire [17:0] temp_P_next;
  wire        phase_reg, phase_next; // 1-bit phase: 0 = COMPUTE, 1 = SHIFT

  // ---------------------------
  // M register: load new value when start, else hold.
  assign M_next = start ? {a[7], a} : M_reg;
  dff #(.WIDTH(9)) M_dff (
    .clk(clk),
    .reset_n(reset_n),
    .d(M_next),
    .q(M_reg)
  );
  
  // P register initialization
  assign P_init = {9'b0, b, 1'b0};

  // Phase flip-flop (pipelining the computation)
  // On start, phase resets to 0 (COMPUTE). Otherwise, it toggles each cycle.
  dff #(.WIDTH(1)) phase_dff (
    .clk(clk),
    .reset_n(reset_n),
    .d( start ? 1'b0 : ~phase_reg ),
    .q(phase_reg)
  );
  // (No separate phase_next wire needed because we toggle directly.)

  // Multiplexer for P:
  // On start, load P_init; otherwise, if phase==0 (COMPUTE) then hold current P;
  // if phase==1 (SHIFT) then update with the shifted value.
  assign P_mux = start ? P_init : ( phase_reg ? P_shifted : P_reg );
  
  dff #(.WIDTH(18)) P_dff (
    .clk(clk),
    .reset_n(reset_n),
    .d(P_mux),
    .q(P_reg)
  );

  // Count register: increment only on SHIFT phase
  wire [2:0] count_plus;
  assign count_plus = count_reg + 3'd1;
  // Reset count on start; increment only when phase==1.
  assign count_next = start ? 3'd0 : ( phase_reg ? count_plus : count_reg );
  dff #(.WIDTH(3)) count_dff (
    .clk(clk),
    .reset_n(reset_n),
    .d(count_next),
    .q(count_reg)
  );
  
  // ---------------------------
  // Datapath: Booth-logic and arithmetic units
  // Instantiate arithmetic modules using P_reg and M_reg

  wire [9:0] add_M_result, sub_M_result, add_2M_result, sub_2M_result;
  
  adder #(.WIDTH(9)) add_M_inst (
    .a(P_reg[17:9]),
    .b(M_reg),
    .cin(1'b0),
    .en(1'b1),
    .sum(add_M_result)
  );
  
  subtractor #(.WIDTH(9)) sub_M_inst (
    .a(P_reg[17:9]),
    .b(M_reg),
    .en(1'b1),
    .o(sub_M_result)
  );
  
  // M shifted left by one (2nd operand for add_2M and sub_2M)
  wire [8:0] M_shifted;

  leftshifter #(.WIDTH(9)) M_shifted_inst (
    .in(M_reg),
    .serial_in(1'b0),
    .out(M_shifted)
  );
  
  adder #(.WIDTH(9)) add_2M_inst (
    .a(P_reg[17:9]),
    .b(M_shifted),
    .cin(1'b0),
    .en(1'b1),
    .sum(add_2M_result)
  );
  
  subtractor #(.WIDTH(9)) sub_2M_inst (
    .a(P_reg[17:9]),
    .b(M_shifted),
    .en(1'b1),
    .o(sub_2M_result)
  );
  
  // Booth selection logic: use lower 9 bits of P and P[2:0] from P_reg.
  // Note: We cover the common cases. (Cases 000/111 imply no operation.)
  booth_selector booth_sel_inst (
    .bits(P_reg[2:0]),
    .add_M(add_M_result[8:0]),
    .add_2M(add_2M_result[8:0]),
    .sub_M(sub_M_result[8:0]),
    .sub_2M(sub_2M_result[8:0]),
    .lower_P(P_reg[8:0]),
    .P(P_reg),
    .temp_P_next(temp_P_next)
  );
  
  // Register to hold booth selection result.
  // We update this in the COMPUTE phase.
  // Note: When phase==0, we register the newly computed temp_P_next.
  dff #(.WIDTH(18)) Pnext_dff (
    .clk(clk),
    .reset_n(reset_n),
    .d( phase_reg ? P_reg : temp_P_next ),
    .q(P_next)
  );
  
  // Right shifter (as given) shifts by 2 bits with sign extension.
  rightshifter2 #(.WIDTH(18)) p_shifter_inst (
    .in(P_next),
    .out(P_shifted)
  );
  
  // ---------------------------
  // Control: done is asserted when count equals 4 (after four SHIFTS)
  assign done = (count_reg == 3'd4);
  
  // Final output: extract bits from P_reg.
  // Because we use radix-4 (2-bit shift per iteration), the internal value is scaled.
  // Adjust extraction as needed. In our design we assume that the proper product is:
  assign o = $signed(P_reg[16:1]);
  
endmodule

module multiplier_tb;
    reg               clk;
    reg               reset_n;
    reg               start;
    reg  signed [7:0] a, b;
    wire signed [15:0] product;
    wire              done;
    
    // Instantiate the multiplier
    multiplier uut (
        .clk(clk),
        .reset_n(reset_n),
        .start(start),
        .a(a),
        .b(b),
        .o(product),
        .done(done)
    );
    
    // Clock generation: 10 ns period
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    initial begin
        // Setup dump for waveform viewing
        $dumpfile("multiplier_tb.vcd");
        $dumpvars(0, multiplier_tb);

        // Initialize control signals
        reset_n = 0;
        start   = 0;
        a       = 0;
        b       = 0;
        #15;           // Wait a bit before releasing reset
        reset_n = 1;
        #10;
        
        // Test Case 1: 3 * 5 => Expected product: 15
        a = 8'd3; 
        b = 8'd5;
        start = 1; 
        #10; 
        start = 0;
        wait(done);  // Wait until done is asserted
        #10;
        $display("Test 1: 3 * 5 = %0d (Expected: 15)", product);
        
        // Test Case 2: -128 * 127 => Expected product: -16256
        a = -128; 
        b = 127;
        start = 1; 
        #10; 
        start = 0;
        wait(done);
        #10;
        $display("Test 2: -128 * 127 = %0d (Expected: -16256)", product);
        
        $finish;
    end
endmodule