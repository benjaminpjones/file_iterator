
#include "file_iterator.h"

////////////////// DEBUG/OTHER FUNCTIONS ////////////////
inline bool file_exists(const string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

void file_iterator::print_file(){
    for (size_t i = 0; i < line.size(); ++i){
        cout << line[i] << '\n';
    }
    cout << "\n=======================================\n";
    for (size_t i = 0; i < line_reverse.size(); ++i){
        cout << line_reverse[i] << '\n';
    }
}

vector<string> file_iterator::data_split(const string& data){
    vector<string> v;
    string temp = "";
    for (size_t i = 0; i < data.size(); ++i){
        if (data[i] == ';'){
            v.push_back(temp);
            temp = "";
        } else {
            temp += data[i];
        }
    }
    v.push_back(temp);
    return v;
}
////////////////// MEMBER FUNCTION //////////////

VALUE_RET file_iterator::data_curr(){
    VALUE_RET ret;
    vector<string> v;
    curr_line = line[curr_line_index];
    v = data_split(curr_line);

    ret.date = v[0];
    ret.open = stod(v[1]);
    ret.high = stod(v[2]);
    ret.low = stod(v[3]);
    ret.close = stod(v[4]);
    ret.volume = stoi(v[5]);
    return ret;
}

int file_iterator::operator++(){
    if (curr_line_index > line.size()){
        cerr << "curr_line_index over index\n";
        return -1;
    }
    if (curr_reverse_line_index == 0){
        cerr << "curr_reverse_line_index is going to below zero\n";
        return -1;
    }
    ++curr_line_index;
    --curr_reverse_line_index;
    return curr_line_index;
}

int file_iterator::operator--(){
    if (curr_reverse_line_index > line.size()){
        cerr << "curr_reverse_line_index over possible index\n";
        return -1;
    }
    if (curr_line_index == 0){
        cerr << "curr_line_index is going to go below zero\n";
        return -1;
    }
    --curr_line_index;
    ++curr_reverse_line_index;
    return curr_line_index;
}

// check if correct
int file_iterator::get_reverse_line_index(int i){
    return line.size() -1 - i;
}
int file_iterator::get_line_index(){
    return this->curr_line_index;
}

void file_iterator::iterate(int i){
    if (i > 0){
        for (int j = 0; j < i; ++j){
            if (curr_line_index > line.size()){
                cerr << "curr_line_index over index\n";
                exit(1);
            }
            if (curr_reverse_line_index == 0){
                cerr << "curr_reverse_line_index is going to below zero\n";
                exit(1);
            }
            ++curr_line_index;
            --curr_reverse_line_index;
        }
    } else if (i < 0){
        for (int j = 0; j < (i * -1); ++j){
            if (curr_reverse_line_index > line.size()){
                cerr << "curr_reverse_line_index over possible index\n";
                exit(1);
            }
            if (curr_line_index == 0){
                cerr << "curr_line_index is going to go below zero\n";
                exit(1);
            }
            --curr_line_index;
            ++curr_reverse_line_index;
        }
    }
}
/////////////// CLASS CONSTRUCTOR ///////////////

file_iterator::file_iterator(const string& f_name)
{
    if (!file_exists(f_name)) {
        cerr << "File does not exist\n";
        exit(1);
    }

    ifile.open(f_name, ios::in);
    if (!ifile) {
        cerr << "ifile error...\n";
        exit(1);
    }

    string temp;
    while( getline(ifile, temp) ){
        if (temp[0] == 'd') continue;
        line.push_back(temp);
    }
    line_reverse = line;
    reverse(line_reverse.begin(), line_reverse.end());

    curr_line_index = 0;
    curr_reverse_line_index = line.size() - 1;
}
