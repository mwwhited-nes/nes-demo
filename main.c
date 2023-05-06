#include <peekpoke.h>
#include <string.h>
#include <nes.h>
#include "neslib.h"
//#link "chr_generics.s"

word counters[128];

void main(void) {
  byte c,x;
  char p[256];
  char q[272];
  
  // set palette colors
  pal_col(0,0x02);	// set screen to dark blue
  pal_col(1,0x14);	// fuchsia
  pal_col(2,0x20);	// grey
  pal_col(3,0x30);	// white

  // write text to name table
  vram_adr(NTADR_A(1,1));		  // set address
  vram_write("Bleeding Eyes", 13);	  // write bytes to video RAM
  
  vram_adr(NTADR_A(1,3));		  // set address
  vram_write("000000000011111111112222222222", 30);	  // write bytes to video RAM
  vram_adr(NTADR_A(1,4));		  // set address
  vram_write("012345678901234567890123456789", 30);	  // write bytes to video RAM
    
  vram_adr(NTADR_A(1,6));		  // set address  
  for (c=0; c<255; c++) {  
    p[c]= c;
  }
  vram_write(p, 256);
  
  vram_adr(NTADR_A(1,15));		  // set address  
  for (c=0; c<30; c++) {  
    for (x=0; x<9; x++) {  
      q[c + x * 32]= c+x*30;
    }
  }
  vram_write(q, 256);
  

  // enable PPU rendering (turn on screen)
  ppu_on_all();

  // infinite loop
  while(1) 
  {
    byte i,j;
    pal_col(0,(i+0x02) % 0x3f);	// white
    pal_col(1,(i+0x14) % 0x3f);	// white
    pal_col(2,(i+0x20) % 0x3f);	// white
    pal_col(3,(i+0x30) % 0x3f);	// white
    i++;
    
    
    for (j=0; j<30; j++) {
      //counters[j] += j*16; 
      ppu_wait_frame();
    }
  }
}

