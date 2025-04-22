module gates_tb; 
  
    //Inputs
    reg in1, in2, in3;

    //Outputs
    wire out1, out2;

    gates
  dut (.in1 (in1), .in2 (in2), .in3 (in3), 
  	.out1 (out1), .out2 (out2)
  );
  
	integer k;
  
		initial begin
          {in1, in2, in3} = 0;
	
          for (k = 1; k < 8; k = k + 1)		
				#20 in1, in2, in3 = k;

          //in1, in2, in3 sunt stocate automat pe 1 bit si vor lua toate valorile lui k 
          //k = 1 ->001 -> in1 = 0, in2 = 0, in3 = 1
          
          //k = 2 -> 010 si tot asa, 3 = 011, 4 = 100, 5 = 101, 6 = 110, 7 = 111
		#20
	end
endmodule

