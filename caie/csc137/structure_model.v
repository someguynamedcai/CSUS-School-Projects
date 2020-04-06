'include "pgu_unit_2bits.v"
'include "su_unit_2bits.v"
'include "cgu_unit_2bits.v"

module 1b((
input [1:0] a;
input [1:0] b;
input carry;

output [1:0] s;
output c1, c2;
);
wire [1:0] c,p,g;
xorgate xor1(carry,p[1],[s1];

assign c1 = c[0];
assign c2 = c[1];

pgu_unit_2bits pgu1(a,b,p,g);
cgu_unt_2bits cgu1(p,g,carry,c);
su_uit_2bits su(p, [c[1:0], carry], s);

endmodule
