/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#pragma GCC optimize("O3", "unroll-loops")
int arr[100000], n;
void inorder(struct TreeNode* root){
    if (!root) return;
    inorder(root->left);
    arr[n++]=root->val;
    inorder(root->right);
}

struct TreeNode* BST(int l, int r){
    if (l>r) return NULL;
    int m=(l+r)/2;
    struct TreeNode* node=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val=arr[m];
    node->left=BST(l, m-1);
    node->right=BST(m+1, r);
    return node;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    memset(arr, 0, sizeof(arr));
    n=0;
    inorder(root);
    return BST(0, n-1);
}
