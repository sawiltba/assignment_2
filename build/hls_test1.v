`timescale 1ns / 1ps
module HLSM(clk, rst, start, done, a, b, c, z, x);
	input clk;
	input rst;
	input start

output reg done;
reg [31:0] state, nextState;
	reg [15:0] a;
	reg [15:0] b;
	reg [15:0] c;
	reg [7:0] z;
	reg [15:0] x;
always @(posedge clk) begin
	if(rst == 1) begin
		state <= 0;
	end
	else begin
		state <= stateNext;
	end
end
always@(state, a, b, c) begin
case(state)
	32'd0: begin
		if(start) begin
			stateNext <= 1;
		end
	end
	32'd1: begin
		e = a + c;
		f = a * c;
		stateNext <= 2;
	end
	32'd2: begin
		d = a + b;
		stateNext <= 3;
	end
	32'd3: begin
		g = d > e;
		stateNext <= 4;
	end
	32'd4: begin
		z = g ? d : e;
		x = f - d;
		stateNext <= 5;
	end
	32'd5 begin
		done <= 1;
		stateNext <= 0;	end
end
endmodule
