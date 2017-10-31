//nem lesz beadva
#include <iostream>
//nem lesz beadva
using namespace std;

/*
 * /**!
 *  Publikus interface a referenciszámolt objektumokhoz
 * *//*
class refCounted {
public:
     //! metódus a pRefernce számának a növeléséhez
    void incRefCnt() {
    }
    /! metódus a pReference számának a csökkentéséhez
    int decRefCnt() {
    }
};*/
/**
 *  Publikus interface a referenciszámolt objektumokhoz
 * */
class refCounted {
private:
    int count; // Reference count

public:
    /** metódus a pRefernce számának a növeléséhez
     * vissza is adja ezt az értéket, miután megnövelte
     * */
    void incRefCnt() {
        // Increment the pReference count
        count++;
    }
    /** metódus a pReference számának a csökkentéséhez
     *
     * vissza is adja ezt az értéket, miután csökkentette
     * */
    int decRefCnt() {
        // Decrement the pReference count and
        // return the pReference count.
        return --count;
    }
};


/** my_pointer template class - 'okos' pointer megvalósítás
 * */
template<class T>
class my_pointer{
private:

    T *pData; /**< pointer */
    refCounted *pReference; /**< referencia számláló */

public:

    /** Constructor
     *
     * Létrehozunk egy új pReference-t
     * Majd növeljük
     */
    my_pointer() : pData(0), pReference(0) {
        pReference = new refCounted();
        pReference->incRefCnt();
    }

    /**Paraméteres constructor
     *
     * Létrehozunk egy új pReference-t
     * Majd növeljük
     */
    my_pointer(T *pValue) : pData(pValue), pReference(0) {
        pReference = new refCounted();
        pReference->incRefCnt();
    }

    /** Copy constructor
     *
     * lemásolja a pData és pReference pointer-t
     * utána növeli a pReference számát
     */
    my_pointer(const my_pointer<T> &myPointer) : pData(myPointer.pData), pReference(myPointer.pReference) {
        pReference->incRefCnt();
    }
    /** Destructor
     *
     * Okos pointernek nincs alapértelmezetten destruktora,
     * viszont az okos pointernek lesz és ő végzi a memória felszabadítást
     *
     * Csökkenti a pReference számát
     * Ha ez 0, akkor törli a pData-t és a pReference-t
     */
    ~my_pointer() {
        if (pReference->decRefCnt() == 0) {
            delete pData;
            pData = nullptr;
            delete pReference;
            pReference = nullptr;
        }
    }

     /** Dereferencing operator (*)
     *
     *  @return
     */
     T &operator*() {
        return *pData;
    }

    /** Indirection operator
     *
     *  metódusainak az eléréséhez
     *  @return T-re mutató pointer
     */
    T *operator->() {
        return pData /*!= 0 ? pData : 0*/;
    }

    /**  operator== overloading/túlterhelés
    *
    * @return bool, hogy megegyezik-e a 2 address
    */
    bool operator==(const my_pointer<T> &myPointer){
        return this == &myPointer;
    }

    /**   operator!= overloading/túlterhelése
     *
     *  @return bool, nem egyenlő a 2 address
     */
    bool operator!=(const my_pointer<T> &myPointer){
        return this != &myPointer;
    }

    /**  operator= (assignment) overloading/túlterhelés*/
    my_pointer<T> &operator=(const my_pointer<T> &myPointer) {

        /**Ellenőrizzük, hogy ne saját magának akarjon értéket adni*/
        if (this != &myPointer)
        {

            /**CSökkentjük a pReference számát és ha 0, akkor memória felszabadítás*/
            if (pReference->decRefCnt() == 0) {
                delete pData;
                pData = nullptr;
                delete pReference;
                pReference = nullptr;
            }
            /**Lemásoljuk a pData és pReference pointert
            majd növeljük a pReference számát*/
            pData = myPointer.pData;
            pReference = myPointer.pReference;
            pReference->incRefCnt();
        }
        return *this;
    }

};

/** nem lesznek beadva*/
class Person {
    int age;


public:

    Person() : age(0) {
        cout<< "Person created" <<endl;
    }

    Person(int age) :  age(age) {
    }

    ~Person() {
        cout<< "Deleted " << endl;
    }

    void Display() {
        cout << " Age = " << age << endl;
    }

};
int main() {
//    my_pointer<refCounted> obj1 = new refCounted();
//    my_pointer<refCounted> obj2 = obj1;

   my_pointer<Person> p(new Person( 25));
/*
    my_pointer<Person> ob1 = new Person;

    p->Display();
    {
        my_pointer<Person> q = p;
        q->Display();
        // Destructor of q will be called here..
        my_pointer<Person> r;
        r = p;
        r->Display();
        // Destructor of r will be called here..

    }
    cout<<"bam bam\n";
    p->Display();


    cout<< (&p);*/
/*
    Person *per = new Person( 25);
    my_pointer<Person> p = per;
    p->Display();*/

    my_pointer<Person> * a = p;

    return 0;
}


