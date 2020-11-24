// my_string.cpp
#include <iostream>
#include "my_string.h"
#include "my_sstream.h"

using std::cout, std::endl;
// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods

// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{0}), _capacity(1), _size(0) {
    // cout << "CREATED MY_STRING" << endl;
}
//   rule of "3"
//     my_string copy constructor
my_string::my_string(const my_string& other): 
_data(new char[other._capacity]{0}), _capacity(other._capacity), _size(other._size){

    copy(other);

    // cout << "COPYING COMPLETED" << endl;
}
//     my_string copy assignment
my_string& my_string::operator=(const my_string& rhs){
    if(this != &rhs){
        copy(rhs);
    }

    // cout << "COPY ASSIGNMENT COMPLETED" << endl;
    
    return *this;
}
//     destructor
my_string::~my_string(){
    delete[] _data;
    _data = nullptr;
    _capacity = 0;
    _size = 0;
    // cout << "DELETED MY_STRING" << endl;
}
//   c-string copy constructor
my_string::my_string(const char* other): _data(new char[1]{0}), _capacity(1),_size(0){    

    size_t otherLength = getLength(other);
    _size = otherLength;
    _capacity = otherLength;
    destroy();

    _data = new char[_capacity]{0};
    

    for(size_t i = 0; i < _size; i++){
        _data[i] = other[i];
    }

    // cout << "C-STRING COPIED" << endl;
}
// element access
char* my_string::getData() const { return _data; }
size_t my_string::getSize() const{ return _size; }
//   at 
const char& my_string::at(size_type index) const{ return _data[index]; }
char& my_string::at(size_type index){ return _data[index]; }

//   front
const char& my_string::front() const{ return _data[0]; }
char& my_string::front(){ return _data[0]; }

//   operator[]
const char& my_string::operator[](size_type index) const{ return at(index); }
char& my_string::operator[](size_type index){ return at(index); }

// capacity
//   empty
bool my_string::empty() const{
    if(_size == 0 || _size == 1){
        return true;
    }
    return false;
}
//   size
size_t my_string::size() const{ return getSize()-1; }
//length
size_t my_string::length() const{ return getSize()-1; }

// operations
//   concatenation
//     my_string + my_string (non-member, friend)
my_string operator+(my_string lhs, const my_string& rhs){

    for(size_t i = 0; i < rhs._size-1; i++){
        lhs.append(rhs._data[i]);
    }

    return lhs;
}
//     my_string + c-string (non-member, friend)
my_string operator+(my_string lhs, const char* rhs){

    my_string temp;
    // cout << "here " << endl;
    temp.copy(rhs);

    my_string temp2 = lhs + temp;
    lhs = temp2;
    return lhs;
}
//     my_string + char (non-member, friend)
my_string operator+(my_string lhs, char rhs){
    
    lhs.append(rhs);
    return lhs;
}
//     c-string + my_string (non-member, friend)
my_string operator+(const char* lhs, const my_string& rhs){

    my_string temp = lhs;
    my_string temp2 = temp + rhs;
    return temp2;
}
//     char + my_string (non-member, friend)
my_string operator+(char lhs, my_string rhs){
    
    my_string temp = "";
    my_string temp2 = temp + lhs;
    temp = temp2 + rhs;
    rhs = temp;
    return rhs;
}
//     my_string += my_string
my_string& my_string::operator+=(const my_string& rhs){
    *this = *this + rhs;
    return *this;
}
//     my_string += c-string
my_string& my_string::operator+=(const char* rhs){
    *this = *this + rhs;
    return *this;
}
//     my_string += char
my_string& my_string::operator+=(char rhs){
    *this = *this + rhs;
    return *this;
}

// search
//   find
my_string::size_type my_string::find(const my_string& str, my_string::size_type pos) const{

    if(str._size > _size){
        return npos;
    }
    bool strFound = true;

    for(size_t i = pos; i < _size-str._size+1; i++){

        for(size_t j = i; j < str._size+i-1; j++){
            if(str[j-i] != _data[j]){
                strFound = false;
            }
        }
        if(strFound){
            cout << _data[i] << endl;
            return i;
        }

        strFound = true;
    }
    return npos;
}

// non-member functions
//   relational operators
//     my_string == my_string
bool operator==(const my_string& lhs, const my_string& rhs){

    if(lhs.getSize() != rhs.getSize()){
        return false;
    }
    
    for(size_t i = 0; i < lhs.getSize(); i++){
        if(rhs[i] != lhs[i]){
            return false;
        }
    }
    return true;
}
//     my_string == c-string
bool operator==(const my_string& lhs, const char* rhs){
    my_string temp = rhs;

    if(lhs.getSize() != temp.getSize()){
        return false;
    }
    
    for(size_t i = 0; i < lhs.getSize(); i++){
        if(temp[i] != lhs[i]){
            return false;
        }
    }
    return true;
}

//   stream operators
//     ostream instertion operator
std::ostream& operator<<(std::ostream& os, const my_string& rhs){
    os << rhs.getData();
    
    return os;
}

    // istream extraction operator
std::istream& operator>>(std::istream& os, my_string& str){
    char temp = '\0';
    str = "";
    while(temp != ' '){
        os >> temp;
        str += temp;
        if (temp == ' '){
            cout << "gamer" << endl;
        }
        cout << "stuck in here" << endl;
    }
    return os;
}

//     getline
std::istream& getline(std::istream& is, my_string& str, char delim){
    char temp = '\0';
    str = "";
    is >> temp;
    while(temp != delim || !is.eof()){
        str += temp;
        is >> temp;
        
    }

    cout << "out here" << endl;
    return is;
}
//   numeric conversions
//     to_string

// my_istringstream methods

my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}

void my_istringstream::eat_whitespaces() {
    while (idx < _str.size() && isspace(_str[idx])) {
        idx++;
    }
}

my_istringstream& my_istringstream::operator>>(my_string& str) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    my_string s;
    while (idx < _str.size() && !isspace(_str[idx])) {
        s += _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    str = s;
    return *this;
}

my_istringstream& my_istringstream::operator>>(char& c) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    if (idx < _str.size()) {
        c = _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    return *this;
}

bool my_istringstream::good() const { return !(state_fail || state_eof); }
bool my_istringstream::fail() const { return state_fail; }
bool my_istringstream::eof() const { return state_eof; }

// TODO(student): define other my_istringstream methods, if any
//erase
my_string& my_string::erase(size_t pos, size_t len){
    my_string temp = *this;
    my_string temp2 = "";
    
    for(size_t i = 0; i < pos; i++){
        temp2 += temp[i];
    }
    for(size_t i = len; i < temp._size; i++){
        temp2 += temp[i];
    }

    *this = temp2;
    _size--;
    _capacity--;
    return *this;
}

//insert
my_string& my_string::insert(size_t pos, const my_string& str){
    my_string temp = "";

    for(size_t i = 0; i < pos; i++){
        temp += _data[i];
    }

    temp += str;

    erase(0,pos);

    temp += _data;
    *this = temp;

    return *this;

}

//to_string
my_string to_string(int val){
    char c;
    my_string output = "";
    my_string temp = "";
    bool neg = false;

    if(val == 0){
        c = '0' + val;
        output += c;
    }

    if(val < 0){
        neg = true;
        val *= -1;
    }

    while (val != 0){
        c = '0' + val % 10;
        temp += c;
        output.insert(0,temp);
        temp = "";
        val /= 10;
    }

    if(neg){
        output.insert(0,"-");
    }

    return output;
}