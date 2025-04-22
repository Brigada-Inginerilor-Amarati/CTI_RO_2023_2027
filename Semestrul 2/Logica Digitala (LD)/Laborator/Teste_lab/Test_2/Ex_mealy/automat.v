`timescale 1ns /100 ps

`define s0 2'b00
`define s1 2'b01
`define s2 2'b10
`define s3 2'b11

module automat(
	input clk,
	input rst,
	input enable,
	output [1:0] current_state,
	output out
);

reg [1:0] state_reg, state_next;
reg out_reg, out_next;

always @(posedge clk or posedge rst)
	if (rst) begin
		state_reg <= `s0;
		out_reg <= 0;
	end
	else begin
		state_reg <= state_next;
		out_reg <= out_next;
	end

always @(*) begin
	//state_next = state_reg;
	//out = 0;

	case(state_reg)
		`s0 : begin
			if (enable) begin
				state_next = `s1;
				out_next = 0;
			end
			else begin
				state_next = `s0;
				out_next = 1;	
			end										
		end
		`s1 : begin 
			if (enable) begin
				state_next = `s2;
				out_next = 0;	
			end
			else begin
				state_next = `s1;
				out_next = 1;	
			end
		end
		`s2 : begin
			if(enable) begin
				state_next = `s3;
				out_next = 1;	
			end
			else begin
				state_next = `s2;
				out_next = 0;	
			end
		end
		`s3 : begin
			if(enable) begin
				state_next = `s0;
				out_next = 1;	
			end
			else begin
				state_next = `s3;
				out_next = 1;	
			end
		end
	endcase

end

assign current_state = state_reg;
assign out = out_reg;

endmodule