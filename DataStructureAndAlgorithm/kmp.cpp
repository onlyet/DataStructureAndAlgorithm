#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
void make_next(const char *pattern, int *next) {
    int q, k;
    int m = strlen(pattern);

    next[0] = 0;
    for (q = 1, k = 0; q < m; q++) {
        while (k > 0 && pattern[q] != pattern[k])
            k = next[k - 1];

        if (pattern[q] == pattern[k]) {
            k++;
        }

        next[q] = k;
    }
}

int kmp(const char *text, const char *pattern, int *next) {
    int n = strlen(text);
    int m = strlen(pattern);
    if (m > n) {
        return -1;
    }

    make_next(pattern, next);

    int i, q;
    for (i = 0, q = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = next[q - 1];
        }

        if (pattern[q] == text[i]) {
            q++;
        }

        if (q == m) {
            break;
        }
    }
    return i - q + 1;
}
#endif

#if 0
void get_next(const char *pattern, int *next) {

    int n = strlen(pattern);
    next[0] = 0;
    // i是pattern的下标，j是当前子串的部分匹配值（next值）
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        next[i] = j;
    }
}

#elif 0
void get_next(const char *pattern, int *next) {
    size_t m = strlen(pattern);
    next[0] = 0;
    int max_prefix_len = 0;
    // i表示next索引
    for (size_t i = 1; i < m; ++i) {
        while (max_prefix_len > 0 && pattern[i] != pattern[max_prefix_len]) {
            max_prefix_len = next[max_prefix_len - 1];
        }
        if (pattern[i] == pattern[max_prefix_len]) {
            ++max_prefix_len;
        }
        next[i] = max_prefix_len;
    }
}

int kmp(const char *text, const char *pattern, int *next) {
    int n = strlen(text);
    int m = strlen(pattern);
    if (m > n) {
        return -1;
    }

    get_next(pattern, next);

    // i是text下标，j是pattern下标
    int i = 0, j = 0;
    for (; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            return i - m + 1;
        }
    }
    return -1;
}
#else
void get_next(const char *pattern, int *next) {
    size_t m = strlen(pattern);
    // pattern下标
    size_t i = 0;
    // 最大公共前后缀元素长度
    int j = -1;
    next[0] = -1;

    while (i < m) {
        if (-1 == j || pattern[i] == pattern[j]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

int kmp(const char *str, const char *pattern, int *next) {
    int n = strlen(str);
    int m = strlen(pattern);
    if (n < m) {
        return -1;
    }
    // 主串索引
    int i = 0;
    // 模式串索引，j=-1时表示主串当前字符不匹配并且模式串不能再回溯，然后开始匹配主串下一个字符
    int j = 0;

    get_next(pattern, next);

    while (i < n && j < m) {
        if (-1 == j || str[i] == pattern[j]) {
            ++i;
            ++j;
        }
        else {
            j = next[j];
        }
    }

    if (j == m) {
        return i - j;
    }
    return -1;
}
#endif

int kmp_test() {
    int i;
    int next[20] = { 0 };

    //char *text = "ababxbababababcdababcabddcadfdsss";
    //char *text = "abcaxxx";
    char *text = "ababababca";
    char *pattern = "abababca";

    //get_next(pattern, next);
    //for (i = 0; i < strlen(pattern); i++) {
    //    printf("%4d", next[i]);
    //}
    //printf("\n");

    int idx = kmp(text, pattern, next);
    printf("match pattern : %d\n", idx);

    for (i = 0; i < strlen(pattern); i++) {
        printf("%4d", next[i]);
    }
    printf("\n");

    return 0;
}

