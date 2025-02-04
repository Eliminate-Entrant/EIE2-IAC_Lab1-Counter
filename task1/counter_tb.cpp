#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    int i; // # of clock cycle count
    int clk; // module clock signal

    Verilated::commandArgs(argc,argv);

    Vcounter* top = new Vcounter; // DUT

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("counter.vcd");

    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    int c = 0;

    for (i=0; i<300;i++){
        for (clk=0; clk<2;clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }
        
        top->rst = (i<2) | (i==13);
        top->en = (i>4);
   
        if((top->count == 9) && (c <2)){
            top->en = 0;
            c +=1;
        }
        else if(c>=2){
            c=0;
            top->en = 1;

        }
        


        if (Verilated::gotFinish()) exit(0);
    }

    tfp->close();
    exit(0);
}
