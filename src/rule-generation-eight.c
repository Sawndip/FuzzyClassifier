    /*     RULES ARE GENERATED IN THIS PROGRAM  */

#include "header.h"


void eighth() {
   FILE *fp1,*fp2;
   int no_lns;
   RULE **rule;
   char c,s[3];
   int i;
   int get_lines(FILE *);
   int get_rule(char *);
   void sort_h(RULE **,int);
   void sort_h1(RULE **,int);
   void select_h(RULE **,int);
   float full_cov,ac_cov;
   
   fp1=fopen("rule.dat","r");
   fp2=fopen("confusion.dat","a+");
   no_lns=get_lines(fp1);
   
   rule = (RULE **)malloc(no_lns*sizeof(RULE *));
   for(i=0;i<no_lns;i++)
     rule[i] = (RULE *)malloc(sizeof(RULE));

   i =0;
   do {
      do {
        c=fgetc(fp1);
      } while(c==' ' && !feof(fp1));
      ungetc((int)c,fp1);
      if(fscanf(fp1,"%c",&c)<0) break;
      ungetc((int)c,fp1);
      rule[i]->no=0;
      do {
          do {
            c=fgetc(fp1);
          } while(c==' ' && !feof(fp1));
          ungetc((int)c,fp1); 

         if(!isdigit((int)c)) {
            fscanf(fp1,"%s",s);
            rule[i]->rule_no[rule[i]->no++]=get_rule(s);
         }
         else {
            fscanf(fp1,"%d",&rule[i]->class); 
            fscanf(fp1,"%d",&rule[i]->freq); 
            break;
         }   
      }while(!feof(fp1));
      i++;
   }while(i<no_lns && !feof(fp1));

   sort_h(rule,no_lns); 
   sort_h1(rule,no_lns); 
   select_h(rule,no_lns);

/* calculating the coverage measure of the rules   */
   full_cov =0.;
   ac_cov =0.;
   for(i=0;i<no_lns;i++) {
     if(rule[i]->class<=NO_CLASS)
         ac_cov+=(float)rule[i]->freq;
     full_cov+=(float)rule[i]->freq;
   }
   printf("COVERAGE =  %f\n",ac_cov/full_cov); 
   fprintf(fp2, "%f \n",ac_cov/full_cov); 

   for(i=0;i<no_lns;i++)
      free(rule[i]);
   free(rule);
   fclose(fp1);
   fclose(fp2);
}   


