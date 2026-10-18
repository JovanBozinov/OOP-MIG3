#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
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

uint64_t DirSize(Directory &d){
    uint64_t sz=0;
    for(size_t i=0; i<d.files.size(); i++){
        sz+=d.files[i]->byteSize;
    }
    for(size_t i=0; i<d.dirs.size(); i++){
        sz+=DirSize(*d.dirs[i]);
    }
    return sz;
}

void printSize(Directory &d){
    cout << "The size of directory " << d.name << " is " << DirSize(d) << "B\n";
}

int main(){
    Directory one;
    one.name="ONE";
    File x, y, z;
    x.byteSize=1024;
    y.byteSize=512;
    z.byteSize=12345;
    one.files.push_back(&x);
    one.files.push_back(&y);
    one.files.push_back(&z);

    Directory two;
    two.name="TWO";
    File a, b, c;
    a.byteSize=10;
    b.byteSize=1000000;
    c.byteSize=9245015;
    two.files.push_back(&a);
    two.files.push_back(&b);
    two.files.push_back(&c);

    Directory three;
    three.name="THREE";
    File d;
    d.byteSize=777777;
    three.files.push_back(&d);

    Directory four;
    four.name="FOUR";
    File e, f;
    e.byteSize=8388608;
    f.byteSize=83886082;
    four.files.push_back(&e);
    four.files.push_back(&f);

    one.dirs.push_back(&two);
    three.dirs.push_back(&four);
    one.dirs.push_back(&three);

    printSize(one);
    printSize(two);
    printSize(three);
    printSize(four);

    return 0;
}