#include <iostream>
#include "CSVParser.h"

void CSVParser::readAndStoreData(const std::string& fileName, Data* data) {

    std::ifstream in;
    in.open("..\\resources\\" + fileName);
    std::string line, token;
    int rowNum = 0;


    while(getline(in, line)) {
        if(rowNum == 0) {
            int cnt = 0;
            std::stringstream s(line);
            while (getline(s, token, ';')) {
                cnt++;
            }
            data->totalColNum = cnt;
        } else {
            std::vector<float> row;
            std::stringstream s(line);
            int colNum = 1;
            while (getline(s, token, ';')) {
                if (colNum != 1) {
                    if (token.empty() || token == "-")
                        row.push_back((float)(1.0f/0.0f));
                    else
                        try {
                            size_t found = token.find(',');
                            if(found != std::string::npos)
                                token[found]='.';
                            row.push_back(std::stof(token));
                        }
                        catch (std::invalid_argument ex) {
                            std::cout << "  ";
                        }
                }
                colNum++;
            }
            if(colNum == data->totalColNum)
                row.push_back((float)(1.0f/0.0f));
            data->data.push_back(row);
        }
        rowNum++;
    }
    in.close();
}


