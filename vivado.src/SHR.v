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


module SHR #(parameter DATAWIDTH = 8)(a,sh_amt,d);
    input [DATAWIDTH-1:0] a, sh_amt;
    output reg [DATAWIDTH-1:0] d;
    
    always@(*) begin
       d <= a >> sh_amt; 
    end

    
endmodule
