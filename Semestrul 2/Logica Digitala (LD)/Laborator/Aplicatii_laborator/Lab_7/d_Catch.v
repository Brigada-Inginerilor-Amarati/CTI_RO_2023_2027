module d_Latch (
	input c, d
	output reg q
);

always @ (c or d) begin
	if(c)
		q <= d;
	end
endmodule

# la = ii zice blocking statement a = 1, b =0 => se executa pe rand atribuirile
# daca folosim <= este un non-blocking assignment adica toate se vor atribui in acelasi timp
# in circuite secventiale folosim non-blocking assignment  