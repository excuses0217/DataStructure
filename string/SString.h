#ifndef DATASTRUCTURE_SSTRING_H
#define DATASTRUCTURE_SSTRING_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR (-1)

typedef int Status;
#define MAXLEN 255

typedef struct {
    char ch[MAXLEN+1];
    int length;
} SString;

Status StringInit(SString &S){
    S.length = 0;
    return OK;
}

Status StringAssign(SString &S, char *chars) {
    int i;
    for (i = 0; chars[i] != '\0' && i <= MAXLEN; i++)
        S.ch[i+1] = chars[i];
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

void GetNext(SString T, int next[]) {
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
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

void PrintString(SString S){
    for (int i = 1; i <= S.length; i++) {
        printf("%c",S.ch[i]);
    }
}

void text(){
    char *chars = "avaskdhaksf";
    SString S;
    StringInit(S);
    StringAssign(S, chars);
    PrintString(S);
}
#endif //DATASTRUCTURE_SSTRING_H
