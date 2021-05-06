﻿#pragma once
#include<assert.h>

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

//从第一个元素开始，给定数列是有序的，将后面的元素插入到这个数列中，将数列从后向前遍历，将待排元素插入到指定位置
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

#if 0
void shell_sort(int arr[], int len) {
    int gap, i, j;
    int temp;
    for (gap = len >> 1; gap > 0; gap >>= 1)
        for (i = gap; i < len; i++) {
            temp = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = temp;
        }
}
#endif

//template<typename T>
//void shell_sort(T *arr, int len)
//{
//    for (int stepLen = len / 2; stepLen >= 1; stepLen /= 2) {
//        for (int i = stepLen; i < len; ++i) {
//            T key = arr[i];
//            T j;
//            for (j = i; j >= stepLen && arr[j - stepLen] > key; j -= stepLen) {
//                arr[j] = arr[j - stepLen];
//            }
//            arr[j] = key;
//        }
//    }
//}

template<typename T>
void shell_sort(T array[], int length) {
    int h = 1;
    while (h < length / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < length; i++) {
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
                std::swap(array[j], array[j - h]);
            }
        }
        h = h / 3;
    }
}

//思路：递归和分治
template<typename T>
void quick_sort(T *a, int left, int right)
{
    if (left < right) {     //递归终止条件：left>=right
        int i = left, j = right;
        T mid = a[left];
        while (i < j) {
            while (i < j && a[j] > mid) {   //从右往左找到第一个小于mid的数的下标
                --j;
            }
            if (i < j) {
                a[i++] = a[j];
            }
            while (i < j && a[i] < mid) {   //从左往右找到第一个大于mid的数的下标
                ++i;
            }
            if (i < j) {
                a[j--] = a[i];
            }
        }
        a[i] = mid;     //将中值放在找到的位置
        quick_sort(a, left, i - 1);
        quick_sort(a, i + 1, right);
    }
}

template<typename T>
static void merge_array(T *a, int start, int mid, int end, T *tmp)
{
    int i = start, j = mid + 1, k = 0;
    while (i <= mid && j <= end) {
        if (a[i] < a[j]) {
            tmp[k++] = a[i++];
        }
        else {
            tmp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= end) {
        tmp[k++] = a[j++];
    }
    //for (int i = 0; i < end - start + 1; ++i) {
    //    a[start + i] = tmp[i];
    //}
    for (int ii = 0; ii < k; ++ii) {
        a[start + ii] = tmp[ii];
    }
}

//time:O(N*logN), space:O(N)
template<typename T>
void merge_sort(T *a, int start, int end, T *tmp)
{
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort(a, start, mid, tmp); 
        merge_sort(a, mid + 1, end, tmp);
        merge_array(a, start, mid, end, tmp);
    }
}