int get_rule(char *s) {
   int clas;
   clas =50;
   if(!strcmp(s,"L1")) clas=1; 
   if(!strcmp(s,"M1")) clas=2; 
   if(!strcmp(s,"H1")) clas=3; 
   if(!strcmp(s,"L2")) clas=4; 
   if(!strcmp(s,"M2")) clas=5; 
   if(!strcmp(s,"H2")) clas=6; 
   if(!strcmp(s,"L3")) clas=7; 
   if(!strcmp(s,"M3")) clas=8; 
   if(!strcmp(s,"H3")) clas=9; 
   if(!strcmp(s,"L4")) clas=10; 
   if(!strcmp(s,"M4")) clas=11; 
   if(!strcmp(s,"H4")) clas=12; 
   if(!strcmp(s,"L5")) clas=13; 
   if(!strcmp(s,"M5")) clas=14; 
   if(!strcmp(s,"H5")) clas=15; 
   if(!strcmp(s,"L6")) clas=16; 
   if(!strcmp(s,"M6")) clas=17; 
   if(!strcmp(s,"H6")) clas=18; 
   if(!strcmp(s,"L7")) clas=19; 
   if(!strcmp(s,"M7")) clas=20; 
   if(!strcmp(s,"H7")) clas=21; 
   if(!strcmp(s,"L8")) clas=22; 
   if(!strcmp(s,"M8")) clas=23; 
   if(!strcmp(s,"H8")) clas=24; 
   if(!strcmp(s,"L9")) clas=25; 
   if(!strcmp(s,"M9")) clas=26; 
   if(!strcmp(s,"H9")) clas=27; 
   if(!strcmp(s,"~L1")) clas=-1; 
   if(!strcmp(s,"~M1")) clas=-2; 
   if(!strcmp(s,"~H1")) clas=-3; 
   if(!strcmp(s,"~L2")) clas=-4; 
   if(!strcmp(s,"~M2")) clas=-5; 
   if(!strcmp(s,"~H2")) clas=-6; 
   if(!strcmp(s,"~L3")) clas=-7; 
   if(!strcmp(s,"~M3")) clas=-8; 
   if(!strcmp(s,"~H3")) clas=-9; 
   if(!strcmp(s,"~L4")) clas=-10; 
   if(!strcmp(s,"~M4")) clas=-11; 
   if(!strcmp(s,"~H4")) clas=-12; 
   if(!strcmp(s,"~L5")) clas=-13; 
   if(!strcmp(s,"~M5")) clas=-14; 
   if(!strcmp(s,"~H5")) clas=-15; 
   if(!strcmp(s,"~L6")) clas=-16; 
   if(!strcmp(s,"~M6")) clas=-17; 
   if(!strcmp(s,"~H6")) clas=-18; 
   if(!strcmp(s,"~L7")) clas=-19; 
   if(!strcmp(s,"~M7")) clas=-20; 
   if(!strcmp(s,"~H7")) clas=-21; 
   if(!strcmp(s,"~L8")) clas=-22; 
   if(!strcmp(s,"~M8")) clas=-23; 
   if(!strcmp(s,"~H8")) clas=-24; 
   if(!strcmp(s,"~L9")) clas=-25; 
   if(!strcmp(s,"~M9")) clas=-26; 
   if(!strcmp(s,"~H9")) clas=-27; 
   return(clas); 
}



void select_h(RULE **rule,int no_lns) {
   int j;
   int prev,curr;
   FILE *fp;
   
   fp=fopen("selrule.dat","w");
   curr =0;
   prev =0;
   while(curr<no_lns) {
      if(rule[curr]->class >= 10) break;
      fprintf(fp,"%3d ",rule[curr]->no);
      for(j=0;j<rule[curr]->no;j++) 
         fprintf(fp,"%3d ",rule[curr]->rule_no[j]);
      for(j=rule[curr]->no;j<10;j++) 
         fprintf(fp,"    ");
      fprintf(fp,"%d ",rule[curr]->class);
      fprintf(fp,"%d \n",rule[curr]->freq);
      prev =curr;
      while(curr < no_lns && rule[curr]->class==rule[prev]->class) 
curr++;
    };
   fclose(fp);
 }


void sort_h1(RULE **rule,int no_lns) {
   int i,j;
   int prev,curr;
   RULE *temp;
   
   curr =0;
   prev =0;
   while(curr<no_lns) {
      prev=curr;
      while(curr < no_lns && rule[curr]->class==rule[prev]->class) 
curr++;
      for(j=curr-1;j>prev;j--)
         for(i=prev;i<j;i++)
            if(rule[i]->freq<rule[i+1]->freq) {
	      temp=rule[i];
              rule[i]=rule[i+1];
              rule[i+1]=temp;
            }
    };
 }

void sort_h(RULE **rule,int no_lns) {
   int i,j;
   RULE *temp;
   for(j=no_lns-1;j>0;j--)
      for(i=0;i<j;i++)
        if(rule[i]->class>rule[i+1]->class) {
	  temp=rule[i];
          rule[i]=rule[i+1];
          rule[i+1]=temp;
        }
 }
/*
int get_lines(FILE *fpin) {
	int no_lns = 0;
	do {
	   if(fgetc(fpin)=='\n')
	     no_lns++;
	}while(!feof(fpin));
	rewind(fpin);
	return(no_lns);
} 
 */
