//2.30 A
module circuit_a(
input x,
input y,
input z,
output f);

wire out0, out1, out2;
or Gate1(out0,x,y);
not Gate2(out1,y);
or Gate3(out2,out1,z);
and Gate4(f,out0,out2);

endmodule
// 2.30 B
module circuit_b(
input x,
input y,
input z,
output f);

wire out0,out1,out2;
nor NGate1(out0, x, y);
nor NGate2(out1, y, y);
nor NGate3(out2, out1,z);
nor NGate4(f,out0,out2);

endmodule
//2.30 D
module circuit_d(
input x,
input y,
input z,
output f);

assign r = (x|y)&(~y|z);

endmodule

module circuit_e(
input x,
input y,
input z,
output reg s);

always@(x or y or z)
begin
	case({x,y,z})
	3'b000: begin s = 0; end
	3'b001: begin s = 0; end
	3'b010: begin s = 0; end
	3'b011: begin s = 1; end
	3'b100: begin s = 1; end
	3'b101: begin s = 1; end
	3'b110: begin s = 0; end
	3'b111: begin s = 1; end
	endcase
end
endmodule

