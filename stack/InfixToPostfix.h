#ifndef DATASTRUCTURE_INFIXTOPOSTFIX_H
#define DATASTRUCTURE_INFIXTOPOSTFIX_H

/*
 * 在实现中缀转后缀（逆波兰）表达式的算法中，我们可以使用一个栈来临时存储运算符。下面是这个算法的基本步骤：
 * 1.从左到右遍历中缀表达式。
 * 2.如果当前字符是操作数（数字），那么直接输出。
 * 3.如果当前字符是左括号"("，则将其压入栈中。
 * 4.如果当前字符是一个运算符（如+，-，*，/），则：
 *  4.1如果栈为空或栈顶元素为左括号"("，则将此运算符入栈。
 *  4.2否则，如果优先级比栈顶运算符的优先级高，也将运算符压入栈中。
 *  4.3否则，将栈顶的运算符弹出并输出，然后再次与新的栈顶运算符比较优先级，重复此步骤。
 * 5.如果当前字符是右括号")"，则将栈顶的运算符弹出并输出，直到遇到左括号为止，此时将这一对括号丢弃。
 * 6.重复步骤2-5，直到表达式的最右端。
 * 7.最后将栈中的元素依次弹出并输出。*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define SIZE 100

char stack[SIZE];
int top = -1;

void push(char item) {
    if(top >= SIZE-1) {
        printf("\nStack Overflow.");
    } else {
        stack[++top] = item;
    }
}

char pop() {
    if(top < 0) {
        printf("\nStack Underflow.");
        exit(1);
    } else {
        return stack[top--];
    }
}

// Function to determine the priority of operators
int priority(char symbol) {
    switch(symbol) {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
        case '(':
        case ')':
        case '#':
            return 1;
    }
    return 0;
}

void InfixToPostfix(char infix_exp[], char postfix_exp[]) {
    int i, j;
    char item;
    char x;

    push('(');  // push '(' onto stack
    strcat(infix_exp, ")");  // add ')' to infix expression

    i = 0;
    j = 0;
    item = infix_exp[i];  // initialize before loop

    while(item != '\0') {  // run loop till end of infix expression
        if(item == '(') {
            push(item);
        } else if(isalnum(item)) {
            postfix_exp[j++] = item;
        } else if(item == ')') {
            while((x = pop()) != '(') {
                postfix_exp[j++] = x;
            }
        } else {  // an operator is encountered
            while(priority(stack[top]) >= priority(item)) {
                postfix_exp[j++] = pop();
            }
            push(item);
        }
        i++;
        item = infix_exp[i];
    }

    postfix_exp[j] = '\0';  // null terminate string
}

int InfixToPostfixMain() {
    char infix[SIZE], postfix[SIZE];
    printf("\nEnter Infix expression : ");
    gets(infix);

    InfixToPostfix(infix,postfix);  // call to convert
    printf("Postfix Expression: ");  // print postfix expression
    puts(postfix);

    return 0;
}

#endif //DATASTRUCTURE_INFIXTOPOSTFIX_H
