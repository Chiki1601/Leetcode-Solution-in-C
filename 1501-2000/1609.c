int depth(struct TreeNode* root){
    if(root == NULL)
        return 0;
    else
        return 1 + fmax( depth(root->left), depth(root->right) );
}

bool isEvenOddTree(struct TreeNode* root){
    int dep = depth(root);

    struct TreeNode** queue0 = malloc(50000 * sizeof(struct TreeNode* ));
    struct TreeNode** queue1 = malloc(50000 * sizeof(struct TreeNode* ));
    int idx0 = 0, idx1 = 0;
    queue0[idx0] = root;
    idx0 = 1;
    while(idx0 || idx1){
        if(idx0){
            for(int i = 0; i < idx0 ; i++){
                if(i == 0){ 
                    if(queue0[i]->val%2 == 0)
                        return false;
                }
                else{
                    if(queue0[i]->val %2 == 0 || queue0[i]->val <= queue0[i-1]->val)
                        return false;
                }   
                if(queue0[i]->left){
                    queue1[idx1] = queue0[i]->left;
                    idx1++;
                }
                if(queue0[i]->right){
                    queue1[idx1] = queue0[i]->right;
                    idx1++;
                }
            }
            idx0 = 0;    
        }
        else{
            for(int i = 0; i < idx1; i++){
                if(i == 0){ 
                    if(queue1[i]->val%2 == 1)
                        return false;
                }
                else{
                    if(queue1[i]->val %2 == 1 || queue1[i]->val >= queue1[i-1]->val)
                        return false;
                }
                if(queue1[i]->left){
                    queue0[idx0] = queue1[i]->left;
                    idx0++;
                }
                if(queue1[i]->right){
                    queue0[idx0] = queue1[i]->right;
                    idx0++;
                }
            }
            idx1 = 0;
        }
    }
    return true;
}
