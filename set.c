//Implementation of sparse set using linked list representation
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node{
    int info;
    int index;
    struct node *link;
};
typedef struct node *NODE;
NODE getnode(){
  NODE NN;
  NN=(NODE)malloc(sizeof(struct node));
  if(NN==NULL){
   printf("No space in memory\n");
   exit(0);
  }
  NN->info=0;
  NN->link=NULL;
  return NN;
}
NODE insert(NODE F,int i){
NODE NN,PN,CN,ind;
int x;
if(F==NULL){ //Initially when the set or list is empty
 NN=getnode();
 x=i%32;
 NN->index=(i/32)*32;
 NN->info=(1<<x)|(NN->info);
 return NN;
}
 ind=(i/32)*32;
 if(ind==F->index){
 x=i%32;
 F->index=ind;
 F->info=(1<<x)|(F->info);
 return F;
}
else if(ind<F->index){ //front insertion in this case
 NN=getnode();
 x=i%32;
 NN->index=ind;
 NN->info=(1<<x)|(NN->info);
 NN->link=F;
 return NN;
}
else{ // for insertion at any position between 1st and last node.
 PN=NULL;
 CN=F;
 while(ind>CN->index){
  PN=CN;
  CN=CN->link;
  if(CN==NULL){
      break;
  }
 }
 if((CN!=NULL)&&(CN->index==ind)){
  x=i%32;
 CN->info=(1<<x)|(CN->info);
 return F;
 }
 else{
   NN=getnode();
 x=i%32;
 NN->index=ind;
 NN->info=(1<<x)|(NN->info);
 NN->link=CN;
 PN->link=NN;
 return F;
 }
}
}
void printset(NODE F){
 int i,x=0,y=0,inf;
 NODE T;
 T=F;
 if(F==NULL){
  printf("Empty set\n");
 }
 while(T!=NULL)
 {
     y=0;
     x=T->index;
     for(i=x;i<(x+32);i++)
     {
        if(((T->info>>y)&1)==1){
           printf("%d\t",i);
        }
          y++;
      }
     T=T->link;
 }
 printf("\n");
}
NODE intersect(NODE F1,NODE F2,NODE F3) {
	NODE m,n;
	m=F1;
	n=F2;
	int b,x,y,o,d,c,i;
	while(m!= NULL && n != NULL) {
		if(m->index == n->index) {
			x=m->index;
			o=0;
			for(i=x;i<x+32;i++) {
				b=m->info;
				c=n->info;
				d=b & c;
				if( ((d >> o) & 1)==1)
					F3=insert(F3,i);
				o++;
			}
			m=m->link;
			n=n->link;
		}
		else if(m->index < n->index)
			m=m->link;
		else
			n=n->link;
	}
	return F3;
}
//Function to perform A-B and B-A ON SETS A nd B
NODE opera(NODE F1,NODE F2,NODE F3) {
	NODE p,q;
	p=F1;
	q=F2;
	int x,d,z,i;
	while( p != NULL && q != NULL) {
		if(p->index == q->index) {
			x=p->index;
			z=0;
			for(i=x;i<x+32;i++) {
				d=(p->info ^ q->info) & p->info;
				if( ((d>>z) & 1)==1)
					F3=insert(F3,i);
				z++;
			}
			q=q->link;
			p=p->link;
		}
		else if(p->index < q->index) {
			x=p->index;
			z=0;
			for(i=x;i<x+32;i++) {
				d=p->info;
				if(((d>>z)&1)==1)
					F3=insert(F3,i);
				z++;
			}
			p=p->link;
		}
		else
			q=q->link;
	}
	if(p!=NULL)
	{
	    x=p->index;
			z=0;
			for(i=x;i<x+32;i++) {
				d=p->info;
				if(((d>>z)&1)==1)
					F3=insert(F3,i);
				z++;
			}
	}
	return F3;
	}
NODE uni(NODE F1,NODE F2,NODE F3){
 int i,x=0,y=0;
 NODE T;
 T=F1;
 while(T!=NULL)
 {
     y=0;
     x=T->index;
     for(i=x;i<(x+32);i++)
     {
        if((((T->info)>>y)&1)==1){
           F3=insert(F3,i);
        }
          y++;
      }
     T=T->link;
 }
 T=NULL;
 T=F2;
 while(T!=NULL)
 {
     y=0;
     x=T->index;
     for(i=x;i<(x+32);i++)
     {
        if((((T->info)>>y)&1)==1){
           F3=insert(F3,i);
        }
          y++;
      }
     T=T->link;
 }
 return F3;
}
int main(){
 int ch,i,n,item;
 NODE first1=NULL;
 NODE first2=NULL;
 NODE first3=NULL;
 for(;;){
  printf("Enter the choice:\n1-Insert to set-1\n2-Insert to set 2\n3-display set 1\n4-Display set 2\n5-Union\n6-Intersection\n7-set1-set2 operation\n8-set2-set1 operation\n9-exit\n");
  scanf("%d",&ch);
  switch(ch){
   case 1:printf("Enter the no. of elements required in set 1\n");
   scanf("%d",&n);
          for(i=0;i<n;i++)
          {
              //printf("Enter the item\n");
              //scanf("%d",&item1);
              item=rand()%100;
              first1=insert(first1,item);
          }
              break;
              case 2:printf("Enter the no. of elements required in set 2\n");
   scanf("%d",&n);
          for(i=0;i<n;i++)
          {
              //printf("Enter the item\n");
              //scanf("%d",&item2);
              item=rand()%100;
              first2=insert(first2,item);
          }
              break;
   case 3:printset(first1);
   break;
   case 4:printset(first2);
   break;
   case 5: first3=uni(first1,first2,first3);
					printset(first3);
					first3=NULL;
					break;
   case 6: first3=intersect(first1,first2,first3);
					printset(first3);
					first3=NULL;
					break;
   case 7: first3=opera(first1,first2,first3);
					printset(first3);
					first3=NULL;
					break;
   case 8: first3=opera(first2,first1,first3);
					printset(first3);
					first3=NULL;
					break;
   default:printf("Invalid choice!Exiting!\n");
   exit(0);
  }
 }
 getch();
}
