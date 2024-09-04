#include "Global.h"
#include "cnfparser.h"
#include "dpll.h"
using namespace std;

Head *root = nullptr;
int varNum = 0, clauseNum = 0, nums = 0;
bool *value_list = nullptr;

int main() {
    string filename;
    cout << "Please input the filename of the CNF file: ";
    cin >> filename;
    CNFParser(filename);
    if(DPLL()) {
        // 打印解
        cout << "Satified!" << endl;
        // printRes();
        // saveRes(filename, true, 1000);
    }
    else {
        cout << "Unsatisfied!" << endl;
        // saveRes(filename, false, 1000);
    }
    DestroyList();
    system("pause");
    return 0;
}
