//Program to generate binary search tree using rand function.
#include<stdio.h>
#include<stdlib.h>
struct node
{
 int info;
 struct node *llink;
 struct node *rlink;
};
typedef struct node *NODE;
NODE getnode()
{
 NODE N;
 N=(NODE)malloc(sizeof(struct node));
 if(N==NULL)
 {
  printf("\n Out of memory ");
  exit(0);
 }
 N->rlink=N->llink=NULL;
 return N;
}
NODE Insert(NODE R,int item)
{
 NODE NN;
 NN=getnode();
 NN->info=item;
 if(R==NULL)
 {
  return NN;
 }
 if(NN->info<R->info)
 {
  if(R->llink==NULL)
   R->llink=NN;
  else Insert(R->llink,NN->info);
 }
 if(NN->info>R->info)
 {
  if(R->rlink==NULL)
   R->rlink=NN;
  else Insert(R->rlink,NN->info);
 }
 return R;
}
void Inorder(NODE R)
{
 if(R==NULL)
  return;
 Inorder(R->llink);
 printf(" %d\t ",R->info);
 Inorder(R->rlink);
}
void Preorder(NODE R)
{
 if(R!=NULL){
  printf(" %d\t ",R->info);
  Preorder(R->llink);
  Preorder(R->rlink);
 }
 return;
}
void Postorder(NODE R)
{
 if(R==NULL) return;
 Postorder(R->llink);
 Postorder(R->rlink);
 printf(" %d\t ",R->info);
}
main()
{
 NODE Root=NULL;
 int ch;
 int n,i,item;
 for(;;)
 {
  printf("\n Enter choice:\n 1.Insert\n 2.Inorder\n 3.Preorder\n 4.Postorder\n 5.Exit\n ");
  scanf("%d",&ch);
  switch(ch)
  {
   case 1:printf("\n Enter number of nodes ");
          scanf("%d",&n);
          for(i=0;i<n;i++)
          {
           item=rand()%100;
           Root=Insert(Root,item);
          }
          break;
   case 2:printf("\n Inorder traversal is:\n ");
          Inorder(Root);
          break;
   case 3:printf("\n Preorder traversal is:\n ");
          Preorder(Root);
          break;
   case 4:printf("\n Postorder traversal is:\n ");
          Postorder(Root);
          break;
   default:exit(0);
  }
 }
}
