
module cache_line #(
    parameter ADDRESS_WORD_SIZE = 32,
    parameter TAG_SIZE = 19,
    parameter WORD_SIZE = 8
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
    output valid,
    output dirty
);

    // Split address
    wire [TAG_SIZE-1:0] addr_tag;
    assign addr_tag = addr[ADDRESS_WORD_SIZE-1 -: TAG_SIZE];

    // TAG register 
    wire [TAG_SIZE-1:0] tag_out;
    wire tag_en;
    assign tag_en = cache_write;
    generate
        genvar i;
        for (i = 0; i < TAG_SIZE; i = i + 1) begin : tag_reg
            dff tag_dff (
                .clk(clk),
                .rst_b(rst_b),
                .en(tag_en),
                .d(addr_tag[i]),
                .q(tag_out[i])
            );
        end
    endgenerate

    //data registers
    wire [WORD_SIZE-1:0] data_out_reg;
    wire data_en = (try_write & hit_internal) | cache_write;
    wire [WORD_SIZE-1:0] data_mux_out;
    assign data_mux_out = cache_write ? write_data : write_data;

    generate
        for (i = 0; i < WORD_SIZE; i = i + 1) begin : data_reg
            dff data_dff (
                .clk(clk),
                .rst_b(rst_b),
                .en(data_en),
                .d(write_data[i]),
                .q(data_out_reg[i])
            );
        end
    endgenerate

    //data out, for read operations
    assign data_out = data_out_reg;

    //VALID register 
    dff valid_dff (
        .clk(clk),
        .rst_b(rst_b),
        .en(cache_write),
        .d(1'b1),
        .q(valid)
    );

    // DIRTY register
    wire dirty_set = try_write & hit_internal;
    wire dirty_clr = cache_write;
    wire dirty_next = dirty_set ? 1'b1 : (dirty_clr ? 1'b0 : dirty);
    dff dirty_dff (
        .clk(clk),
        .rst_b(rst_b),
        .en(dirty_set | dirty_clr),
        .d(dirty_next),
        .q(dirty)
    );

    // hit check
    wire tag_match;
    comparator #(TAG_SIZE) tag_cmp (
        .a(tag_out),
        .b(addr_tag),
        .eq(tag_match)
    );
    wire hit_internal = tag_match & valid;
    assign hit = hit_internal;

endmodule

// flip flop module
module dff (
    input clk,
    input rst_b,
    input en,
    input d,
    output reg q
);
    always @(posedge clk or negedge rst_b) begin
        if (!rst_b)
            q <= 0;
        else if (en)
            q <= d;
    end
endmodule
//comparator module
module comparator #(parameter N = 8) (
    input [N-1:0] a,
    input [N-1:0] b,
    output eq
);
    assign eq = (a == b);
endmodule

