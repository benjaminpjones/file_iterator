#ifndef FILE_ITERATOR_H
#define FILE_ITERATOR_H

#include <bits/stdc++.h>

using namespace std;


struct VALUE_RET {
    string date;
    double open;
    double high;
    double low;
    double close;
    int volume;
};

class file_iterator {
    public:
        file_iterator(const string& f_name);
        ~file_iterator(){ ifile.close(); };
        int operator++();
        int operator--();
        VALUE_RET data_curr();
        int get_reverse_line_index(int i);
        int get_line_index();
        void iterate(int i);

        // debug
        void print_file();
    private:
        vector<string> data_split(const string& data);
        ifstream ifile;
        vector<string> line;
        vector<string> line_reverse;
        string curr_line;
        size_t curr_line_index;
        size_t curr_reverse_line_index;
};

#endif
