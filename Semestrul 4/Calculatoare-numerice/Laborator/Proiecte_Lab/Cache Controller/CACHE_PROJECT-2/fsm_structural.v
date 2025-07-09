
// Structural FSM for cache control 
module fsm_structural (
    input clk,
    input rst_b,
    input hit,
    input dirty,
    input op_read,
    input op_write,
    output [2:0] current_state,
    output try_read,
    output try_write,
    output mem_read,
    output mem_write,
    output cache_write,
    output ready
);

// State encoding
localparam IDLE        = 3'b000,
           READ_HIT    = 3'b001,
           READ_MISS   = 3'b010,
           WRITE_HIT   = 3'b011,
           WRITE_MISS  = 3'b100,
           EVICT       = 3'b101,
           ALLOCATE    = 3'b110;

wire [2:0] next_state;
wire [7:0] state_decode;

// Flip-Flops for state register
dff_3bit state_reg (
    .clk(clk),
    .rst_b(rst_b),
    .d(next_state),
    .q(current_state)
);

//decoder
decoder_3x8 decode_state (
    .in(current_state),
    .out(state_decode)
);

// Next-state logic
next_state_logic logic_unit (
    .current_state(current_state),
    .hit(hit),
    .dirty(dirty),
    .op_read(op_read),
    .op_write(op_write),
    .next_state(next_state)
);

// Outputs based on decoded state
assign try_read    = state_decode[IDLE] & op_read;
assign try_write   = state_decode[IDLE] & op_write;
assign mem_write   = state_decode[EVICT];
assign mem_read    = state_decode[ALLOCATE];
assign cache_write = state_decode[WRITE_HIT] | state_decode[ALLOCATE];
assign ready       = state_decode[READ_HIT] | state_decode[WRITE_HIT] | state_decode[ALLOCATE];

endmodule

module decoder_3x8(
    input [2:0] in,
    output reg [7:0] out
);
    always @(*) begin
        out = 8'b00000000;
        out[in] = 1'b1;
    end
endmodule

module next_state_logic(
    input [2:0] current_state,
    input hit,
    input dirty,
    input op_read,
    input op_write,
    output reg [2:0] next_state
);
    localparam IDLE        = 3'b000,
               READ_HIT    = 3'b001,
               READ_MISS   = 3'b010,
               WRITE_HIT   = 3'b011,
               WRITE_MISS  = 3'b100,
               EVICT       = 3'b101,
               ALLOCATE    = 3'b110;

    always @(*) begin
        case (current_state)
            IDLE: begin
                if (op_read)
                    next_state = hit ? READ_HIT : READ_MISS;
                else if (op_write)
                    next_state = hit ? WRITE_HIT : WRITE_MISS;
                else
                    next_state = IDLE;
            end
            READ_MISS,
            WRITE_MISS: next_state = dirty ? EVICT : ALLOCATE;
            EVICT:      next_state = ALLOCATE;
            READ_HIT,
            WRITE_HIT,
            ALLOCATE:   next_state = IDLE;
            default:    next_state = IDLE;
        endcase
    end
endmodule

module dff_3bit(
    input clk,
    input rst_b,
    input [2:0] d,
    output reg [2:0] q
);
    always @(posedge clk or negedge rst_b) begin
        if (!rst_b)
            q <= 3'b000;
        else
            q <= d;
    end
endmodule
