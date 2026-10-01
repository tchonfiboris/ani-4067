#include <iostream>
/* #define ACTIVE_CLASS */
#include "header.hpp"



void TesterAvecDefine() {
    std::cout << "___test1(avec #Define)--- " << std::endl;
    MaClass objet;
    objet.afficher();
   }

/* void TestSansDefine(){
    std::cout << "\n---test 2(sans define)---" <<std:: endl;

    MaClass* ptr = nullptr;
    std::cout << "la classe est une coquille vide" << std::endl;

    std::cout << ptr << std::endl;
} */

int main() {
   /*  std::cout << "Hello from exo5-le_define_qui_manque!" << std::endl; */
    
   /* TestSansDefine(); */
    TesterAvecDefine();

    return 0;
}
