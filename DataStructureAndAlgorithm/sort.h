#pragma once
#include<assert.h>
#include <iostream>

using namespace std;

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

template<typename T>
void shell_sort(T *arr, int len)
{
    for (int stepLen = len / 2; stepLen >= 1; stepLen /= 2) {
        for (int i = stepLen; i < len; ++i) {
            T key = arr[i];
            T j;
            for (j = i; j >= stepLen && arr[j - stepLen] > key; j -= stepLen) {
                arr[j] = arr[j - stepLen];
            }
            arr[j] = key;
        }
    }
}

#if 0
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
#endif

#if 0
//思路：递归和分治
template<typename T>
void quick_sort(T *a, int left, int right)
{
    if (left < right) {     //递归终止条件：left>=right
        int i = left, j = right;
        T mid = a[left];
        while (i < j) {
            while (i < j && a[j] >= mid) {   //从右往左找到第一个小于mid的数的下标
                --j;
            }
            if (i < j) {
                a[i++] = a[j];
            }
            while (i < j && a[i] <= mid) {   //从左往右找到第一个大于mid的数的下标
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
#endif

#if 0
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
#endif

template<typename T>
void quick_sort_impl(T arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int i = left, j = right;
    T midValue = arr[i];

    while (i < j) {
        while (i < j && arr[j] >= midValue) {
            --j;
        }
        if (i < j) {
            arr[i++] = arr[j];
        }
        while (i < j && arr[i] <= midValue) {
            ++i;
        }
        if (i < j) {
            arr[j--] = arr[i];
        }
    }

    arr[i] = midValue;

    quick_sort_impl(arr, left, i - 1);
    quick_sort_impl(arr, i + 1, right);
}

template<typename T>
void quick_sort(T arr[], int len) {
    quick_sort_impl(arr, 0, len - 1);
}


template<typename T>
void merge(T arr[], T tmp[], int left, int mid, int right) {
    int i = left, j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            tmp[k++] = arr[i++];
        }
        else {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= right) {
        tmp[k++] = arr[j++];
    }

    for (int i = 0; i < k; ++i) {
        arr[left++] = tmp[i];
    }
}

template<typename T>
void merge_sort_impl(T arr[], T tmp[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort_impl(arr, tmp, left, mid);
    merge_sort_impl(arr, tmp, mid + 1, right);
    merge(arr, tmp, left, mid, right);
}

template<typename T>
void merge_sort(T arr[], int len, T tmp[]) {
    merge_sort_impl(arr, tmp, 0, len - 1);
}

#if 0
template<typename T>
void heapify(T *arr, int len) {
    int parent;
    for (int i = 1; i < len; ++i) {
        int j = i;
        while (j > 0) {
            if (j % 2) {
                parent = (j - 1) / 2;
            }
            else {
                parent = (j - 2) / 2;
            }
            if (arr[j] > arr[parent]) {
                std::swap(arr[j], arr[parent]);
                j = parent;
            }
            else {
                break;
            }
        }
    }
}

template<typename T>
void heap_sort(T *arr, int len) {
    int end = len;
    while (end > 1) {
        heapify(arr, end);
        std::swap(arr[0], arr[end - 1]);
        --end;
    }
}
#elif 1
template<typename T>
void heapify(T arr[], int start, int end) {
    int dad = start;
    int son = 2 * dad + 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1]) {
            ++son;
        }
        if (arr[dad] > arr[son]) {
            return;
        }
        else {
            std::swap(arr[dad], arr[son]);
            dad = son;
            son = 2 * dad + 1;
        }
    }
}

template<typename T>
void heap_sort(T arr[], int len) {
    int end = len - 1;

    /*
     * 先将数组所有元素构造最大堆（大根堆，大顶堆）
     * 构造完成后，堆顶元素（数组第0个元素）的值最大。
     */
    for (int i = len / 2 - 1; i >= 0; --i) {
        heapify(arr, i, end);
    }

    for (int i = end; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, 0, i - 1);
    }
}
#else
void max_heapify(int arr[], int start, int end) {
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;
        if (arr[dad] > arr[son]) // 如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比較
            std::swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(int arr[], int len) {
    // 初始化，i從最後一個父節點開始調整
    for (int i = len / 2 - 1; i >= 0; i--)
    {
        max_heapify(arr, i, len - 1);
    }

    // 先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
    for (int i = len - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        for (int i = 0; i < len; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        max_heapify(arr, 0, i - 1);
    }
}
#endif

void counting_sort(int arr[], int sorted_arr[], int len, int max) {
    int *count_arr = new int[max + 1];
    for (int i = 0; i <= max; ++i) {
        count_arr[i] = 0;
    }
    for (int i = 0; i < len; ++i) {
        ++count_arr[arr[i]];
    }
    for (int i = 1; i <= max; ++i) {
        count_arr[i] += count_arr[i - 1];
    }
    //for (int i = len - 1; i >= 0; --i) {
    for (int i = 0; i < len; ++i) {
        int j = arr[i];
        sorted_arr[count_arr[j] - 1] = j;
        --count_arr[j];
    }
    delete[] count_arr;
}

void counting_sort_demo(int arr[], int len) {
    int *sorted_arr = new int[len];
    int max = 99;
    counting_sort(arr, sorted_arr, len, max);
    for (int i = 0; i < len; ++i) {
        std::cout << sorted_arr[i] << " ";
    }
    std::cout << std::endl;
    delete[] sorted_arr;
}


#if 0
#include<iterator>
#include<iostream>
#include<vector>
using namespace std;

const int BUCKET_NUM = 10;

struct ListNode {
    explicit ListNode(int i = 0) :mData(i), mNext(NULL) {}
    ListNode* mNext;
    int mData;
};

ListNode* insert(ListNode* head, int val) {
    ListNode dummyNode;
    ListNode *newNode = new ListNode(val);
    ListNode *pre, *curr;
    dummyNode.mNext = head;
    pre = &dummyNode;
    curr = head;
    while (NULL != curr && curr->mData <= val) {
        pre = curr;
        curr = curr->mNext;
    }
    newNode->mNext = curr;
    pre->mNext = newNode;
    return dummyNode.mNext;
}


ListNode* Merge(ListNode *head1, ListNode *head2) {
    ListNode dummyNode;
    ListNode *dummy = &dummyNode;
    while (NULL != head1 && NULL != head2) {
        if (head1->mData <= head2->mData) {
            dummy->mNext = head1;
            head1 = head1->mNext;
        }
        else {
            dummy->mNext = head2;
            head2 = head2->mNext;
        }
        dummy = dummy->mNext;
    }
    if (NULL != head1) dummy->mNext = head1;
    if (NULL != head2) dummy->mNext = head2;

    return dummyNode.mNext;
}

void BucketSort(int n, int arr[]) {
    vector<ListNode*> buckets(BUCKET_NUM, (ListNode*)(0));
    for (int i = 0; i < n; ++i) {
        int index = arr[i] / BUCKET_NUM;
        ListNode *head = buckets.at(index);
        buckets.at(index) = insert(head, arr[i]);
    }
    ListNode *head = buckets.at(0);
    for (int i = 1; i < BUCKET_NUM; ++i) {
        head = Merge(head, buckets.at(i));
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = head->mData;
        head = head->mNext;
    }
}
#else
// 假设元素区间是[0,100)
// 不带头结点的链表
template<typename T>
struct ListNode {
    T value;
    ListNode *next;
    explicit ListNode(T value = 0) : value(value), next(nullptr) {}
};

template<typename T>
ListNode<T>* insert(ListNode<T>* head, T value) {
    ListNode<T> dumpNode;
    ListNode<T>* dummy = &dumpNode;
    dummy->next = head;
    ListNode<T>* pre = dummy;
    ListNode<T>* cur = head;
    while (nullptr != cur && cur->value <= value) {
        pre = cur;
        cur = cur->next;
    }
    ListNode<T>* new_node = new ListNode<T>(value);
    new_node->next = cur;
    pre->next = new_node;

    return dummy->next;
}

// 两个链表有序，并且right中元素大于left中元素
template<typename T>
ListNode<T>* merge(ListNode<T>* left, ListNode<T>* right) {
    if (nullptr == left) {
        return right;
    }
    else if (nullptr == right) {
        return left;
    }
    ListNode<T>* head = left;
    while (nullptr != left->next) {
        left = left->next;
    }
    left->next = right;
    return head;
}

// 当前桶的元素范围和数组长度一样
template<typename T>
void bucket_sort(T arr[], int len) {
    vector<ListNode<T>*> buckets(len, nullptr);
    ListNode<T>* head;
    for (int i = 0; i < len; ++i) {
        int index = arr[i] / len;
        head = buckets.at(index);
        buckets.at(index) = insert(head, arr[i]);
    }
    head = buckets.at(0);
    for (int i = 1; i < len; ++i) {
        head = merge(head, buckets.at(i));
    }
    for (int i = 0; i < len; ++i) {
        arr[i] = head->value;
        head = head->next;
    }
}
#endif

#if 1
template<typename T>
int get_max_digit(T arr[], int len) {
    if (len < 1) {
        return 1;
    }

    //int max_digit = 1;
    //for (int i = 0; i < len; ++i) {
    //    int digit = 1;
    //    int j = 10;
    //    while (arr[i] / j) {
    //        ++digit;
    //        j *= 10;
    //    }
    //    if (digit > max_digit) {
    //        max_digit = digit;
    //    }
    //}
    //return max_digit;

    T maxValue = arr[0];
    for (int i = 1; i < len; ++i) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    int digit = 1;
    int j = 10;
    while (maxValue / j) {
        ++digit;
        j *= 10;
    }
    return digit;
}

//template<typename T>
// 基数排序的桶相当于一个栈，元素后进先出，所以填充辅助数组的时候从后往前填充（len-1 -> 0）
void radix_sort(int arr[], int len) {
    int max_digit = get_max_digit(arr, len);
    int count_arr[10];
    int* tmp_arr = new int[len];
    int radix = 1;
    for (int d = 0; d < max_digit; ++d) {
        for (int i = 0; i < 10; ++i) {
            count_arr[i] = 0;
        }
        for (int i = 0; i < len; ++i) {
            int k = arr[i] / radix % 10;
            ++count_arr[k];
        }
        for (int i = 1; i < 10; ++i) {
            count_arr[i] += count_arr[i - 1];
        }
#if 0
        // 正向填充辅助数组的话就破坏了稳定性
        //for (int i = 0; i < len; ++i) {
#else
        for (int i = len - 1; i >= 0; --i) {
#endif
            int j = arr[i] / radix % 10;
            tmp_arr[count_arr[j] - 1] = arr[i];
            --count_arr[j];
        }
        for (int i = 0; i < len; ++i) {
            arr[i] = tmp_arr[i];
        }
        radix *= 10;

        //for (int i = 0; i < len; ++i) {
        //    cout << arr[i] << " ";
        //}
        //cout << endl;
    }
    delete[] tmp_arr;
}
#else
int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int maxData = data[0];              ///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;
    /*    int d = 1; //保存最大的位数
        int p = 10;
        for(int i = 0; i < n; ++i)
        {
            while(data[i] >= p)
            {
                p *= 10;
                ++d;
            }
        }
        return d;*/
}
void radix_sort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) //进行d次排序
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for (j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[]tmp;
    delete[]count;
}
#endif