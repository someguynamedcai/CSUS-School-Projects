module OG(
input q1,q0,x,
output z
);

assign z = q1 & q0 & x;

endmodule
