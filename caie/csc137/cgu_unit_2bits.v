module cgu_unit_2bits(g,p,c)(
input [1:0] c;
input [1:0] p;
input carry;

output [1:0] c;

wire [2:0] out;

assign c = g[0]|(p[0]^carry);
assign c1 = g[1]|(p[1]^g[0])|(p[1]^p[0]^carry);

endmodule



