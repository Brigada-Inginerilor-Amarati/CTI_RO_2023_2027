module halfadder_tb;
	reg ai;
	reg bi;
	
	wire si;
	wire ci1;
	
	halfadder uut(
		.ai(ai),
		.bi(bi),
		.si(si),
		.ci1(ci1)
	);

	initial begin
		ai = 0;
		bi = 0;
		#100;
	end

	always begin
		#25 ai = ~ai;
		#50 bi = ~bi;
	end
endmodule