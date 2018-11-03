`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/20/2018 11:20:41 AM
// Design Name: 
// Module Name: add
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module MUX2x1 #(parameter DATAWIDTH = 64)(a,b,sel,d);
    input [DATAWIDTH-1:0] a,b;
    input sel;
    output reg [DATAWIDTH-1:0] d;

    always@(a,b,sel) begin
        if(sel == 0)
            d <= a;
        else
            d <= b;
    end


endmodule
