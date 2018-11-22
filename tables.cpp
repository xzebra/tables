#include "tables.h"

void errorMsg(std::string s) {
    std::cout << "tables error: " << s << std::endl;
}

std::string centerText(std::string s, int w) {
    std::string t = "";
    int left = w - s.length();
    for (int i = 0; i < left / 2; i++)
        t += " ";
    t += s;
    
    for (int i = 0; i < (left % 2 == 0 ? left / 2 : left / 2 + 1); i++)
        t += " ";
    return t;
}

Table::Table(std::string title) {
    columns = 1;
    rows = 1;
    t = std::vector<std::vector<std::string> >(
        1, std::vector<std::string>(1, title)
    );
    width = std::vector<int>(1, title.length() + 2);
}

void Table::addRow(std::vector<std::string> s) {
    if (s.size() != columns)
        errorMsg("addRow(std::vector<std::string> s) -> s.size() != number of columns");
    else {
        t.push_back(s);
        for (int i = 0; i < columns; i++) {
            if (s[i].length() + 2 > width[i])
                width[i] = s[i].length() + 2;
        }
        rows++;
    }
}

std::vector<std::string> Table::getRow(int index) {
    if (index >= rows || index < 0) {
        errorMsg("std::vector<std::string> getRow(int index) -> invalid index");
        return std::vector<std::string>(0);
    }
    return t[index];
}

void Table::addColumn(std::vector<std::string> s) {
    if (s.size() != rows)
        errorMsg("addColumn(std::vector<std::string> s) -> s.size() != number of rows");
    else {
        int columnWidth = 0;
        for (size_t i = 0; i < t.size(); i++) {
            if (s[i].length() + 2 > columnWidth)
                columnWidth = s[i].length() + 2;
            t[i].push_back(s[i]);
        }
        width.push_back(columnWidth);
        columns++;
    }
}

std::vector<std::string> Table::getColumn(int index) {
    if (index >= columns || index < 0) {
        errorMsg("std::vector<std::string> getColumn(int index) -> invalid index");
        return std::vector<std::string>(0);
    }
    
    std::vector<std::string> temp;
    for (int i = 0; i < rows; i++) {
        temp.push_back(t[i][index]);
    }
    return temp;
}

void Table::setCell(int col, int row, std::string s) {
    if (col >= columns || col < 0)
        errorMsg("void setCell(int col, int row) -> invalid col index");
    else if (row >= rows || row < 0)
        errorMsg("void setCell(int col, int row) -> invalid row index");
    else t[row][col] = s;
}

void Table::print(std::ostream& output, const char* init, 
                const char* newLine, const char* endString) {
    output << init;
    std::string hdiv = "+", temp = "|", temp2 = "|";
    // Generate divisors and header
    for (int i = 0; i < columns; i++) {
        for (int e = 0; e < width[i]; e++)
            hdiv += "-";
        temp += centerText(t[0][i], width[i]) + "|";
        hdiv += "+";
    }
    output << hdiv << newLine << temp << newLine << hdiv << newLine;

    // First row is reserved for the column names
    for (int row = 1; row < rows; row++) {
        temp = temp2 = '|';
        for (int col = 0; col < columns; col++) {
            temp += centerText(t[row][col], width[col]) + '|';
            temp2 += centerText("", width[col]) + '|';
        }
        output << temp << newLine;
        if (row < rows - 1) output << temp2 << newLine;
    }
    if (rows > 1) output << hdiv;
    output << endString;
}

void Table::writeAsHTML() {
    outputFile.open("output.html");
    print(outputFile, "<pre style=\"text-align:center;\">\n", "\n", "\n</pre>");
    outputFile.close();
}

void Table::writeToFile() {
    outputFile.open("output.txt");
    print(outputFile);
    outputFile.close();
}