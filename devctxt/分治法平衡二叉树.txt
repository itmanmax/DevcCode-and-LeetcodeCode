#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#define N 21

struct TreeNode{
char val;
struct TreeNode *lchild,*rchild;
};
void build_tree(struct TreeNode** root,char pre[],char in[],int n){
if(n==0){
*root=NULL; return;
}
*root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
(*root)->val=pre[0];
int i,left=0;
for(i=0;i<n;i++){
if(in[i]==(*root)->val) break;
left++;
}
build_tree(&(*root)->lchild,pre+1,in,left);
build_tree(&(*root)->rchild,pre+left+1,in+left+1,n-left-1);
}

//write your other code here if you need

int isBalanced(struct TreeNode *root) {
    // write your code here

}

int main(){
struct TreeNode *root=NULL;
char pre[N],in[N];
scanf("%s%s",pre,in);
build_tree(&root,pre,in,strlen(pre));
if(isBalanced(root)) printf("True");
else printf("False");
return 0;
} 
