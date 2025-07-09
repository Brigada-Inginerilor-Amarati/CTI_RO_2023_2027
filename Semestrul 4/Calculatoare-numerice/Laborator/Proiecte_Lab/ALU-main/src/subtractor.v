module subtractor #(
    parameter WIDTH = 8
)(
    input  [WIDTH-1:0] a,
    input  [WIDTH-1:0] b,
    input              en,
    output [WIDTH:0]   o    // for WIDTH=8, o is 9 bits
);
    // Two's complement subtraction: a - b = a + (~b) + 1 when en is active.
    // When en is low, you might simply pass a (or do nothing, depending on your design).
    wire [WIDTH-1:0] b_inv = b ^ {WIDTH{en}};
    wire cin = en;
    wire [WIDTH:0] sum_internal;
    
    adder #(.WIDTH(WIDTH)) u_add (
        .a(a),
        .b(b_inv),
        .cin(cin),
        .en(1'b1),
        .sum(sum_internal)
    );
    
    // To remove the 256 excess, ignore the extra carry-out.
    // Instead of outputting sum_internal (which is WIDTH+1 bits),
    // we output a 0 as the top bit and the lower WIDTH bits of sum_internal.
   // assign o ={1'b0, sum_internal[WIDTH-1:0]};
    assign o = { sum_internal[WIDTH-1], sum_internal[WIDTH-1:0] };
endmodule

// module subtractor_tb;
//     reg signed [7:0] a;
//     reg signed [7:0] b;
//     reg en = 1'b1;
//     wire signed [8:0] difference;

//     subtractor #(.WIDTH(8)) uut (
//         .a(a),
//         .b(b),
//         .en(en),
//         .o(difference)
//     );

//     integer k;

//     initial begin
//         for(k = 0; k < 10000; k = k + 1) begin
//             {a, b} = k;
//             #10;
//             $display("a=%d      b=%d      dif=%d        diff8=%d", a, b, difference[7:0], difference[8]);
//         end
//     end

// endmodule