#ifndef DPLL_H
#define DPLL_H
#include "Global.h"

void CreateClause(const int ord);
Head* DestroyClause(const Head *tar);
void Destoryliteral(const int clause_ord, const int literal_ord);
void AddLiteral(Head *clause, const int ord, const bool is_neg);
bool DPLL();

#endif //DPLL_H
