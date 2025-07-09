`include "fsm_structural.v"
`include "cache_memory.v"
// Patched cache_controller that uses structural FSM

module cache_controller #(
    parameter ADDRESS_WORD_SIZE = 32,
    parameter TAG_SIZE = 19,
    parameter BLOCK_SIZE = 8,
    parameter WORD_SIZE = 8,
    parameter NUMBER_OF_SETS = 128
) (
    input clk,
    input rst_b,
    input opcode,         // 0: read, 1: write
    input [7:0]data_in,
    input [ADDRESS_WORD_SIZE-1:0] address,
    output [7:0] data_out,
    output hit,
    output ready
);

    // Signals
    wire dirty;
    wire [2:0] fsm_state;
    wire try_read;
    wire try_write;
    wire mem_read;
    wire mem_write;
    wire cache_write;
    wire [7:0] cache_data;
    // Instantiate structural FSM
    fsm_structural fsm (
        .clk(clk),
        .rst_b(rst_b),
        .hit(hit),
        .dirty(dirty),
        .op_read(~opcode),
        .op_write(opcode),
        .current_state(fsm_state),
        .try_read(try_read),
        .try_write(try_write),
        .mem_read(mem_read),
        .mem_write(mem_write),
        .cache_write(cache_write),
        .ready(ready)
    );

    // Cache memory placeholder
    cache_memory cache_inst (
        .clk(clk),
        .rst_b(rst_b),
        .addr(address),
        .try_read(try_read),
        .try_write(try_write),
        .cache_write(cache_write),
        .write_data(data_in), 
        .data_out(cache_data),
        .hit(hit),
        .dirty(dirty)
    );

    assign data_out = cache_data;

endmodule
