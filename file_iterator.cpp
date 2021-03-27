
#include "file_iterator.h"

////////////////// DEBUG/OTHER FUNCTIONS ////////////////
inline bool file_exists(const string& name) 
    // check if file path exists
{
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

void file_iterator::print_file()
    // debugging purpose
    // just prints all lines in the two line strng vectors
{
    for (size_t i = 0; i < line.size(); ++i){
        cout << line[i] << '\n';
    }
    cout << "\n=======================================\n";
    for (size_t i = 0; i < line_reverse.size(); ++i){
        cout << line_reverse[i] << '\n';
    }
}

vector<string> file_iterator::data_split(const string& data)
    // splits strings to extract data of the date
    // return vector containing all the data (all in string format)
{
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
VALUE_RET file_iterator::data_curr()
    // returns a struct VALUE_RET that contains the data for that day
{
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
    }
    if (curr_reverse_line_index == 0){
        cerr << "curr_reverse_line_index is going to below zero\n";
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
/////////////// CLASS CONSTRUCTOR ///////////////

file_iterator::file_iterator(const string& f_name)
       // first checks if file exists
       // fill up line and reverse_line vectors
       // also gets rid of the first line of the csv file
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
        line_reverse.push_back(temp);
    }
    line = line_reverse;
    reverse(line.begin(), line.end());

    curr_line_index = 0;
    curr_reverse_line_index = line.size() - 1;
}
