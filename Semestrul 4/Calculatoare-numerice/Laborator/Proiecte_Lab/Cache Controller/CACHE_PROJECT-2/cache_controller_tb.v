`timescale 1ns / 1ps
`include "cache_controller.v"
module cache_controller_tb;

    // Inputs
    reg clk;
    reg rst_b;
    reg opcode;
    reg [7:0] data_in; // Data input for write operations
    reg [31:0] address; // Address input for cache operations
    // Outputs
    wire [7:0] data_out;
    wire hit;
    wire ready;

    // Instantiate DUT
    cache_controller uut (
        .clk(clk),
        .rst_b(rst_b),
        .opcode(opcode),
        .data_in(data_in),
        .address(address),
        .data_out(data_out),
        .hit(hit),
        .ready(ready)
    );

    // Clock 
    initial clk = 0;
    always #5 clk = ~clk;

    //task to send operation to cache controller
    task send_op(input reg rw, input [7:0] val,input [31:0] addr);
        begin
            @(posedge clk);
            opcode <= rw;
            data_in <= val;
            address <= addr;
            $display("Opcode = %0s | Addr = 0x%08h | data_in = 0x%0h @ %0t", 
                  rw ? "WRITE" : "READ", addr, val, $time);
             #20;
        end
    endtask
    //waiting for ready signal
    task wait_ready;
        begin
            while (!ready)
                @(posedge clk);
            $display("READY: data_out = 0x%0h | RESULT = %s @ %0t",
                 data_out, hit ? "HIT " : "MISS", $time);
        end
    endtask

    initial begin

        clk = 0;
        rst_b = 0;
        opcode = 0;  // read

        // Reset phase
        #12 rst_b = 1;

        send_op(0, 8'h00, 32'h00000010); wait_ready(); // MISS
        send_op(0, 8'h00, 32'h00000010); wait_ready(); // HIT
        
        send_op(1, 8'hA5, 32'h00000080); wait_ready(); // MISS

        send_op(1, 8'hB6, 32'h00000100); wait_ready(); // HIT
        send_op(0, 8'h00, 32'h00000100); wait_ready(); // HIT

        send_op(0, 8'h00, 32'h00000200); wait_ready(); // MISS
        send_op(1, 8'hC7, 32'h00000200); wait_ready(); // HIT
        send_op(0, 8'h00, 32'h00000200); wait_ready(); // HIT

        send_op(0, 8'h00, 32'h00000400); wait_ready(); // MISS
        send_op(1, 8'hD8, 32'h00000400); wait_ready(); // HIT
        send_op(0, 8'h00, 32'h00000400); wait_ready(); // HIT

        $display("Simulation done.");
        $finish;
    end

endmodule
