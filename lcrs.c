//Program that implements left child right sibling.
#include<stdio.h>
#include<stdlib.h>
static int gName=0;
struct node
 {
 int info;
 struct node *llink;
 struct node *rchild;
 };
 typedef struct node *NODE;
 NODE q=NULL;             //NODE q indicates the parent of a node p ,if input is given in q->p format
NODE getnode()
{
 NODE N;
 N=(NODE)malloc(sizeof(struct node));
 if(N==NULL)
 {
  printf("no space in memory\n");
  exit(0);
 }
 N->llink=NULL;
 N->rchild=NULL;
 return N;
}
//This function searches for appropriate node q to which a node must be inserted as child
void search(NODE R,int key)
{
   if(R==NULL)
   {
    return;
   }
   if(R->info==key)
   {
    q=R;
    return;
   }
   search(R->llink,key); //searching reursively in left subtree
   if(R->rchild!=NULL)
   {
   search(R->rchild,key);
   R=R->rchild;
   }
}
NODE insert(int info1,int info2,NODE root){
 NODE temp1;
 if(root==NULL){
 NODE temp2;
 temp1=getnode();
 temp2=getnode();
 temp1->info=info1;
 temp2->info=info2;
 root=temp1;
 temp1->llink=temp2;
 return root;
 }
 q=NULL;
 search(root,info1);
 if(q==NULL){
 printf("Error condition!Insertion not possible!\n");
 return root;
 }
 if(q->llink==NULL){ // this implies that node is the first child of q and hence inserting to its left
 temp1=getnode();
 temp1->info=info2;
 q->llink=temp1;
 return root;
 }
 q=q->llink;          // if node to be inserted is not the first child of q traverse right.
 while(q->rchild!=NULL){
  q=q->rchild;
  }
  temp1=getnode();
  temp1->info=info2;
  q->rchild=temp1;
  return root;
  }
  void preorderDotDump (NODE R, FILE* outputFile)
{
	if (R != NULL)
	{
		fprintf (outputFile, "%d [label=%d,color=black];\n",R->info, R->info);
		if (R->llink != NULL)
		         fprintf (outputFile, "%d -> %d;\n", R->info, (R->llink)->info);

        	if (R->rchild != NULL)
            		fprintf (outputFile, "%d -> %d;\n", R->info, (R->rchild)->info);
        	preorderDotDump (R->llink, outputFile);
        	if(R->rchild!=NULL)
        	{
        	preorderDotDump (R->rchild, outputFile);
        	R=R->rchild;
    	}
    }
}
void dotDump(NODE R, FILE *outFile)
{
	gName++;
	fprintf (outFile, "digraph BST {\n",gName);
	preorderDotDump (R, outFile);
    	fprintf (outFile, "}\n");
}
FILE *OutputFile;
   void display(NODE F){
    if(F==NULL) return;
    printf("%d\t",F->info);
    display(F->llink);
    if(F->rchild!=NULL){
    display(F->rchild);
    F=F->rchild;
    }
    }
   main(){
    FILE *pipe;
    int ch,n,i,l,m;
    NODE R=NULL;
    printf("Enter the no. of nodes\n");
    scanf("%d",&n);
    OutputFile = fopen ("lcrs.dot", "w");
    fclose (OutputFile);
    while(1){
    printf("\nEnter the choice :1-Insert\t2-display\t3-exit\n");
    scanf("%d",&ch);
    switch(ch){
    case 1:for(i=0;i<n;i++){
            printf("Enter in l->m format\n");
            scanf("%d%d",&l,&m);
            R=insert(l,m,R);
            }
            break;
    case 2:display(R);
     OutputFile=fopen("lcrs.dot","a");
	if(OutputFile != NULL)
        {
         dotDump(R,OutputFile);
	}
	fclose(OutputFile);
        pipe=popen("dot -Tps lcrs.dot -o lcrs.ps","w");
	pclose(pipe);
	pipe=popen("evince lcrs.ps","r");
	pclose(pipe);
        break;
      default:exit(0);
      }

      }
      }



