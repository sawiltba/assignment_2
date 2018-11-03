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


module SSUB #(parameter DATAWIDTH = 8)(a,b,diff);
    input [DATAWIDTH-1:0] a,b;
    output reg [DATAWIDTH-1:0] diff;
    
    always@(a,b) begin
        diff = $signed($signed(a) - $signed(b));
    end

endmodule