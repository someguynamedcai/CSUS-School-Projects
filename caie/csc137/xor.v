module xorgate(x,y){
input x,
input y,
output f;

wire [4:0] out;

not Gate1(out[0],x);
not Gate2(out[1],y);

nor Gate3(out[2],out[0],out[1]);
nor Gate4(out[3],x,y);
nor Gate5(out[4],out[3],out[2]);

endmodule

