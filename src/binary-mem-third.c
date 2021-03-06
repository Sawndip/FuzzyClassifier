/*    CALCULATING THE BINARY MEMBERSHIP AND THE MEMBERSHIP OF
                   THE TRAINING SET                    */
#include "header.h"

void third() {
   int i,j,no_lns,bin,class;
   float patt_mem;

  /* function definitions */ 
   void fno_lns(FILE *,int *);

   FILE *fpin, *fpout;    /* fpin & fpout are the i/p and o/p files */

/* opening the files for input and output  and counting the no of patterns*/
   fpin = fopen("inmem.dat","r");
   fpout = fopen("bin.dat","w+");
   fno_lns(fpin,&no_lns);

   for(i=0;i<no_lns;i++) {
       fscanf(fpin,"%d",&class);
       fprintf(fpout,"%d ",class);
       for(j=0;j<3*NO_ATRIB;j++) {
          fscanf(fpin,"%f",&patt_mem);
          if(patt_mem < .5) 
             bin=0;
          else 
             bin=1;
          fprintf(fpout,"%d ",bin);
       }
       fprintf(fpout,"\n");
  }

   fclose(fpin);
   fclose(fpout);
}

