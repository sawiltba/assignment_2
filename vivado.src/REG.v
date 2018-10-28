`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/20/2018 11:58:03 AM
// Design Name: 
// Module Name: REG
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

module REG #(parameter DATAWIDTH = 32)(clk, rst, d, q);
    input clk, rst;
    input [DATAWIDTH-1:0] d;
    reg [DATAWIDTH-1:0] store;
    output [DATAWIDTH-1:0] q;

    assign q = store;
    always@(posedge clk) begin
        if(rst) begin
            store <= 0;
        end
        else begin
            store <= d;
        end
    end

endmodule
