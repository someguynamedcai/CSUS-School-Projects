module FF(
input clock,reset,x
output reg z);

always@(posedge clock, posedge reset)
begin
	if (reset == 1)
		current_state<= 0;
	else
		current_state<=next_state;

end
endmodule