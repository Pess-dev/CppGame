#include <iostream>
#include <conio.h>
#include <list>
 
using namespace std;

static int deb;

class Base
{
    public:
    
    
    Base(){
       // deb=0;
        deb+=1;
    }
        virtual string output()
        {
            return "Parent ";
        }
};
 
// class Child: public Base
// {
//     public:
//         virtual string output()
//         {
//             // вызов метода базового класса в методе наследника
//             return "Child ";
//         }
// };

void f(Base b){
    list<Base> l2;
    l2.push_front(b);
} 
 
int main()
{  

    Base ptr=Base();
    cout<<deb<<endl;

    list<Base> l;
    l.push_back(ptr);
    cout<<deb<<endl;
     
    f(ptr);
    cout<<deb<<endl;
    // Base *l=new Base[1];
    
    // Base * ptr;
 
    // ptr = new Child();
    // l[0]=*ptr;

    // std::cout << ptr -> output() << "\n"; // вызов метода наследника 
    // std::cout << (*l).output() << "\n"; // попытка вызова метода наследника(
    // delete ptr;
    
    return 0;    
}
