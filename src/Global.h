#ifndef GLOBAL_H
#define GLOBAL_H
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>

typedef int status;
#define FOUND 1
#define NOTHING 0
#define ERROR -1

typedef struct Node {   // 变元节点
    int ord;    // 变元序号
    bool is_neg;    // 是否为负元
    Node *next;    // 子句中下一变元
}Node;

typedef struct Head {   // 子句头节点
    int ord;    // 子句序号，为0表示根节点
    Node *first; // 第一变元
    Head *next; // 下一子句
}Head;

#endif //GLOBAL_H
