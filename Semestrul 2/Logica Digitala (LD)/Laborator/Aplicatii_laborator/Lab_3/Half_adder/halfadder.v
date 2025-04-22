module halfadder(output si, output ci1, input ai, input bi);
	assign si = ai ^ bi;
	assign ci1 = ai & bi;
endmodule