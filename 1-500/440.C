int countSteps(int n, long long curr, long long next) {
    int steps = 0;
    while (curr <= n) {
        steps += (int)(next <= n ? next - curr : n - curr + 1);
        curr *= 10;
        next *= 10;
    }
    return steps;
}
int findKthNumber(int n, int k) {
    long long curr = 1;  // Start from 1 (smallest lexicographical number)
    k--;  // Decrease k by 1 because we consider the current number as the 1st smallest

    while (k > 0) {
        int steps = countSteps(n, curr, curr + 1);  // Calculate the number of steps between curr and curr + 1

        if (steps <= k) {
            // If the steps are less than or equal to k, move to the next sibling in the lexicographical tree
            curr++;
            k -= steps;  // Reduce k by the number of steps
        } else {
            // If steps > k, move to the first child (go deeper into the tree)
            curr *= 10;
            k--;  // Moving to a child means counting one number, so decrease k
        }
    }

    return (int)curr;
}
