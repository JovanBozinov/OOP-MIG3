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
};

void printDir(Directory &d){
    cout << "Direcotry: " << d.name << '\n';
    for (size_t i=0; i<d.files.size(); i++){
        cout << "File: " << getFullFilename(*d.files[i]) << '\n';
    }
    for (size_t i=0; i<d.dirs.size(); i++){
        printDir(*d.dirs[i]);
    }
}

int main(){
    Directory one;
    one.name="ONE";
    File x, y, z;
    x.name="X";
    x.extension="pdf";

    y.name="Y";
    y.extension="txt";

    z.name="Z";
    z.extension="jpg";

    one.files.push_back(&x);
    one.files.push_back(&y);
    one.files.push_back(&z);

    Directory two;
    two.name="TWO";
    File a, b, c;
    a.name="A";
    a.extension="png";

    b.name="B";
    b.extension="exe";

    c.name="C";
    c.extension="docx";

    two.files.push_back(&a);
    two.files.push_back(&b);
    two.files.push_back(&c);

    Directory three;
    three.name="THREE";
    File d;
    d.name="D";
    d.extension="app"; 

    three.files.push_back(&d);

    two.dirs.push_back(&three);
    one.dirs.push_back(&two);

    Directory four;
    four.name="FOUR";
    File e;
    e.name="E";
    e.extension="ppt";

    four.files.push_back(&e);

    one.dirs.push_back(&four);

    printDir(one);
    cout << '\n';
    printDir(two);
    cout << '\n';
    printDir(four);


    return 0;
}