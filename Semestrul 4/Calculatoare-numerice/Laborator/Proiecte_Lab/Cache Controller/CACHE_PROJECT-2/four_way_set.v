`include "cache_line.v"
// Fixed and enhanced four_way_set module

module four_way_set #(
    parameter ADDRESS_WORD_SIZE = 32,
    parameter TAG_SIZE = 19,
    parameter INDEX_SIZE = 7,
    parameter BLOCK_SIZE = 8,
    parameter WORD_SIZE = 8
) (
    input clk,
    input rst_b,
    input [ADDRESS_WORD_SIZE-1:0] address_word,
    input try_read,
    input try_write,
    input cache_write,
    input [7:0] write_data,
    output [7:0] data,
    output hit_miss,
    output [1:0] hit_index,
    output dirty_out,
    output valid_out
);

    //  Tag and Index extraction 
    wire [TAG_SIZE-1:0] tag = address_word[ADDRESS_WORD_SIZE-1 -: TAG_SIZE];      // [31:13]
    wire [INDEX_SIZE-1:0]index = address_word[ADDRESS_WORD_SIZE - TAG_SIZE - 1 -: INDEX_SIZE]; // [12:6]


    wire [3:0] hit_vec;
    wire [3:0] valid_vec;
    wire [3:0] dirty_vec;
    wire [7:0] data_vec [3:0];

    genvar i;
    generate
    //the 4 lines of the cache set, 4 way SA
        for (i = 0; i < 4; i = i + 1) begin : cache_lines
            cache_line line (
                .clk(clk),
                .rst_b(rst_b),
                .addr(address_word),
                .try_read(try_read),
                .try_write(try_write),
                .cache_write(cache_write & (hit_index == i)),
                .write_data(write_data),
                .hit(hit_vec[i]),
                .valid(valid_vec[i]),
                .dirty(dirty_vec[i]),
                .data_out(data_vec[i])
            );
        end
    endgenerate

    // Determine if  hit or miss
    assign hit_miss = |hit_vec;

    // Select first match (priority encoder)
    assign hit_index = (hit_vec[0]) ? 2'd0 :
                       (hit_vec[1]) ? 2'd1 :
                       (hit_vec[2]) ? 2'd2 :
                       (hit_vec[3]) ? 2'd3 : 2'd0;

    assign data = data_vec[hit_index];
    assign dirty_out = dirty_vec[hit_index];
    assign valid_out = valid_vec[hit_index];

endmodule

