#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class File{
    string name;
    string extension;
    uint64_t byteSize;

public:
    File(string n, string e, uint64_t b){
        name=n;
        extension=e;
        byteSize=b;
    }
    void setFileName(string n){
        name=n;
    }
    void setFileExt(string e){
        extension=e;
    }
    void setFileSize(uint64_t b){
        byteSize=b;
    }

    string FullFilename(){
        return name+'.'+extension;
    }
    string getFileName(){
        return name; 
    }
    string getFileExt(){
        return extension;
    }
    uint64_t getFileSize(){
        return byteSize;
    }

    void CheckFileDups(unordered_map<string, bool> &mf){
        string filename=FullFilename();
        while(mf[filename]){
            cout << "Name is taken, try another one!\n";
            cin >> name >> extension;
            filename=FullFilename();
        }
        mf[filename]=true;
    }
};

class Directory{
    string name;
    vector<File*> files;
    vector<Directory*> dirs;
    Directory* parent=nullptr;

public:
    Directory(string n){
        name=n;
    }
    Directory(string n, vector<File*> f, vector<Directory*> d, Directory* p){
        name=n;
        files=f;
        dirs=d;
        parent=p;
    }
    void setDirName(string n){
        name=n;
    }
    void setDirFiles(vector<File*> f){
        files=f;
    }
    void setDirDirs(vector<Directory*> d){
        dirs=d;
    }
    void setDirPar(Directory* p){
        parent=p;
    }
    void addFile(File *f){
        files.push_back(f);
    }
    void addDir(Directory *d){
        dirs.push_back(d);
    }

    string getDirname(){
        return name;
    }
    vector<File*> getFiles(){
        return files;
    }
    vector<Directory*> getDirs(){
        return dirs;
    }
    Directory* getParent(){
        return parent;
    }

    void CheckDirDups(unordered_map<string, bool> &md){
        while(md[name]){
            cout << "Name is taken, try another one!\n";
            cin >> name;
        }
        md[name]=true;
    }
    void printDir(){
        cout << "Directory: " << name << '\n';
        for (size_t i=0; i<files.size(); i++){
            cout << "File: " << files[i]->FullFilename() << '\n';
        }
        for (size_t i=0; i<dirs.size(); i++){
            dirs[i]->printDir();
        }
    }
    void Up(){
        if (parent==nullptr)
            cout << "/(root)\n";
        else 
            cout << parent->name << '\n';
    }

    bool FindFile(File &what){
        for (size_t i=0; i<files.size(); i++){
            if (what.FullFilename()==files[i]->FullFilename())
                return true;
        }
        for (size_t i=0; i<dirs.size(); i++){
            if (dirs[i]->FindFile(what))
                return true;
        }
        return false;
    }
    bool FindDir(Directory &what){
        if (name==what.getDirname())
            return true;
        for (size_t i=0; i<dirs.size(); i++){
            if (dirs[i]->getDirname()==what.getDirname())
                return true;
        }
        for (size_t i=0; i<dirs.size(); i++){
            if (dirs[i]->FindDir(what))
                return true;
        }
        return false;
    }
    void printFound(bool check){
        if (check)
            cout << "Found!\n";
        else
            cout << "Not Found!\n";
    }

    uint64_t DirSize(){
        uint64_t sz=0;
        for (size_t i=0; i<files.size(); i++)
            sz+=files[i]->getFileSize();
        for (size_t i=0; i<dirs.size(); i++)
            sz+=dirs[i]->DirSize();
        return sz;
    }
    void printSize(){
        cout << "The size of directory " << name << " is " << DirSize() << "B\n";
    }
};

int main(){
    unordered_map<string, bool> fNames, dNames;
    File r("A", "txt", 32), t("A", "txt", 64);
    fNames[r.FullFilename()]=1;
    t.CheckFileDups(fNames);
    Directory rd("KKK"), td("KKK");
    dNames[rd.getDirname()]=1;
    td.CheckDirDups(dNames);

    Directory one("ONE");
    File x("X", "pdf", 32), y("Y", "txt", 64), z("Z", "jpg", 902);
    one.addFile(&x);
    one.addFile(&y);
    one.addFile(&z);

    Directory two("TWO");
    File a("A", "png", 2694), b("B", "exe", 956244), c("C", "docx", 3275);
    two.addFile(&a);
    two.addFile(&b);
    two.addFile(&c);

    Directory three("THREE");
    File d("D", "app", 6362);
    three.addFile(&d);

    Directory four("FOUR");
    File e("E", "ppt", 867625), f("F", "jpeg", 25491);
    four.addFile(&e);
    four.addFile(&f);

    two.addDir(&three);
    one.addDir(&two);
    one.addDir(&four);
    three.setDirPar(&two);
    two.setDirPar(&one);
    four.setDirPar(&one);

    one.printDir();
    cout << '\n';
    two.printDir();
    cout << '\n';

    one.Up();
    two.Up();
    three.Up();
    four.Up();

    one.printFound(one.FindFile(d));
    four.printFound(four.FindFile(a));
    one.printFound(one.FindDir(four));
    two.printFound(two.FindDir(four));

    one.printSize();
    three.printSize();

    return 0;
}