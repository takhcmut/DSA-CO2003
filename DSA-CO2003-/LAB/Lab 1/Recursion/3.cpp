int findMax(int* arr, int length) {
    if (length == 1){
        return arr[0];
    }

    int findMaxofArray = findMax (arr + 1, length - 1);

    if (arr[0] > findMaxofArray){
        return arr[0];
    }
    else {
        return findMaxofArray;
    }

}