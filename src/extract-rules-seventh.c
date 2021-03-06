
 /*   THIS PROGRAM WRITES OUT THE RULES FROM THE PRUNED ID3  */
#include "header.h"


extern NODEPTR rootnode;
void popg();
void pushg(int ); 
void write_rule();
FILE *fpout;
int seventh() {
     void freenode(NODEPTR);
     void rules(NODEPTR);
      
     fpout = fopen("rule.dat","w");
/* initialise stack    */
     rulestack.top=0;

     rules(rootnode);


     freenode(rootnode);

     fclose(fpout); 
    
     return(0);
}


/*  function to extract the rules  */
void rules(NODEPTR root) {
        void write_rule(NODEPTR);
        if(root==NULL) return;  
        if((root->leftptr==NULL)&&(root->rightptr==NULL)) { 
           write_rule(root); 
           return;
         }
       
         pushg(root->atrib+1); 
         rules(root->rightptr);
         popg();

         pushg(-(root->atrib+1)); 
	 rules(root->leftptr); 
         popg();
}

/* writes a rule into the rule file  */
void write_rule(NODEPTR root) {
        int i,j;
        char *str="   ";
        for(i=0;i<rulestack.top;i++) {
           switch(rulestack.array[i]) {
               case 1: str=" L1";
                       break; 
               case 2: str=" M1";
                       break; 
               case 3: str=" H1";
                       break; 
               case 4: str=" L2";
                       break; 
               case 5: str=" M2";
                       break; 
               case 6: str=" H2";
                       break; 
               case 7: str=" L3";
                       break; 
               case 8: str=" M3";
                       break; 
               case 9: str=" H3";
                       break; 
               case 10: str=" L4";
                       break; 
               case 11: str=" M4";
                       break; 
               case 12: str=" H4";
                       break; 
               case 13: str=" L5";
                       break; 
               case 14: str=" M5";
                       break; 
               case 15: str=" H5";
                       break; 
               case 16: str=" L6";
                       break; 
               case 17: str=" M6";
                       break; 
               case 18: str=" H6";
                       break; 
               case 19: str=" L7";
                       break; 
               case 20: str=" M7";
                       break; 
               case 21: str=" H7";
                       break; 
               case 22: str=" L8";
                       break; 
               case 23: str=" M8";
                       break; 
               case 24: str=" H8";
                       break; 
               case 25: str=" L9";
                       break; 
               case 26: str=" M9";
                       break; 
               case 27: str=" H9";
                       break; 
               case -1: str="~L1";
                       break; 
               case -2: str="~M1";
                       break; 
               case -3: str="~H1";
                       break; 
               case -4: str="~L2";
                       break; 
               case -5: str="~M2";
                       break; 
               case -6: str="~H2";
                       break; 
               case -7: str="~L3";
                       break; 
               case -8: str="~M3";
                       break; 
               case -9: str="~H3";
                       break;
               case -10: str="~L4";
                       break; 
               case -11: str="~M4";
                       break; 
               case -12: str="~H4";
                       break; 
               case -13: str="~L5";
                       break; 
               case -14: str="~M5";
                       break; 
               case -15: str="~H5";
                       break; 
               case -16: str="~L6";
                       break; 
               case -17: str="~M6";
                       break; 
               case -18: str="~H6";
                       break; 
               case -19: str="~L7";
                       break; 
               case -20: str="~M7";
                       break; 
               case -21: str="~H7";
                       break; 
               case -22: str="~L8";
                       break; 
               case -23: str="~M8";
                       break; 
               case -24: str="~H8";
                       break; 
               case -25: str="~L9";
                       break; 
               case -26: str="~M9";
                       break; 
               case -27: str="~H9";
                       break; 
               default: str="  ";
                       break; 
            }
           fprintf(fpout,"%s ",str);
        }
        for(j=i;j<NO_ATRIB*3;j++)
           fprintf(fpout,"    ");
        fprintf(fpout,"%5d   ",root->class);
        fprintf(fpout,"%d \n",root->right-root->left);

}


/* pops the stack by one */
void popg() {
    rulestack.top--;
}

/* pushes a value into the stack */
void pushg(int val) {
    rulestack.array[rulestack.top++]=val;
}


/* freeing the memory held by the decision tree */
void freenode(NODEPTR rootnode) {
    if(rootnode ==NULL)
        return;
    freenode(rootnode->leftptr);
    freenode(rootnode->rightptr);
    free(rootnode);
}

