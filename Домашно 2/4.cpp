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

bool findFile(File &what, Directory &where){
    for(size_t i=0; i<where.files.size(); i++){
        if(getFullFilename(what)==getFullFilename(*where.files[i])){
            return true;
        }       
    }
    for(size_t i=0; i<where.dirs.size(); i++){
        if(findFile(what, *where.dirs[i]))
            return true;
    }
    return false;
}

bool findDir(Directory &what, Directory &where){
    if (what.name==where.name)
        return true;
    for(size_t i=0; i<where.dirs.size(); i++){
        if(what.name==where.dirs[i]->name)
            return true;
    }
    for(size_t i=0; i<where.dirs.size(); i++){
        if(findDir(what, *where.dirs[i]))
            return true;
    }
    return false;
}

void printFound(bool check){
    if(check)
        cout << "Found!" << '\n';
    else
        cout << "Not Found!" << '\n';
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

    printFound(findFile(d, one));
    printFound(findFile(x, two));
    printFound(findFile(e, four));
    cout << '\n';
    printFound(findDir(three, one));
    printFound(findDir(three, two));
    printFound(findDir(one, four));

    return 0;
}