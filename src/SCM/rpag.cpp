#include <cstdio>
#include "rpag.h"
#define MAX_N 1<<24


int que[MAX_N];
int used[MAX_N];

char op[MAX_N];
int op1[MAX_N];
int op2[MAX_N];
int start = 0;
int fin;

void init(){
  que[0] = 1;
  op[0] = 1;
  used[1] = 1;
  fin++;
}
void printRes(int n){
   for(int i=1;i<n;i++){
    printf(" %c (%d,%d)\n",op[i],op1[i],op2[i]);
   }
}


int rec_fill(int n, int rec_level){

 // printf("%d,%d\n",n,rec_level);
 // printRes(10);
 if(rec_level>n) return 0;

   int k = start;
   int r = rec_level;
  // printf("2nnnnnnnnnn");
   while(k<rec_level){
      int use = que[k++];
      int i=1;
     // printf("%d",use);
      while (use<n){
         i++;
         use<<=1;
         if(used[use]) continue;
         op[use] = 2;
         op1[use] = que[k-1];
         op2[use] = i;
         used[use] = 1;
         que[r++] = use;
      }
   }
   //printf("f %d",rec_level);
  //printRes(n);


// printf("MMMMMMMMMMMMMMMMMM");
   for(int i=start;i<rec_level-1;i++){
      for(int j=i+1;j<rec_level;j++){
          //printf("S:(%d,%d,%d)\n",i,j,r);

          int tmp1 = que[i] + que[j];
          if((!used[tmp1]) && (tmp1<n) ) {
                op[tmp1] = 3;
                op1[tmp1] = que[i];
                op2[tmp1] = que[j];
                used[tmp1] = 1;
                que[r++] = tmp1;
          }
          tmp1 = que[i] - que[j];
          if((tmp1>0) && (!used[tmp1])) {
                op[tmp1] = 4;
                op1[tmp1] = que[i];
                op2[tmp1] = que[j];
                used[tmp1] = 1;
                que[r++] = tmp1;
          }
          tmp1 = que[j] - que[i];
          if((tmp1>0) && (!used[tmp1])) {
                op[tmp1] = 4;
                op1[tmp1] = que[j];
                op2[tmp1] = que[i];
                used[tmp1] = 1;
                que[r++] = tmp1;
          }
     }

   }

   fin = r;
   return rec_fill(n,r);
}

int getExpr(int m, char* ops, int* fst, int* sec, int k){

     if(m<=1) return 1;
     ops[k] = op[m];
     fst[k] = op1[m];
     sec[k] = op2[m];
     int l =2*k+1;
     int r =2*k+2;
     if(ops[k]>=3){
        getExpr(fst[k],ops+l,fst+l,sec+l,l);
        getExpr(sec[k],ops+r,fst+r,sec+r,r);
     }
     return 1;
}


int getNumber(int m, char* ops, int* fst, int* sec, int k){

     if(m<=1) return 1;
     char oper = op[m];
     if(oper==2){
        return getNumber(op1[m],ops,fst,sec,k)<<op2[m];
     }
     else if(oper==3){
        return getNumber(op1[m],ops,fst,sec,k) + getNumber(op2[m],ops,fst,sec,k);
     }
     else if(oper==4){
        return getNumber(op1[m],ops,fst,sec,k) - getNumber(op2[m],ops,fst,sec,k);
     }
     else if(oper==5){
        return getNumber(op2[m],ops,fst,sec,k) - getNumber(op1[m],ops,fst,sec,k);
     }

     return 1;
}

int getNumber2(int n,char* ops, int* fst, int* sec, int k){

     if(k>=n) return 0;
     char oper = ops[k];

     if(oper==2){
        return getNumber(fst[k],ops,fst,sec,2*k+1)<<sec[k];
     }
     else if(oper==3){
        return getNumber(fst[k],ops,fst,sec,2*k+1) + getNumber(sec[k],ops,fst,sec,2*k+2);
     }
     else if(oper==4){
        return getNumber(fst[k],ops,fst,sec,2*k+1) - getNumber(sec[k],ops,fst,sec,2*k+2);
     }
     else if(oper==5){
        return getNumber(sec[k],ops,fst,sec,2*k+2) - getNumber(fst[k],ops,fst,sec,2*k+1);
     }

     return 1;
}

