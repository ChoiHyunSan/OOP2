#include <iostream>
#include "Pet.h"
#include "Dog.h"
using namespace std;


int main()
{
    Dog* dog = new Dog("Happy", 1);

    string DogName = "Happy";

    //dog->setName(DogName);
    //dog->setAge(1);
    dog->bark();

   
    delete dog;

    return 0;
}


