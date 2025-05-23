/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int depth(struct TreeNode* root){
    if(root == NULL)
        return 0;

    return 1 + fmax(depth(root->left) , depth(root->right) );
}

struct TreeNode* lcaDeepestLeaves(struct TreeNode* root){
    int l_depth = depth(root->left)  ;
    int r_depth = depth(root->right) ;
    if(l_depth == r_depth)
        return root;
    if(l_depth > r_depth)
        return lcaDeepestLeaves(root->left) ;
    else
        return lcaDeepestLeaves(root->right) ;
}
