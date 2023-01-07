int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize){
    int sm = 0, oldsm = 0, ind = 0;
    for (int i = gasSize - 1; i != -1; i--) {
        sm += (gas[i] - cost[i]);
        if (sm > oldsm)
        {
            oldsm = sm;
            ind = i;
        }
    }
    return sm > -1 ? ind : -1;
}
