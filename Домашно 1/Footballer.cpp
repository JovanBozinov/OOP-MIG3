#include <iostream>
void strcpy(char *where, char *from){
    while(*from){
        *where=*from;
        from++;
        where++;
    }
    *where='\0';
}
struct birth{
    int day;
    int month;
    int year;
};
struct futbaler{
    char name[50];
    char club[50];
    birth date;
};

int main(){
    futbaler n;
    strcpy(n.name, "Jovan Bozinov");
    strcpy(n.club, "Barcelona");
    n.date.day=1;
    n.date.month=7;
    n.date.year=2009;
    futbaler *np=&n;
    std::cout << "Name: " << np->name << '\n' << "Club: " << np->club << '\n';
    std::cout << "Date of birth: " << np->date.day << '.' << np->date.month << '.' << np->date.year;

    return 0;
}