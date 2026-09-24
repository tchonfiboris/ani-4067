#ifndef MA_CLASS
#define MA_CLASS 

#ifdef ACTIVE_CLASS

class MaClass{
    public:
         void afficher() 
         const {std::cout << "la classe est active" << std::endl;}
};

#else

class MaClass;

#endif
#endif