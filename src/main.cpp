#include "Global.h"
#include "cnfparser.h"
#include "dpll.h"
using namespace std;

Head *root = nullptr, *tail = nullptr;
int varNum = 0, clauseNum = 0;
bool *value_list = nullptr;

int main() {
    string filename;
    cout << "Please input the filename of the CNF file: ";
    cin >> filename;
    CNFParser(filename);
    if(DPLL()) {
        // 打印解
        cout << "Satified!" << endl;
        for(int i = 1; i <= varNum; ++i) {
            cout << "x" << i << " = " << value_list[i] << endl;
        }
    }
    else cout << "Unsatisfied!" << endl;
    return 0;
}
