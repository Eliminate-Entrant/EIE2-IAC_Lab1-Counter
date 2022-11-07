module counter #(
    parameter WIDTH = 16
)(
    // interface signals
    input logic clk, // clock
    input logic rst, //reset
    input logic en, //counter enable
    output logic [WIDTH-1:0] count //count output
);

always_ff @ (posedge clk) //positive edge clock
    if (rst) count <= {WIDTH{1'b0}};
    else count <= count + (en ? {{WIDTH-1{1'b0}},1'b1} : {WIDTH{1'b1}});//{{WIDTH-1{1'b0}},en}; //clock addition

endmodule
