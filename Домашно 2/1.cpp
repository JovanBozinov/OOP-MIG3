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

void CheckFileDups(unordered_map<string, bool> *mf, File &f){
    string name=getFullFilename(f);
    while ((*mf)[name]){
        cout << "Name is taken, try another one!" << '\n';
        cin >> f.name >> f.extension;
        name=getFullFilename(f);
    }
    (*mf)[name]=1;
}

void CheckDirDups(unordered_map<string, bool> *md, Directory &d){
    while ((*md)[d.name]){
        cout << "Name is taken, try another one!" << '\n';
        cin >> d.name;
    }
    (*md)[d.name]=1;
}

int main(){
    unordered_map<string, bool> fNames, dNames;
    File a, b;
    a.name="A";
    a.extension="txt";
    fNames[getFullFilename(a)]=1;
    cin >> b.name >> b.extension;
    CheckFileDups(&fNames, b);
    Directory c, d;
    c.name="Okay";
    dNames[c.name]=1;
    cin >> d.name;
    CheckDirDups(&dNames, d);

    return 0;
}