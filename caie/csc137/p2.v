//Project 1
module pg_unit_2bits(
input [2:0] x,
input [2:0] y,

output [1:0] p,
output [1:0] g,

wire [3:0] out;

and Gate1(g[0],x[0],y[0]);
and Gate2(g[1],x[1],y[1]);
//Output for g0 and g1

nor Gate3(out[0],x[0],x[0]);
nor Gate4(out[1],y[0],y[0]);
nor Gate5(out[2],out[0],y[0]);
nor Gate6(out[3],out[1],x[0]);
nor Gate7(p[0],out[3],out[2]];
//Circuit for p0

nor Gate10(out[0],x[0],x[0]);
nor Gate11(out[1],y[0],y[0);
nor Gate12(out[2],out[0],y[0]);
nor Gate13(out[3],out[1],x[0]);
nor Gate14(p[0],out[3],out[2];
//Output for p1

endmodule

