`include "four_way_set.v"

module cache_memory #(
    parameter ADDRESS_WORD_SIZE = 32,
    parameter TAG_SIZE = 19,
    parameter BLOCK_SIZE = 8,
    parameter WORD_SIZE = 8,
    parameter NUMBER_OF_SETS = 128
)(
    input clk,
    input rst_b,
    input [ADDRESS_WORD_SIZE-1:0] addr,
    input try_read,
    input try_write,
    input cache_write,
    input [WORD_SIZE-1:0] write_data,
    output [WORD_SIZE-1:0] data_out,
    output hit,
    output dirty
);

    // Extract index: for 128 sets, index = bits [12:6]
    wire [6:0] index = addr[12:6];

    // Wires for all sets
    wire [WORD_SIZE-1:0] data_out_array [0:NUMBER_OF_SETS-1];
    wire hit_array   [0:NUMBER_OF_SETS-1];
    wire dirty_array [0:NUMBER_OF_SETS-1];

    genvar i;
    generate
    //all 128 cache sets
        for (i = 0; i < NUMBER_OF_SETS; i = i + 1) begin : sets
            wire active = (index == i);
            four_way_set #(
                .ADDRESS_WORD_SIZE(ADDRESS_WORD_SIZE),
                .TAG_SIZE(TAG_SIZE),
                .WORD_SIZE(WORD_SIZE)
            ) set_inst (
                .clk(clk),
                .rst_b(rst_b),
                .address_word(addr),
                .try_read(try_read & active),
                .try_write(try_write & active),
                .cache_write(cache_write & active),
                .write_data(write_data),
                .data(data_out_array[i]),
                .hit_miss(hit_array[i]),
                .dirty_out(dirty_array[i]),
                .valid_out()
            );
        end
    endgenerate

    assign data_out = data_out_array[index];
    assign hit      = hit_array[index];
    assign dirty    = dirty_array[index];

endmodule

