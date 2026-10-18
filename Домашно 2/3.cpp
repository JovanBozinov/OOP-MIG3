#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
using namespace std;

struct File{
    string name;
    string extension;
    uint64_t byteSize;
};

string getFullFilename(File &f){
    return f.name + '.' + f.extension;
}

struct Directory{
    string name;
    vector<File*> files;
    vector<Directory*> dirs;
    Directory* parent=nullptr;
};

void Up(Directory &current){
    if(current.parent==nullptr)
        cout << "/(root)" << '\n';
    else
        cout << current.parent->name << '\n';
}

int main(){
    Directory a, b, c, d, e, f;
    a.name="A";
    b.name="B";
    c.name="C";
    d.name="D";
    e.name="E";
    f.name="F";

    a.dirs.push_back(&b);
    b.parent=&a;

    d.dirs.push_back(&e);
    e.parent=&d;
    c.dirs.push_back(&d);
    d.parent=&c;

    Up(a);
    Up(b);
    Up(c);
    Up(d);
    Up(e);
    Up(f);

    return 0;
}