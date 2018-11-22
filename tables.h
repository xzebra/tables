#ifndef TABLES_H
#define TABLES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Table {
  public:
    Table(std::string columnName);
    Table(std::vector<std::string> columnNames);

    void addRow(std::vector<std::string> s);
    std::vector<std::string> getRow(int index);

    void addColumn(std::vector<std::string> s);

    std::vector<std::string> getColumn(int index);

    void setCell(int col, int row, std::string s);

    void print(std::ostream& output = std::cout, const char* init = "", 
                const char* newLine = "\n", const char* endString = "\n");
    void writeToFile();
    void writeAsHTML();
  private:
    int columns, rows;
    std::vector<int> width;
    std::vector<std::vector<std::string> > t;
    std::ofstream outputFile;
};

#endif // TABLES_H