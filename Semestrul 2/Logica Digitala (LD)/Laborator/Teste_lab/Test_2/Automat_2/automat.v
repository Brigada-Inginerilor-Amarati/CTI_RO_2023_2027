`timescale 1ns /100 ps

`define RE 2'b00
`define MV 2'b01
`define ENC 2'b10
`define ME 2'b11

module automat(
	input clk,
	input rst,
	input sel,
	input rd,
	output [1:0] current_state,
	output reg [1:0] out
);

reg [1:0] state_reg, state_next;

always @(posedge clk or posedge rst)
	if (rst)
		state_reg <= `RE;
	else
		state_reg <= state_next;

always @(*) begin
	state_next = state_reg;
	out = 2'b00;

	case(state_reg)
		`RE : begin
			out = 2'b00;
			if (sel & ~rd)
				state_next = `ENC;
			else
				state_next = `RE;												
		end
		`MV : begin 
			out = 2'b01;
			if(~sel & ~rd)
				state_next = `ME;
			else if (sel & rd)
				state_next = `RE;
			else
				state_next = `MV;
		end
		`ENC : begin
    			out = 2'b10;
    			if (sel) begin
        			state_next = `MV;
    			end 
			else if (~sel & ~rd) begin
        			state_next = `ME;
    			end 
			else begin
        			state_next = `ENC;
    			end
		end
		`ME : begin
			out = 2'b11;
			if(~sel)
				state_next = `MV;
			else if(sel & rd)
				state_next = `RE;
			else
				state_next = `ME;
		end
	endcase

end

assign current_state = state_reg;

endmodule