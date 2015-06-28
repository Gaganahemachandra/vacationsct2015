#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float co[10],cosine;
int i,j,k,user[943][1682];
struct node
{
  int head;
  int array[10];
  struct node *link;
  int cnt;
};
typedef struct node *NODE;
NODE R=NULL;
NODE getnode()
{
  NODE N;
  N=(NODE)malloc(sizeof(struct node));
  if(N==NULL)
  {
   printf("No space in memory\n");
   exit(0);
  }
  N->link=NULL;
  N->cnt=0;
  return N;
}
NODE insert(NODE NN)
{
 NODE T;
 if(R==NULL)
 {
  return NN;
 }
 T=R;
 while(T->link!=NULL)
 {
   T=T->link;
 }
 T->link=NN;
 return R;
}
void cosinecompute()
{
 NODE NN;
 float min=1;
 int v;
 float sqr1,sqr2,sum;
 for(i=0;i<943;i++)
 {
  NN=getnode();
  NN->head=i;
  for(j=0;j<943;j++)
  {
   sqr1=sqr2=0;
   sum=0;
   if(i==j)
   {
    continue;
   }
   for(k=0;k<1682;k++)
   {
    if(user[i][k]!=0)
    {
     sqr1=sqr1+(user[i][k]*user[i][k]);
    }
    if(user[j][k]!=0)
    {
      sqr2=sqr2+(user[j][k]*user[j][k]);
    }
    if((user[i][k]!=0)&&(user[j][k]!=0))
    {
     sum=sum+(user[i][k]*user[j][k]);
    }
   }
   cosine=(sum/sqrt(sqr1*sqr2));
   if(NN->cnt<10)
   {
    NN->array[NN->cnt]=j;
    co[NN->cnt]=cosine;
    NN->cnt++;
   }
   else
   {
     min=1;
    for(k=0;k<10;k++)
    {
     if(co[k]<min)
     {
      min=co[k];
      v=k;
     }
    }
    if(co[v]<cosine)
    {
     NN->array[v]=j;
     co[v]=cosine;
    }
   }
  }
  R=insert(NN);
}
}
void recommend(int u)
{
 NODE T;
 T=R;
 int count,ind;
 while(T!=NULL)
 {
  if((T->head)==u)
  {
   for(k=0;k<1682;k++)
   { 
    count=0;
    for(j=0;j<10;j++)
    {
     ind=T->array[j];    
     if((user[u][k]==0)&&(user[ind][k]!=0))
     {
      count++;
     }
    }
    if(count>6)
    {
     printf("User %d is recommended movie %d\n",u,k);
    }
   }
   break;
  }
  else
  {
   T=T->link;
  }
 }
}
    
void display()
{
 NODE T=R;
 while(T!=NULL)
 {
 printf("10 nearest neighbours of user %d\n",T->head);
  for(i=0;i<10;i++)
  {
   printf("%d\t",T->array[i]);
  }
  T=T->link;
  printf("\n");
 }
}  
main()
{
 int us,mov,ratg,ju,u;
 for(i=0;i<100000;i++)
 {
  scanf("%d%d%d%d",&us,&mov,&ratg,&ju);
  user[us-1][mov-1]=ratg;
 }
 cosinecompute();
 display();
 //printf("Enter the user for which recommendations is needed\n");
 //scanf("%d",&u);
 recommend(2);
}
