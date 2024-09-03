#include "cnfparser.h"
using namespace std;

extern Head *root, *tail;
extern int varNum, clauseNum;
extern bool *value_list;

void CNFParser(const string &filename) {
    const string path = "../src/cnffile/" + filename;
    cout << path << endl;
    ifstream file(path, ios::in);   // 打开文件
    if (!file.is_open()) {
        cout << "File not found!" << endl;
        exit(1);
    }
    char buf[100];
    char ch = '\0';
    while(ch != 'p') {  // 跳过注释
        file.getline(buf, 100);
        file.get(ch);
    }
    int ord = 1;  // 变元数，子句数，子句序号
    file >> buf >> varNum >> clauseNum;   // 读取变元数和子句数
    value_list = new bool[varNum + 1];   // 初始化变元值列表
    memset(value_list, 0, sizeof(bool) * (varNum + 1));
    root = new Head;
    root->ord = 0;
    root->next = nullptr;
    root->first = nullptr;
    tail = root;
    while(ord <= clauseNum) {
        // 读取子句
        CreateClause(ord++);
        int literal;
        file >> literal;
        while(literal) {
            if(literal < 0) AddLiteral(tail, -literal, true);
            else AddLiteral(tail, literal, false);
            file >> literal;
        }
    }
    file.close();
}