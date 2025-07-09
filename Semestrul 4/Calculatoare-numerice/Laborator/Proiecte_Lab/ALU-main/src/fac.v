module fac(
    input x, y, ci,
    output z, co
);
    assign z = x ^ y ^ ci;
    assign co = (x & y) | (x & ci) | (y & ci);
endmodule