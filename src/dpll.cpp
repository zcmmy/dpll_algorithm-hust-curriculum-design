#include "dpll.h"
using namespace std;

extern Head *root, *tail;
extern int varNum, clauseNum;
extern bool *value_list;

void DestroyList() {
    // 销毁链表
    auto p = root;
    while(p) {
        auto q = p->first;
        while(q) {
            auto temp = q;
            q = q->next;
            delete temp;
        }
        auto temp = p;
        p = p->next;
        delete temp;
    }
}

void CreateClause(const int ord) {
    auto *new_Clause = new Head;
    new_Clause->ord = ord;
    new_Clause->next = nullptr;
    tail->next = new_Clause;
    tail = new_Clause;
}

Head* DestroyClause(const Head *tar) {
    // 销毁子句，返回下一子句
    auto p = root;
    if(tar == tail) {
        while(p->next != tail) p = p->next;
        tail = p;
    }
    auto q = tar->first;
    while(q) {
        auto temp = q;
        q = q->next;
        delete temp;
    }
    p = root;
    while (p->next != tar && p->next != nullptr) {
        p = p->next;
    }
    p->next = tar->next;
    delete tar;
    return p->next;
}

void Destoryliteral(const int ord) {
    Head *p = nullptr;
    for(p = root; p; p = p->next) {
        for(auto q = p->first; q; q = q->next) {
            if(q->ord == ord) {
                if(q->is_neg == !(value_list[ord])) {
                    // 文字为真，删除子句
                    p = DestroyClause(p);
                }
                else {
                    // 文字为假，删除变元
                    auto r = p->first;
                    if(r == q) {
                        p->first = q->next;
                        delete q;
                    }
                    else {
                        while(r->next != q) r = r->next;
                        r->next = q->next;
                        delete q;
                    }
                }
                break;
            }
        }
    }
}

void AddLiteral(Head *clause, const int ord, const bool is_neg) {
    auto *new_literal = new Node;
    new_literal->ord = ord;
    new_literal->is_neg = is_neg;
    new_literal->next = clause->first;
    clause->first = new_literal;
}

status UnitPropagation() {
    // 单子句传播，返回是否找到单子句
    auto p = root->next;
    while(p) {
        if(p->first->next == nullptr) {
            // 子句只有一个变元
            int tar = p->first->ord;
            if(p->first->is_neg) value_list[tar] = false;
            else value_list[tar] = true;
            DestroyClause(p);
            Destoryliteral(tar);
            return FOUND;
        }
        else p = p->next;
    }
    return NOTHING;
}

status PureLiteralelimination() {
    // 孤立文字消除，返回是否找到孤立文字
    int count[varNum+1] = {0};
    for(auto *p = root->next; p; p = p->next) {
        for(auto *q = p->first; q; q = q->next)
            count[-q->ord]++;
    }
    status s = NOTHING;
    auto p = root->next;
    while(p) {
        bool flag = true;
        for(auto *q = p->first; q; q = q->next) {
            if(count[q->ord] == 1) {
                if(q->is_neg) value_list[q->ord] = false;
                else value_list[q->ord] = true;
                p = DestroyClause(p);
                s = FOUND;
                flag = false;
                break;
            }
        }
        if(flag) p = p->next;
    }
    return s;
}

Head* CopyList() {
    auto *new_root = new Head;
    new_root->ord = 0;
    new_root->first = nullptr;
    new_root->next = nullptr;
    Head *new_cur = new_root;
    // 复制子句
    for(Head *p = root->next; p != nullptr; p = p->next) {
        auto *new_clause = new Head;
        new_clause->ord = p->ord;
        new_clause->first = nullptr;
        new_clause->next = nullptr;
        new_cur->next = new_clause;
        new_cur = new_clause;
        // 复制变元
        for(Node *q = p->first; q != nullptr; q = q->next) {
            auto *new_literal = new Node;
            new_literal->ord = q->ord;
            new_literal->is_neg = q->is_neg;
            new_literal->next = new_clause->first;
            new_clause->first = new_literal;
        }
    }
    return new_root;
}

int ChooseVariable() {
    // 选择变元，启发函数
    return root->next->first->ord;
}

bool DPLL() {
    Head *new_root = CopyList();    // 备份
    bool *new_value_list = new bool[varNum + 1];
    memcpy(new_value_list, value_list, sizeof(bool) * (varNum + 1));
    // 单子句传播
    status s;
    while((s = UnitPropagation()) == FOUND);
    while((s = PureLiteralelimination()) == FOUND);
    if(!root->next) return true; // 问题解决
    else {
        int var = ChooseVariable();
        CreateClause(tail->ord+1);
        AddLiteral(tail, var, false);
        if(DPLL()) return true;
        // 回溯
        DestroyList();
        delete [] value_list;
        root = new_root;
        value_list = new_value_list;
        CreateClause(tail->ord+1);
        AddLiteral(tail, var, true);
        if(DPLL()) return true;
        // 回溯
        DestroyList();
        delete [] value_list;
        root = new_root;
        value_list = new_value_list;
    }
    return false;
}