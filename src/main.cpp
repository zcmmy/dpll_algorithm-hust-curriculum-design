#include "Global.h"
#include "cnfparser.h"
#include "dpll.h"
using namespace std;

Head *root = nullptr;
int varNum = 0, clauseNum = 0, nums = 0, nums2 = 0;
bool *value_list = nullptr;

int main() {
    string filename;
    cout << "Please input the filename of the CNF file: ";
    cin >> filename;
    CNFParser(filename);
    clock_t start_time = clock();
    status s = DPLL();
    clock_t end_time = clock();
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    if(s) {
        // 打印解
        cout << "Satified!" << endl;
        // printRes();
        saveRes(filename, true, 1000*duration);
    }
    else {
        cout << "Unsatisfied!" << endl;
        saveRes(filename, false, duration);
    }
    DestroyList();
    system("pause");
    return 0;
}
