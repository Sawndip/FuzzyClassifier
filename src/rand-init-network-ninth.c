/*    THIS PROGRAM USES A THREE LAYER RANDOMLY INITIALISED NEURAL NETWORK
     TO CLASSSIFY THE PATTERNS  */

#include "header.h"

void ninth()  {
   /*time_t t; */
   int i,j,k;
   long iter;
   int link_count;
   double conf[OUTPUT][OUTPUT];
   double oi[INPUT+1],oj[HIDDEN+1],ok[OUTPUT],tar[OUTPUT];
   double wj[HIDDEN][INPUT+1],wk[OUTPUT][HIDDEN+1];
   int **flag_wj,**flag_wk;
   double dwj[HIDDEN][INPUT+1],dwk[OUTPUT][HIDDEN+1];
   double odwj[HIDDEN][INPUT+1];
   double delta_j[HIDDEN+1],delta_k[OUTPUT];
   PATTERN_I **patt,**train,**test;
   FILE *fp,*fq,*fr;
   int no_lns1,no_lns2;
   int train_size,test_size;
   int get_lines(FILE *);
   double theta_0=1.;
   double eta=.5;
   double alpha=.3;
   double Error=0.;

/* function declarations   */
   void flagset_i(int **,int **);

/* temporary variables   */
   double net;
   PATTERN_I *temp_pat;
   int ran1,ran2;
   double tot;
   double max_val;
   int max_class = -1;

/* allocate space for the flags */
   flag_wj=(int **)malloc(HIDDEN*sizeof(int *));
   for(i=0;i<HIDDEN;i++)
     flag_wj[i]=(int *)malloc(sizeof(int)*(INPUT+1));

   flag_wk=(int **)malloc(sizeof(int *)*OUTPUT);
   for(i=0;i<OUTPUT;i++)
     flag_wk[i]=(int *)malloc(sizeof(int)*(HIDDEN+1));
/* set the flags    */
   flagset_i(flag_wj,flag_wk);

/* open the files  */
   fp=fopen("inmem.dat","r"); 
   fq=fopen("inmemtest.dat","r"); 
   fr=fopen("ornres.dat","a"); 
   no_lns1=get_lines(fp);
   no_lns2=get_lines(fq);
   train_size = no_lns1;
   test_size = no_lns2;
/* allocate memory location for test and train patterns */
   patt=(PATTERN_I **)malloc((no_lns1+no_lns2)*sizeof(PATTERN_I *));
   for(i=0;i<no_lns1+no_lns2;i++)
      patt[i]=(PATTERN_I *)malloc(sizeof(PATTERN_I));

   train=(PATTERN_I **)malloc(train_size*sizeof(PATTERN_I *));

   test=(PATTERN_I **)malloc(test_size*sizeof(PATTERN_I *));
/* read the patterns */
   k=0;
   do {
      if(fscanf(fp,"%d",&patt[k]->class)<0)
        break;  
      for(i=0;i<INPUT;i++)
        fscanf(fp,"%lf",&patt[k]->atrib[i]);
      k++;
   }while(!feof(fp));
   fclose(fp);
  
   do {
      if(fscanf(fq,"%d",&patt[k]->class)<0)
        break;  
      for(i=0;i<INPUT;i++)
        fscanf(fq,"%lf",&patt[k]->atrib[i]);
      k++;
   }while(!feof(fq));
   fclose(fq);


/* seperate the trainig and test set */
   for(i=0;i<train_size;i++) 
      train[i]=patt[i];
   for(i=train_size;i<no_lns1+no_lns2;i++) 
      test[i-train_size]=patt[i];

/* initialize the weights initially */
   oi[INPUT] =1.;
   oj[HIDDEN]=1.;
   
   for(i=0;i<HIDDEN;i++)    /* for wj */
     for(j=0;j<=INPUT;j++) 
        wj[i][j] = (float)rand()/(float)RAND_MAX-.5; 
     

   for(i=0;i<OUTPUT;i++)    /* for wk */
     for(j=0;j<=HIDDEN;j++)  
        wk[i][j] = (float)rand()/(float)RAND_MAX-.5;  


      
 /* calculates the delta weights changes   */
   for(k=0;k<OUTPUT;k++)
      for(j=0;j<=HIDDEN;j++)
         dwk[k][j]=0.;
   for(j=0;j<HIDDEN;j++)
      for(k=0;k<=INPUT;k++)
         dwj[j][k]=0.;

/*   this loops trains the network    */
 iter =0; 
 do {
   Error=0.;
   for(i=0;i<train_size;i++)  {
       /* updates the weights   */
       for(k=0;k<OUTPUT;k++)
         for(j=0;j<=HIDDEN;j++)
           wk[k][j]+=dwk[k][j];
       for(j=0;j<HIDDEN;j++)
         for(k=0;k<=INPUT;k++)
           wj[j][k]+=dwj[j][k];

       /*neutralising the weights  */
       for(j=0;j<HIDDEN;j++)
         for(k=0;k<INPUT+1;k++)
            if(flag_wj[j][k]==0)
               wj[j][k]=0.;

       for(j=0;j<OUTPUT;j++)
         for(k=0;k<HIDDEN+1;k++)
            if(flag_wk[j][k]==0)
               wk[j][k]=0.;

       /* reads a pattern */
       for(j=0;j<OUTPUT;j++)
          tar[j]=.1;
       tar[train[i]->class]=.9;
       for(j=0;j<INPUT;j++)
          oi[j]=train[i]->atrib[j];

       /* calculates the net for hidden layer */
       for(j=0;j<HIDDEN;j++) {
          net =0.;
          for(k=0;k<=INPUT;k++)
             net+= wj[j][k]*oi[k];
          net = -net/theta_0;
          oj[j] = 1./(1.+exp(net));
       } 

       /* calculates the net for output layer */
       for(j=0;j<OUTPUT;j++) {
          net =0.;
          for(k=0;k<=HIDDEN;k++)
             net+= wk[j][k]*oj[k];
          net = -net/theta_0;
          ok[j] = 1./(1.+exp(net));
       } 
  /* printf("Trang %d %f %f %f %f 
%f\n",train[i]->class,ok[0],ok[1],ok[2],ok[3],ok[4],ok[5]); 
  */
   /* calculates the deltas of output layer */
       for(j=0;j<OUTPUT;j++)   
          delta_k[j]=(tar[j]-ok[j])*ok[j]*(1.-ok[j]);

       /* calculates the deltas of hidden layer */
       for(j=0;j<=HIDDEN;j++)  {
          delta_j[j]=0.;
          for(k=0;k<OUTPUT;k++)
             delta_j[j]+= delta_k[k]*wk[k][j];
          delta_j[j]*=oj[j]*(1.-oj[j]);
       }
       /* stores the old delta weights */ 
       for(j=0;j<HIDDEN;j++)
         for(k=0;k<=INPUT;k++)
           odwj[j][k]=dwj[j][k];

       /* calculates the delta ws   */
       for(k=0;k<OUTPUT;k++)
         for(j=0;j<=HIDDEN;j++)
           dwk[k][j]=eta*delta_k[k]*oj[j];
       for(j=0;j<HIDDEN;j++)
         for(k=0;k<=INPUT;k++)
           dwj[j][k]=eta*delta_j[j]*oi[k]+alpha*odwj[j][k];
       
       /* Calculate the sytem error */
       for(k=0;k<OUTPUT;k++) 
         Error+= .5*pow((tar[k]-ok[k]),2);
    }  /* end of no_lns for loop */

  /* shuffle the train set */
   for(i=0;i<100*train_size;i++) {
      ran1=train_size*(int)((float)rand()/((float)RAND_MAX+1.));
      ran2=train_size*(int)((float)rand()/((float)RAND_MAX+1.));
      temp_pat = train[ran1];
      train[ran1]=train[ran2];
      train[ran2]=temp_pat;   
   } 
    
    Error=Error/(float)train_size;
/*    printf("System error is %lf\n",Error); */ 
    iter++;
    if(iter%100 ==0)
       alpha+=.1;
 } while(fabs(Error)>THRESHOLD && iter < ITER);

/* initializing the confusion matrix   */
   for(i=0;i<OUTPUT;i++)
     for(j=0;j<OUTPUT;j++)
        conf[i][j]=0.;

/* classifying the test set and determining the confusion matrix  */
  for(i=0;i<test_size;i++) {
       /* reads a pattern from the test set */
       for(j=0;j<INPUT;j++)
          oi[j]=test[i]->atrib[j]; 

       /* calculates the net for hidden layer */
       for(j=0;j<HIDDEN;j++) {
          net =0.;
          for(k=0;k<=INPUT;k++)
             net+= wj[j][k]*oi[k];
          net = -net/theta_0;
          oj[j] = 1./(1.+exp(net));
       } 
       oj[HIDDEN] = 1.;   
       
       max_val = -1.;
       /* calculates the net for output layer */
       for(j=0;j<OUTPUT;j++) {
          net =0.;
          for(k=0;k<=HIDDEN;k++)
             net+= wk[j][k]*oj[k];
          net = -net/theta_0;
          ok[j] = 1./(1.+exp(net));
          if(max_val<ok[j]) {
             max_val=ok[j];
             max_class = j;
          }
       }
       conf[test[i]->class][max_class]++;
  /*printf("%d %f %f %f %f 
%f\n",test[i]->class,ok[0],ok[1],ok[2],ok[3],ok[4],ok[5]); 
  */ } 
    printf("THE CONFUSION MATRIX:\n" );

   for(i=0;i<OUTPUT;i++) {
     for(j=0;j<OUTPUT;j++)
        printf(" %d ",(int)conf[i][j]);
     printf("\n\n"); 
   }  

   for(i=0;i<OUTPUT;i++) {
     tot=0.;
     for(j=0;j<OUTPUT;j++)
       tot+=conf[i][j];
     tot = 100.*conf[i][i]/tot;
     printf("CLASS %d = %lf\n",i+1,tot); 
     fprintf(fr,"%lf ",tot); 
   }

   tot=0.;
   for(i=0;i<OUTPUT;i++) 
     tot+=conf[i][i];
   tot = 100.*tot/(double)test_size;
   printf("Total percent = %f  in %ld iterations\n",tot,iter);
   fprintf(fr,"%f %ld",tot,iter);
   link_count=0;


   printf("\n");
   printf("WEIGHTS: INPUT ---> HIDDEN LAYER\n");
   for(i=0;i<HIDDEN;i++) {
      for(j=0;j<INPUT+1;j++) {
         if(fabs(wj[i][j])>.5) link_count++;
         printf("%-8.4f ",wj[i][j]);  
      }
      printf("\n");  
   }
   printf("\n");

   printf("WEIGHTS: HIDDEN   ---> OUPUT LAYER\n");
   for(i=0;i<OUTPUT;i++) {
      for(j=0;j<HIDDEN+1;j++) {
         if(fabs(wk[i][j])>.5) link_count++;
         printf("%-8.4f ",wk[i][j]);  
      }
      printf("\n");  
   }
  
   printf("\n# SIGNIFICANT LINKS IN  NETWORK : %d\n",link_count);

   fprintf(fr," %d\n",link_count);

/*  freeing memory  */
   for(i=0;i<HIDDEN;i++)
     free(flag_wj[i]);
   free(flag_wj);

   for(i=0;i<OUTPUT;i++)
     free(flag_wk[i]);
   free(flag_wk);

   for(i=0;i<no_lns1+no_lns2;i++)
      free(patt[i]);
   free(patt);
   free(train);
   free(test); 
   fclose(fr);

}


void flagset_i(int **flag_wj,int **flag_wk) {
   int i,j;
   for(i=0;i<HIDDEN;i++)
      for(j=0;j<INPUT+1;j++)
         flag_wj[i][j]=1;

   for(i=0;i<OUTPUT;i++)
      for(j=0;j<HIDDEN+1;j++)
         flag_wk[i][j]=1;

   for(i=0;i<0;i++)
      for(j=0;j<INPUT+1;j++)
         flag_wj[i][j]=0;

   for(i=0;i<OUTPUT;i++)
      for(j=0;j<0;j++)
         flag_wk[i][j]=0;
 
  

 }
