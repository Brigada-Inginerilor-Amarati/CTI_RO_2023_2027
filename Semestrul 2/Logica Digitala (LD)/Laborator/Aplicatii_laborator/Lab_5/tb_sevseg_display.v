module tb_seven_segment_display();
    reg [3:0] num_in_tb;
    wire [7:0] out_tb;

    seven_segment_display DUT(
        .num_in(num_in_tb),
        .leds_out(out_tb)
    );

    initial begin
        num_in_tb = 4'd0;
    end 

    always begin
        #20 num_in_tb = num_in_tb + 1;
    end 
endmodule