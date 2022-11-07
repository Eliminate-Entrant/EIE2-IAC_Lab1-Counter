#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env){
    int i; // # of clock cycle count
    int clk; // module clock signal

    Verilated::commandArgs(argc,argv);

    Vcounter* top = new Vcounter; // DUT

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("counter.vcd");

    if(vbdOpen()!=1) return (-1);
    vbdHeader("ALLAHU AKBAR");
    vbdSetMode(1);


    top->clk = 1;
    top->rst = 1;
    top->en = 1;
    int c = 0;

    

    for (i=0; i<1000;i++){
        if(vbdFlag()){
            for (clk=0; clk<2;clk++){
                tfp->dump (2*i+clk);
                top->clk = !top->clk;
                top->eval ();
            }
        }
        vbdHex(4,(int(top->count) >> 12) & 0xF);  
        vbdHex(3,(int(top->count) >> 8) & 0xF);
        vbdHex(2,(int(top->count) >> 4) & 0xF); 
        vbdHex(1,(int(top->count)) & 0xF);

        
         ///  vbdPlot(int(top->count), 0, 255);
        vbdCycle(i+1);
        

        top->rst = (i<2) | (i==13);
        // if(vbdFlag()){
        //     top->count = vbdValue();
        // };    

   
        // if((top->count == 9) && (c <2)){
        //     top->en = 0;
        //     c +=1;
        // }
        // else if(c>=2){
        //     c=0;
        //     top->en = 1;

        // }
        


        if (Verilated::gotFinish()) exit(0);
    }






    vbdClose();
    tfp->close();
    exit(0);
}
