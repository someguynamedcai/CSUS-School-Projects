`include "v1.v"
module circuit_b_tb();
reg x, y, z;
wire f;
circuit_b A(x,y,z,f);

initial begin
	$display("Time X Y Z S");
	$monitor("%4d %b", $time, f);
	x = 0; y = 0; z = 0;$display("%4d %b %b %b",$time, x, y, z);
	#1
	x = 0; y = 0; z = 1;$display("%4d %b %b %b",$time, x, y, z);
	#1
	x = 0; y = 1; z = 0;$display("%4d %b %b %b",$time, x, y, z);
	#1
	x = 0; y = 1; z = 1;$display("%4d %b %b %b",$time, x, y, z);
	#1
	x = 1; y = 0; z = 0;$display("%4d %b %b %b",$time, x, y, z);
	#1
	x = 1; y = 0; z = 1;$display("%4d %b %b %b",$time, x, y, z);
	#1
	x = 1; y = 1; z = 0;$display("%4d %b %b %b",$time, x, y, z);
	#1
	x = 1; y = 1; z = 1;$display("%4d %b %b %b",$time, x, y, z);
	#1
$finish;
end 
endmodule
