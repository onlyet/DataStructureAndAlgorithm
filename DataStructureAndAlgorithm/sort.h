#pragma once

//排序算法都按升序处理

template<typename T>
void Swap(T &lhs, T&rhs)
{
    T tmp = rhs;
    rhs = lhs;
    lhs = tmp;
}

template<typename T>
void bubble_sort(T *arr, int n)
{
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                Swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template<typename T>
void bubble_sort_2(T *arr, int n)
{
    for (int i = 0; i < n - 1; ++i) {
        bool done = true;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                Swap(arr[j], arr[j + 1]);
                done = false;
            }
        }
        if (done) {
            break;
        }
    }
}

//template<typename T>
//void bubble_sort_3(T *arr, int n)
//{
//    T sorted_index = n - 1 - i, sorted_index_tmp = sorted_index;
//    for (int i = 0; i < n - 1; ++i) {
//        bool done = true;
//        for (int j = 0; j < sorted_index; ++j) {
//            if (arr[j] > arr[j + 1]) {
//                Swap(arr[j], arr[j + 1]);
//                sorted_index_tmp = j;
//                done = false;
//            }
//        }
//        if (done) {
//            break;
//        }
//
//        if (sorted_index > sorted_index_tmp) {
//            sorted_index = sorted_index_tmp;
//        }
//    }
//}

template<typename T>
void bubble_sort_3(T *arr, int n)
{
    T flag = n - 1, i;
    while (flag) {
        i = flag;
        flag = 0;
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j + 1]) {
                Swap(arr[j], arr[j + 1]);
                flag = j;
            }
        }
    }
}

//不稳定
template<typename T>
void selection_sort(T *a, int n)
{
    int min = 0;
    for (int i = 0; i < n - 1; ++i) {
        min = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[min] > a[j]) {
                min = j;
            }
        }
        if (min != i) {
            Swap(a[min], a[i]);
        }
    }
}

template<typename T>
void insertion_sort(T *a, int n)
{
    int i, j;
    T tmp;
    for (i = 1; i < n; ++i) {
        tmp = a[i];
        for (j = i; j > 0 && a[j - 1] > tmp; --j) {
            a[j] = a[j - 1];
        }
        a[j] = tmp;
    }
}