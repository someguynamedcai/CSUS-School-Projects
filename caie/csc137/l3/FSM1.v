`include "FF.v"
`include "OG.v"
`include "NSG.v"

module FSM1(clock,reset,x,z
	input q1,q0,x,d1,d0;
	output z;
);
wire [1:0] q, d, ~q;
NSG nsg1(q, x ,d);
FF FF1(d[1], r, clock, ~q[1]);
FF FF2(d[0], r, clock, ~q[0]);
OG OG1(q,x,z);

endmodule