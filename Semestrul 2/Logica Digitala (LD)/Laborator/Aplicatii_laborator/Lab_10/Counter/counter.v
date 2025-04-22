module counter 
  
  #(parameter COUNT_TARGET = 50000000, WIDTH = 32)
  
  (input clk, rst, output clk_1Hz, output [WIDTH- 1:0] cnt);
  
  reg [WIDTH - 1:0] cnt_reg, cnt_nxt;
  
  reg clk_1Hz_reg, clk_1Hz_nxt;
  
  //sequential
  
  always @(posedge clk or negedge rst) begin
    if(~rst) begin
      cnt_reg <= 0;
      clk_1Hz_reg <= 0;
      
    end
    
    else begin
	cnt_reg <= cnt_nxt;
	clk_1Hz_reg <= clk_1Hz_nxt;
    end
end
    
    //combinational
    
    always @(cnt_reg, clk_1Hz_reg) begin
      cnt_nxt = cnt_reg;
      clk_1Hz_nxt = clk_1Hz_reg;
      
      //niciodata reg in partea stanga nu o sa avem;
      
      if(cnt_reg == COUNT_TARGET) begin
        cnt_nxt = 0;
      	clk_1Hz_nxt = ~clk_1Hz_reg;
end
      else
        cnt_nxt = cnt_reg + 1;
    end
    
    assign cnt = cnt_reg;
endmodule
        
      