MergeSort (int * A, int l, int r)
{
    if (l < r)
    {
        int q = (l+r)/2;
        MergeSort (A, l, q);
        MergeSort (A, q+1, r);
        Merge (A, l, q, r);
    }
}

Merge (int * A, int l, int q, int r)
{
    int * B = (int) malloc (lenght (A) * sizeof (int));
    int i = l;
    int j = q+1;
    int k = l;

    while (i <= q && j <= r)
    {
        if (A[i] < A[j])
        {
            B[k] = A[i];
            i++;
        }
        else 
        {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    
    int x;
    if (i <= q)
    {
        x = i;
    }
    else 
    {
        x = j;
    }
    while (k <= r)
    {
        B[k] = A[x];
        x++;
        k++;
    }
}