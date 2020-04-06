'include "xor.v"

module su_unit_2bits(p,c,s)(
input [1:0] p;
input [1:0] c;
input carry;
output [1:0] s;

xorgate su1(s[0],p[0],carry);
xorgate su2(s[1],p[1],c[0]);
endmodule

