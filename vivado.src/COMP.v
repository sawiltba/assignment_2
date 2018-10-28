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

module comp #(parameter DATAWIDTH = 64)(a,b,gt,lt,eq);
    input [DATAWIDTH-1:0]           a,b;
    output reg                      gt,lt,eq;
    
    always@(*) begin
        if (a > b) begin
            gt = 1;
        end else begin
            gt = 0;
        end
        if (a < b) begin
            lt = 1;
        end else begin
            lt = 0;
        end
        if (a == b) begin
            eq = 1;
        end else begin
            eq = 0;
        end
    end

    
endmodule
