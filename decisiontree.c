//To build decision tree for a given data set .
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
float gini[20]; //keeps the gini indices of test conditions 
int n;   
struct data       //this structure is used to represent dataset
{
 char attribute[20][20]; //the table is stored as a structure having attribute and corresponding value
 char val[20][20];
};
typedef struct data DATA;
DATA d[20];
DATA new[20];    //new[] is used to hold new dataset table
struct node
{
 struct node *link[20];
 char testlabel[20];  //stores the testcondition/attribute for which gini index is maximum or class label
 int count;           //to hold attribute (in case of internal node)or class label (in case of leaf node)
};
typedef struct node *NODE;
struct attribute
{
  char name[20];   //holds the name of attribute
  int cnt;         //cnt holds the number of types an attribute can have
  char type[20][20];   //this holds the names attribute types .ex- cartype has types family,sports,luxury.
};
typedef struct attribute ATTR;
NODE getnode()
{
 NODE N;
 int i;
 N=(NODE)malloc(sizeof(struct node));
 if(N==NULL)
 {
  printf("No space in memory\n");
  exit(0);
 }
 for(i=0;i<n;i++)
 {
  N->link[i]=NULL;
 }
 return N;
}
void outcome(ATTR a[],int size)  //This function determines the no of types under each attribute and assigns the types to type[][] array
{
int flag=0,i,j,k;
for(j=0;j<n;j++) // loop for itrating through different attributes
  for(i=0;i<size;i++) //loop for traversing the table rows
  {
    if(strcmp(d[i].attribute[j],a[j].name)==0)  
    {
     flag=0;
     if(a[j].cnt==0) //Initially when type[][] array doesnt hold any types corresponding to attribute a[j].name
     {
      strcpy(a[j].type[a[j].cnt],d[i].val[j]);
      a[j].cnt++;
     }
     else
     {
      for(k=0;k<a[j].cnt;k++)
      {
       if(strcmp(a[j].type[k],d[i].val[j])==0)
       {
        flag=1;
        break;
       }
      }
      if(flag!=1)
      {
       strcpy(a[j].type[a[j].cnt],d[i].val[j]);
       a[j].cnt++;
      }
     }
    }
  }
}     
}
int stopping(DATA D[20],int size) //this fuction returns 1 if the class lables of table D are same
{
 int i,m;
 char *c;
 c=D[0].val[n-1];
 for(i=1;i<size;i++)
 {
  if(strcmp(c,D[i].val[n-1])!=0)
    return 0;
 }
 return 1;
}
int findbestsplit(DATA M[20],int size,ATTR a[]) /*Determines the test condition or attribute for which best split is achieved(minimum gini index).and returns the corresponding index of attribute*/                                     
{
  int i,j,k,p,l,z,v;
  float g[20],sum[20],coun[10],pr=0,min=1; /*g[] holds the intermediate gini indice of each type under attribute and coun[]holds total no. of values belonnging to each class*/
  for(i=0;i<(n-1);i++) //for attribute
  {
  gini[i]=0;
   for(j=0;j<a[i].cnt;j++) //for types under each attribute
   {
    sum[j]=0;
    for(z=0;z<5;z++) 
    {
     coun[z]=0;
    }
    for(k=0;k<size;k++) //for tabel
    {
     if(strcmp(M[k].val[i],a[i].type[j])==0)
     {
      for(p=0;p<a[n-1].cnt;p++)
      {
     
       if(strcmp(M[k].val[n-1],a[n-1].type[p])==0)
       {
        coun[p]++;
        sum[j]++;
       }
      }
     }
    }
    for(l=0;l<a[n-1].cnt;l++)
    {
     if(sum[j]!=0)
     {
      pr=pr+pow((coun[l]/sum[j]),2);
     }
    }
    g[j]=1-pr;
    pr=0;
   }
   for(j=0;j<a[i].cnt;j++)
   {
    gini[i]=gini[i]+g[j]*(sum[j]/size); 
   }
 }
 v=0;
 min=gini[0];
 for(i=1;i<(n-1);i++) //finding attribute having minimum gini index.
 {
   if(gini[i]<min)
   {
    min=gini[i];
    v=i;
   }
 }
 return v;
} 
NODE treegrowth(DATA D[20],int size,ATTR a[]) //this function is recursively called to build decision tree
{
 int x,i,j,k,l,m,y;
 NODE NN,Root,c;
 x=stopping(D,size);
 if(x==1)
 {
  NN=getnode();
  strcpy(NN->testlabel,D[0].val[n-1]);
 return NN;
}
else
{
  Root=getnode();
  m=findbestsplit(D,size,a);
  strcpy(Root->testlabel,a[m].name);   //assigning the test condition to newly created node corresponding to index m.
  for(i=0;i<(n-1);i++)
  {
   if(strcmp(Root->testlabel,a[i].name)==0)
   {
    for(j=0;j<a[i].cnt;j++)
    {
     k=0;
     for(l=0;l<size;l++)
     {
      if(strcmp(a[i].type[j],D[l].val[i])==0)
      {
       for(y=0;y<n;y++)
       {
        strcpy(new[k].val[y],D[l].val[y]);
        strcpy(new[k].attribute[y],D[l].attribute[y]);
       }
       k++;
      }
     }
    c=treegrowth(new,k,a);
    Root->link[Root->count]=c;
    Root->count++;
   }
  }
 }
 return Root;
}
}
void display(NODE R)  // recursive function to display the decision tree.
{
int i;
 if(R==NULL)
 {
  printf("Tree doesn't exist\n");
  return;
 }
 printf("%s\n",R->testlabel);
 for(i=0;i<(R->count);i++)
 {
  display(R->link[i]);
 }
}
main()
{
 NODE R=NULL;
 ATTR a[20];
 int i,j,size;
 printf("Reading data set from file\n");
 scanf("%d",&n);
 scanf("%d",&size);
 for(i=0;i<n;i++) // different attributes are stored in array a[].name
 {
   a[i].cnt=0;
   scanf("%s",a[i].name);
 }
 for(j=0;j<size;j++) //reading data set from file
 {
   for(i=0;i<n;i++)
   {
    scanf("%s",d[j].val[i]);
    strcpy(d[j].attribute[i],a[i].name);
   }
 }      
 for(i=0;i<n;i++)
 {
   printf("%s\t\t",a[i].name);
 }
 printf("\n");
 for(i=0;i<size;i++)
 {
   for(j=0;j<n;j++)
   {
    printf("%s\t\t",d[i].val[j]);
   }
   printf("\n");
 }
  outcome(a,size); //outcome function is called to determine the no. of types of each attribute.  
 for(i=0;i<n;i++)
 {
  printf("%s\n",a[i].name);
  for(j=0;j<a[i].cnt;j++)
  {
   printf("%s\n",a[i].type[j]); //this prints the types under different attributes.
  }
 }
 R=treegrowth(d,size,a);      
 printf("\n");      
  display(R);
}
