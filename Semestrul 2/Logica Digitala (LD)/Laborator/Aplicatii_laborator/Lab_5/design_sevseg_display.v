module seven_segment_display(
    input [3:0] num_in,
    output [7:0] leds_out
);

    reg [7:0] mem;

    always @(num_in) begin
        case(num_in) 
            4'd0: mem = 8'h3F;  //display 0
            4'd1: mem = 8'h06;  //display 1
            4'd2: mem = 8'h5B;    //display 2
            4'd3: mem = 8'h4F;    //display 3
            4'd4: mem = 8'h66;    //display 4
            4'd5: mem = 8'h6D;    //display 5
            4'd6: mem = 8'h7D;    //display 6
            4'd7: mem = 8'h07;    //display 7
            4'd8: mem = 8'h7F;    //display 8
            4'd9: mem = 8'h6F;    //display 9
        endcase
    end

    assign leds_out = mem;
endmodule
