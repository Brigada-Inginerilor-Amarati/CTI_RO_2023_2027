

module adder #(
    parameter WIDTH = 8
)(
    input [WIDTH-1:0] a,
    input [WIDTH-1:0] b,
    input cin,
    input en,
    output [WIDTH:0] sum
);
    wire [WIDTH-1:0] c;
    wire [WIDTH-1:0] s;

    fac f0(a[0], b[0], cin, s[0], c[0]);

    generate
        genvar i;
        for (i = 1; i < WIDTH; i = i + 1) begin : rca
            fac f(a[i], b[i], c[i-1], s[i], c[i]);
        end
    endgenerate
    
    assign sum = en ? {c[WIDTH-1], s} : 20;
endmodule

// module adder_tb;
//     reg [7:0] a;
//     reg [7:0] b;
//     reg cin;
//     reg en = 1'b1;
//     wire [8:0] sum;

//     adder #(.WIDTH(8)) uut (
//         .a(a),
//         .b(b),
//         .cin(cin),
//         .en(en),
//         .sum(sum)
//     );

//     integer k;

//     initial begin
//         for(k = 0; k < 10000; k = k + 1) begin
//             {a, b, cin} = k;
//             #10;
//             $display("a=%d b=%d cin=%d sum=%d sum8=%d", a, b, cin, sum[7:0], sum[8]);
//         end
//     end

// endmodule
