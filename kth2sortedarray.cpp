/*
try to find k  element from A and B (we seach in A from start and in B from end)
among these k we have x element from A and k-x element from B
We search for last index x in A

in zero based index
x-1 th element from A is the last element from A
and k-x-1 th element is the last element from A
0) we initialize intial range of x ( last index in A)
lower -> if B.size <= k, from A we definitely get k-B.size element
upper->if A.size <= k, from A we definitely get A.size element
1) if B[k-x-1] is the kth elment then all the element in A including and before x-1 
are less than B[k-x-1] and A[x] is greater than B[k-x-1] if this is not the case
we need to take more element from A ( we can't go back in B as we are scanning B from the back in reverse direction)
 
2) else if A[x-1] is the kth element then all the element including and before B[k-x-1] are less than A[x-1]
and B[k-x] is greater than A[x-1]
if this is not the case we need less element form B ( as we are scanning b in reverse)

3) if this is not the case then max( A[x-1] or B[k-x-1]) is the kth element.

*/
double findkth(const vector<int> &A, const vector<int> &B, int k) {
    int a = A.size();
    int b = B.size();
        int xl = max(0, k-b);
        int xh = min(k, a);
        while(xl <= xh){
            int x = xl + (xh-xl)/2;
            if(x  < a && k-x-1 >= 0 && A[x] < B[k-x-1]){
                //more element from a increase x
                xl = x + 1;
            }else if(k-x < b && x-1 >= 0 && B[k-x] < A[x-1]){
                //more element from b decrease x
                xh = x-1;
            }else{
                if(x-1 >= 0  && k-x-1 >= 0 ){
                    return max(A[x-1], B[k-x-1]);
                }else if(x-1 >= 0){
                    return A[x-1];
                }else if(k-x-1 >= 0){
                    return B[k-x-1];
                }
            }
        }
        return 0;
}

double Solution::findMedianSortedArrays(const vector<int> &A, const vector<int> &B) {
    int k = A.size() + B.size();
    if(A.empty()){
        double ret = B[B.size()/2];
        if(k%2 == 0){
            ret += B[B.size()/2-1];
            ret /= 2.0;
        }
        return ret;
    }
    if(B.empty()){
        double ret = A[A.size()/2];
        if(k%2 == 0){
            ret += A[A.size()/2-1];
            ret /= 2.0;
        }
        return ret;
    }
    double ret = findkth(A,B, k/2+1);
    if(k%2 == 0){
        ret +=  findkth(A,B, k/2);
        ret /= 2.0;
    }
    return ret;
}
