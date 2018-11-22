#include "tables.h"

int main(int argc, char *argv[]) {
    Table table({"Title", "Column Name", "Column Name"});
    std::string arr[3][3] = {
        {"Something", "5", "Something but longer and cooler"},
        {"Something", "2", "Something normal"},
        {"Something", "9", "Asdasdasdasdasdasdasdasd"}};
    for (int i = 0; i < 3; i++) {
        table.addRow(std::vector<std::string>(arr[i], arr[i] + 3));
    }

    table.print();
    table.writeToFile();
    table.writeAsHTML();
    
    return 0;
}
