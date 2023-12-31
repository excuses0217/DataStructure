#ifndef DATASTRUCTURE_SSTRING_H
#define DATASTRUCTURE_SSTRING_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR (-1)

typedef int Status;
#define MAXLEN 255

typedef struct {
    char ch[MAXLEN + 1];
    int length;
} SString;

Status StringInit(SString &S) {
    S.length = 0;
    return OK;
}

Status StringAssign(SString &S, char *chars) {
    int i;
    for (i = 0; chars[i] != '\0' && i <= MAXLEN; i++)
        S.ch[i + 1] = chars[i];
    // If chars is longer than MAXLEN, only the first MAXLEN characters will be copied
    if (i == MAXLEN && chars[i] != '\0')
        return ERROR;
    S.length = i;
    return OK;
}

Status StrCopy(SString &T, SString S) {
    int i;
    for (i = 1; i <= S.length && i <= MAXLEN; i++)
        T.ch[i] = S.ch[i];
    // If S.length is greater than MAXLEN, only the first MAXLEN characters will be copied
    if (i == MAXLEN && i < S.length)
        return ERROR;
    T.length = i;
    return OK;
}

bool StrEmpty(SString S) {
    return S.length == 0;
}

int StrLength(SString S) {
    return S.length;
}

// 比较操作。若S>T，则返回值>0;若S=T，则返回值=0;若S<T，则返回值<0
int StrCompare(SString S, SString T) {
    for (int i = 0; i <= S.length && i <= T.length; i++) {
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    }
    // 扫描过的所有字符都相同，则长度长的串更大
    return S.length - T.length;
}

bool SubString(SString &Sub, SString S, int pos, int len) {
    // 字串范围越界
    if (pos + len - 1 > S.length)
        return false;
    for (int i = pos; i < pos + len; i++)
        Sub.ch[i - pos + 1] = S.ch[i];
    Sub.length = len;
    return true;
}

int Index(SString S, SString T) {
    int i = 1, n = StrLength(S), m = StrLength(T);
    SString sub;    // 用于暂存字串
    while (i <= n - m + 1) {
        SubString(sub, S, i, m);
        if (StrCompare(sub, T) != 0)++i;
        else return i;  // 返回字串再主串中的位置
    }
    return 0;   // S中不存在与T相等的子串
}

Status Concat(SString &T, SString S1, SString S2) {
    if (S1.length + S2.length > MAXLEN)
        return ERROR; // If the total length of S1 and S2 exceeds MAXLEN, return ERROR
    // Copy S1 to T
    for (int i = 1; i <= S1.length; i++)
        T.ch[i] = S1.ch[i];
    // Append S2 to T
    for (int i = 1; i <= S2.length; i++)
        T.ch[S1.length + i] = S2.ch[i];

    T.length = S1.length + S2.length;

    return OK;
}

/*
 * 朴素模式匹配算法
 * 其基本思想是从主串 S 的第一个字符开始，依次和模式串 T 的字符进行比较，
 * 如果当前字符匹配成功，就比较下一个字符，
 * 如果匹配失败，则将 S 向右滑动一位，再重新和 T 进行匹配。*/
int Index_BruteForce(SString S, SString T) {
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length) {
        if (S.ch[i] == T.ch[j]) { // 若当前字符匹配成功，则比较下一个字符
            ++i;
            ++j;
        } else { // 若匹配失败，则i回退，j归1，从S的下一位置开始匹配
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T.length) // 匹配成功，返回模式串T在主串S中的开始位置
        return i - T.length;
    else // 匹配失败，返回0
        return 0;
}

/*
 * 下面解释KMP算法修next数组的逻辑：
1.初始化变量：设置两个指针i和j，其中i指向模式串的当前位置，j表示当前字符前缀的最长相等前缀后缀的长度，即已匹配的字符数目。
2.首先，将next[1]设置为0，因为next[1]始终为0。
3.进入循环，遍历整个模式串T：
    3.1如果j为0，或者当前位置i的字符与前缀的第j个字符相等（即T.ch[i] == T.ch[j]），则将i和j都向后移动一位，并将next[i]设置为j的值。
    3.2如果当前位置i的字符与前缀的第j个字符不相等，则需要回溯。此时将j更新为next[j]，即回溯到当前字符前缀的最长相等前缀后缀的长度，继续进行比较。
    3.3这个操作相当于将模式串向右移动一位，但是不需要从头开始，而是从已匹配的前缀的末尾开始。
    3.4通过不断回溯，直到找到一个相等的前缀或者j变为0，表示无法回溯到更短的相等前缀。
4.重复步骤3，直到遍历完整个模式串T。*/
void GetNext(SString T, int next[]) {
    int i = 1, j = 0;
    next[1] = 0; // next[1]无脑写0
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    next[i + 1] = -1; // 给最后一位一个标识符表示结束
}

void GetNextVal(SString T, int nextval[]) {
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            if (T.ch[i] != T.ch[j])
                nextval[i] = j;
            else // 当两个字符相等时，将nextval值设为next的nextval值
                nextval[i] = nextval[j];
        } else {
            j = nextval[j];
        }
    }
    nextval[i + 1] = -1; // 给最后一位一个标识符表示结束
}

int Index_KMP(SString S, SString T, int next[]) {
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length) {
        if (j == 0 || S.ch[i] == T.ch[j]) { // 如果当前字符匹配成功，或者j=0，比较下一个字符
            ++i;
            ++j;
        } else {
            j = next[j]; // 如果当前字符匹配失败，则将j设置为next[j]，i不变
        }
    }
    if (j > T.length) // 匹配成功，返回模式串T在主串S中的开始位置
        return i - T.length;
    else // 匹配失败，返回0
        return 0;
}

void PrintString(SString S) {
    for (int i = 1; i <= S.length; i++) {
        printf("%c", S.ch[i]);
    }
}

void text() {
    int next[255];
    SString T;
    StringInit(T);
    char* chars = "abaabc";
    StringAssign(T,chars);
    PrintString(T);
    printf("\n");
    GetNext(T, next);
    for (int i = 1; next[i] !=-1 ; i++) {
        printf("%d",next[i]);
    }

    SString S;
    StringInit(S);
    char* chars1 = "abaabaabcabaabc";
    StringAssign(S,chars1);
    printf("\n%d",Index_KMP(S,T,next));
}

#endif //DATASTRUCTURE_SSTRING_H
