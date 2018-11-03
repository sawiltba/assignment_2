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
// MM will do

module MUL #(parameter DATAWIDTH = 64)(a,b,prod);
    input [DATAWIDTH-1:0]           a,b;
    output reg [2*DATAWIDTH-1:0]    prod;
    
    always@(*) begin
        prod = $unsigned( a * b);
    end

endmodule
