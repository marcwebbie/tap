/*
This file is part of Tap.

    Tap is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tap is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tap.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TAP_H
#define TAP_H



#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <sstream>


namespace mjr{
typedef unsigned long int ulint;
typedef unsigned const char* cpByte;                    // help iteration
typedef unsigned char* pByte;                           // help iteration
static const int myBASE = (1<<8);

class Tap{
public:
    typedef unsigned char Byte;
    typedef std::vector<Byte>::reverse_iterator re_iter;
    typedef std::vector<Byte>::const_reverse_iterator re_citer;
    typedef std::vector<Byte>::iterator iter;
    typedef std::vector<Byte>::const_iterator citer;

    // [Constructors] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Tap() :data(1) {}                                           // x = 0
    //Tap(const std::string&);                                  // x = "123456"
    Tap(const char*);                                           // x = "123456"
    explicit Tap(ulint);                                        // x = 123456
    explicit Tap(citer from, citer to): data(from, to){}        // x(t2.beg, t2.end)
    explicit Tap(size_t sz, bool) : data(sz){}                  // bool is artificial
    Tap(const Tap&);                                            // copy Ctor
    Tap& operator=(const Tap&);

    // [Managers] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    int normalize();
    void resize(size_t nsz, Byte elem='\0') { data.resize(nsz,elem); }
    void push_back(Byte by) { data.push_back(by); }
    void reinit(Byte by='\0') { data.assign(len(), by); }       // reinit all digits
    // to '\0' by default

    // [Checkers] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    size_t len() const { return data.size(); }
    size_t size() const { return data.size(); }
    std::string to_s(size_t base=10) const ;
    std::string print_raw() const ;
    ulint to_ul() const ;

    // [Element access] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Byte& operator[](size_t i) { return data[i]; }
    Byte operator[](size_t i) const { return data[i]; }
    const Byte* to_arr() const { return &data[0]; }
    const Byte* to_rarr() const { return &data[len()-1]; }
    unsigned char* to_arr() { return &data[0]; }                /// @note non const
    Byte* to_rarr() { return &data[len()-1]; }                  /// @note non const

    // [Iterators] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    iter begin() { return data.begin(); }
    iter end() { return data.end(); }
    re_iter rbegin() { return data.rbegin(); }
    re_iter rend() { return data.rend(); }
    re_citer rbegin() const { return data.rbegin(); }
    re_citer rend() const { return data.rend(); }
    citer begin() const { return data.begin(); }
    citer end() const { return data.end(); }

    // [Short operations] %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    /// @attention these functions change (*this)
    int quot(int);                                              /// @test
    int modulo(int);                                            /// @test
    int mult(int);                                              /// @test
    int add(int);                                               /// @test
    int diff(int);                                              /// @test

    Tap& operator++();
    Tap operator++(int);
    Tap& operator--();
    Tap operator--(int);
    Tap& operator*=(const Tap& t2);
    Tap& inc1();                                                // TEST: Do some testing
    void inc1v2();                                              // @test
    void inc1v3();                                              // @test
    Tap pow(Tap);                                               // FIXME: slow opperation
    //..
private:

    std::vector<Byte> data;
    //..
};


class TapConvertionException{
public:
    TapConvertionException(const std::string& s) : message(s) {}
    std::string message;
};


class Util{
public:
    template<typename T>
    static std::string stringfy(T x)
    {
        std::ostringstream o;
        if (!(o << x))
            throw TapConvertionException("The number couldn't be converted into a string");
        return o.str();
    }

    template<typename Base>
    static int product(int n, unsigned char* z, unsigned char* x, int y, Base base){
        unsigned carry = 0;
        for (int i = 0; i < n; i++) {
            carry += x[i]*y;
            z[i] = carry%base;
            carry /= base;
        }
        return carry;
    }

private:
    Util();
    //..
};


}//namespace mjr


// ============
// Global operators
// ============
mjr::Tap operator* (const mjr::Tap&, const mjr::Tap&);
mjr::Tap operator+ (const mjr::Tap&, const mjr::Tap&);
mjr::Tap operator- (const mjr::Tap&, const mjr::Tap&);
mjr::Tap operator/ (mjr::Tap, mjr::Tap);
mjr::Tap operator% (const mjr::Tap&, const mjr::Tap&);
bool operator> (const mjr::Tap&, const mjr::Tap&);
bool operator< (const mjr::Tap&, const mjr::Tap&);
bool operator== (const mjr::Tap&, const mjr::Tap&);
bool operator!= (const mjr::Tap&, const mjr::Tap&);
std::ostream& operator<<(std::ostream& os, const mjr::Tap& tap_number);


//TODO: test if this functions are faster and implement it
bool is_equal(const mjr::Tap&, const mjr::Tap&);                   /// @test
mjr::Tap addv2 (const mjr::Tap&, const mjr::Tap&);                 /// @test



/* fromPOWER table found using...
    for(int i=2; i<=36; ++i)
        cout << "Base (" << i << ") estimate bits:" << log2(i) << endl;
 estimate of the number of bits for each digit...
   use [i] to accesse by the power ex:
   base of 3A0(number given) is 16, then, fromPOWER[i] return


double fromPOWERraw[] = {
    0, 0,       // base 0 and base 1
    1,          // base 2
    2, 2,       // base 3 to base 4
    3, 3, 3, 3, // base 5 to base 8
    4, 4, 4, 4, 4, 4, 4, 4,                         // base 9 to base 16
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, // base 17 to base 32
    6, 6, 6, 6  // base 33 to base 36
};*/

using std::cerr;

namespace{//anonymous
const unsigned long int ULL = 0;
// TABLES ======================================================================
static double K_BASE [] = {
    0, 0,       // base 0 and base 1
    1,          // base 2
    1.58496, 2, // base 3 to base 4
    2.32193, 2.58496, 2.80735, 3,   // base 5 to base 8
    3.16993, 3.32193, 3.45943, 3.58496, 3.70044, 3.80735, 3.90689, 4,   // base 9 to base 16
    4.08746, 4.16993, 4.24793, 4.32193, 4.39232, 4.45943, 4.52356, 4.58496, // base 17 to base 32
    4.64386, 4.70044, 4.75489, 4.80735, 4.85798, 4.90689, 4.9542, 5,    // base 17 to base 32
    5.04439, 5.08746, 5.12928, 5.16993 // base 33 to base 36

};
static char digset[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                        22,23,24,25,26,27,28,29,30,31,32,33,34,35};      // digit set

// CLASSES =====================================================================
class yAboveLimit{};    class badBase{};
class badString{};

// TYPEDEFS ====================================================================

//..
}//local namespace



namespace mjr{ //namespace mjr
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// → [CONSTRUCTORS]
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/**
 *  @brief Construct a Tap from a std::string
 *  @example Tap a = "123456";
*/
//Tap::Tap(const std::string& s)
//{
//    const short n_base = 10;                // base of given number.
//    size_t n = s.size();                    // n° of digs of number passed.

//    //int k = log2(n_base);                 // k is a conservative estimate of
//    // the number of bits
//    //int k = 0;                            // each digit in base represents.
//    //for(; (1<<k) < n_base; ++k) {}        // this is another way of finding k
//    double k = K_BASE[n_base];              // using a table seems faster

//    // find the number of bytes needed
//    // m = n*k/8
//    double temp = (n*k/8);                  // this(Tap) n° of digs.

//    size_t m = (temp > int(temp)) ? temp+1  // round number up if double
//                                  : temp;   // ex: 1.6 ==> 2

//    data.resize(m, '\0');

//    std::string::const_iterator p = s.begin();
//    for ( ; (*p && isalnum(*p) && digset[*p-'0'] < n_base); ++p){
//        int carry = this->mult(n_base);     // advance number by base..
//        if(carry)                           // lastValue * base
//            break;
//        this->add(digset[*p-'0']);          // add the number to this Tap
//    }
//    this->normalize();                      // normalize if trailling zeros
//}

/**
 *  @brief Construct a Tap from a zstring
 *  @example Tap a = "123456";
*/
Tap::Tap(const char* s)
{
    const short n_base = 10;                // base of given number.
    size_t n = std::strlen(s);                // n° of digs of number passed.

    //int k = log2(n_base);                 // k is a conservative estimate of
    // the number of bits
    //int k = 0;                            // each digit in base represents.
    //for(; (1<<k) < n_base; ++k) {}        // this is another way of finding k
    double k = K_BASE[n_base];              // using a table seems faster

    // find the number of bytes needed
    // m = n*k/8
    double temp = (n*k/8);                  // this(Tap) n° of digs.

    size_t m = (temp > int(temp)) ? temp+1  // round number up if double
                                  : temp;   // ex: 1.6 ==> 2

    data.resize(m, '\0');

    const char* p = s;
    for ( ; (*p && isalnum(*p) && digset[*p-'0'] < n_base); ++p){
        int carry = this->mult(n_base);     // advance number by base..
        if(carry)                           // lastValue * base
            break;
        this->add(digset[*p-'0']);          // add the number to this Tap
    }
    this->normalize();                      // normalize if trailling zeros
}


/**
 *  @brief Construct a Tap from an integer
 *  @example Tap a = 123456;
 *  @note This method seems a slow
*/
Tap::Tap(ulint u)
{
    ulint tmp = u;
    int i = 0, j = 1;
    for(; (tmp/=myBASE) > 0; ++j)           //  find n° of digits necessary
    {}
    data.resize(j, 0);

    while(u > 0){
        data[i++] = u%myBASE;               // an implicity % happens to
        u /= myBASE;                        // contract to byte size...
    }                                       // we could've done data[++i] = u;
}


/**
 *  @brief Copy constructor. Construct a Tap from another Tap
 *  @example Tap a = 123456;
*/
Tap::Tap(const Tap& t2): data(t2.len()){             // copy Ctor
    memcpy(&data[0], t2.to_arr(), t2.len());
    normalize();
}


/**
 *  @brief Copy assignement operator. Assign another Tap into (this)
 *  @example Tap a = 123456; Tap b = a;
 *  @param const Tap& t2:
 *  @return Tap&: reference to (this) after assignement
*/
Tap& Tap::operator=(const Tap& t2){
    if(&t2 != this){
        data.resize(t2.len());
        memcpy(&data[0], t2.to_arr(), t2.len());
    }
    return *this;
}




// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// → [MANAGEMENT] These operations change the obj data
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/**
 *  @brief Remove any trailing zeros from (this)
 *  @example (*this) == |0,1,2,3,4,5,6|     // in memory
 *           this->normalize();
 *           (*this) == |1,2,3,4,5,6|       // in memory
 *
 *  @return int: Result of operation: -1 means (this) was empty
 *          any number >= 0 means trailing '0' where found
*/
int Tap::normalize()
{
    int i = len()-1;
    while(i>=0 and (*this)[i] == 0)     // while zero keep going
        --i;
    if(i == -1)                         // i == -1 means (this) was empty
        data.resize(1, 0);
    else if(i >= 0)                     // i >= 0 means trailling zeros were
        data.resize(++i);               // found so resize it
    return len()-i;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// → [CHECKERS] These operations don't change obj data
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/**
 *  @brief Return a std::string representation of (this)
 *  @note This operation is slow.
 *
 *  @return std::string: u
*/
std::string Tap::to_s(size_t base/*=10*/) const{
    if(not base >= 2 && not base <= 35) throw badBase();
    if(len() == 0) return std::string("0");

    // 1. find needed size
    int k = K_BASE[base]; /*int k=0;*/
    //   for (k = 5; (1<<k) > base; k--)    // find the n° of digits necessarry
    /*continue*/;                           // for printing
    size_t sz = ( 8*len() )/k + 1 + 1;

    // 2. build std::string in base
    std::string str(sz, '$');
    int i = 0;

    size_t n = len()-1;
    Tap x = *this;                         // get a ref for preventing changes
    unsigned carry;
    do {
        // int r = x.modulo(base);
        carry = 0;
        for (int j = n; j >= 0; --j) {
            carry = carry*myBASE + x[j];
            x[j] = carry/base;
            carry %= base;
        }
        str[i++] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[carry];
        while (n > 1 && x[n-1] == 0)
            n--;
    } while (n > 1 || x[0] != 0);

    // 3. reverse and return
    std::string::reverse_iterator rit = str.rbegin();
    for( ; *rit == '$'; ++rit) /*continue*/;
    return std::string(rit, str.rend());
}



/**
 *  @brief Return a representation of (this) as an integer
 *  @note if (this) is larger than a ulint can hold it log error
 *  and returns 0
 *
 *  @return unsigned long int: u
*/
ulint Tap::to_ul() const {
    assert(len() < sizeof(ulint));
    //    if(len() > sizeof(ulint)){
    //        cerr << "Tap bigger than long int\n";
    //        return 0;
    //    }

    ulint u = 0;
    int i = this->len();
    while (--i >= 0)
        u = u*myBASE + (*this)[i];
    return u;
}



/**
 *  @name Print_raw
 *  @brief Build a std::string with the real values within the bytes
 *  the format is "[xxx, xxx, xxx]
 *  @return std::string:
*/
std::string Tap::print_raw() const
{
    std::string s;
    s.push_back('[');
    for(int i=len(); true; /*++i*/){
        int dat = int(data[i]);
        if(dat == 0)
            s.push_back('0');
        else
            s += mjr::Util::stringfy(dat);
        if(--i >= 0)
            break;
        s.push_back(',');
    }
    s.push_back(']');
    return s;
}




// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// → [UNARY OPERATORS]
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/**
 *  @brief Prefix increment operator: '++x'
 *  @return Tap&: reference to (this) after increment
*/
Tap& Tap::operator++(){
    int carry=0;
    carry = this->add(1);
    if(carry){
        this->resize(len()+1, carry);
    }
    return *this;

}


/**
 *  @brief Postfix increment operator: 'x++'
 *  @return Tap: copy of (this) before increment
*/
Tap Tap::operator++(int){
    unsigned char* p = &data[0];
    if(*p < (myBASE-1)){
        *p = *p+1;
        return *this;
    }
    int i=len();
    for( ;(*p == myBASE-1) and bool(i); --i)
        *p++ = 0;
    if(i==0)
        data.push_back(1);
    else
        ++(*p);

    return *this;

    /*
    Tap tmp = *this;
    int carry=0;
    carry = this->add(1);
    if(carry){
        this->resize(len()+1, carry);
    }
    return tmp;
    */
}


/**
 *  @brief Prefix decrement operator: '--x'
 *  @return Tap&: reference to (this) after decrement
*/
Tap& Tap::operator--(){
    this->diff(1);
    this->normalize();
    return *this;
}


/**
 *  @brief Postfix decrement operator: 'x--'
 *  @return Tap: copy of (this) before decrement
*/
Tap Tap::operator--(int){
    this->diff(1);
    this->normalize();
    return *this;
}


/**
 *  @brief Mutliply and assign value to (*this). ex: 'x *= y' as in 'x = x*y'
 *  @return Tap&: reference to (this) after operation
*/
Tap& Tap::operator*=(const Tap& t2){
    *this = (*this) * (t2);
    return *this;
}


/// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
/**
 *  @brief INCREMENT BY ONE ... performance test
 *  @return Tap&: reference to (this) after operation
 *  This function uses iterators for walking over digits
*/
/*
Tap& Tap::inc1()
{
    iter p = this->begin();
    iter last = this->end();
    while(*p == myBASE-1 and p != last)
        *p++ = 0;
    if(p == last)
        this->resize(len()+1, 1);
    else
        *p = *p+1;

    return *this;
}
*/


/// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
/**
 *  @brief INCREMENT BY ONE ... performance test
 *  @return Tap&: reference to (this) after operation
*/
/*
void Tap::inc1v2()
{
    unsigned char* p = &data[0];
    if(*p < (myBASE-1)){
        *p = *p+1;
        return ;
    }
    int i=len();
    for( ;(*p == myBASE-1) and bool(i); --i)
        *p++ = 0;
    if(i==0)
        data.push_back(1);
    else
        ++(*p);
}
*/

/// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
/**
 *  @brief INCREMENT BY ONE ... performance test
 *  @return Tap&: reference to (this) after operation
*/
/*
void Tap::inc1v3()
{
    pByte p = &data[0];
    if(*p < (myBASE-1)){
        *p = *p+1;
        return ;
    }
    int SIZE = len();
    int k = 0;

    asm __volatile__(
                "mov %0, %%rax;"
                "movl $0, %%edi;"
                "mov %1, %%edx;"

                "loop_start:\n\t"
                "cmp %%edi, %%edx;"         // we hit the end?
                "je final;"
                "cmpb $0xff,(%%rax);"       // is number pointed less than 255
                "jne to_add;"               // if so, jump to to_add and leave // jle

                "incl %%edi;"               // edi++

                "movb $0x0, (%%rax);"
                "inc %%rax;"
                "jmp loop_start;"

                "to_add:\n\t"               // increment number
                "incb (%%rax);"

                "final:\n\t"                //  end of loop
                "mov %%edi, %2"
                ://no output var
                :"m"(p), "m"(SIZE), "m"(k)
                :"rax", "edi", "edx");

    if(k == SIZE) data.push_back(1);
}

*/

Tap Tap::pow(Tap p)
{
    if (p == 0) return Tap(1);
    return (*this)*pow(--p);
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// → [MEMBER OPERATIONS] : Those operations change data
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/**
 *  @brief Set *this[0..n) => this/y
 *  @param int y:
 *  @return int: Modulo of operation
*/
int Tap::quot(int y){                   //
    if(y >= (2<<8) || y==0) throw yAboveLimit();
    Tap& z = *this;
    unsigned carry = 0;
    for (int i = z.len() - 1; i >= 0; i--) {
        carry = carry*myBASE + z[i];
        z[i] = carry/y;
        carry %= y;
    }
    return carry;
}


/**
 *  @brief Return modulo of operation => this/y
 *  @param int y:
 *  @return int: Modulo of operation
*/
int Tap::modulo(int y){
    if(y >= (2<<8) || y==0) throw yAboveLimit();
    Tap& z = *this;
    unsigned carry = 0;
    for (int i = z.len()-1; i >= 0; --i) {
        carry = carry*myBASE + z[i];
        carry %= y;
    }
    return carry;
}


/**
 *  @brief Set *this[0..n) => this*y return carry
 *  @param int y:
 *  @return int: carry
*/
int Tap::mult(int y){
    Tap& x = *this, &z = *this;
    int n = x.len();

    int carry = 0;
    for (int i = 0; i < n; i++){
        carry += x[i]*y;
        z[i] = carry % myBASE;
        carry /= myBASE;
    }
    return carry;
}


/**
 *  @brief Set *this[0..n) => this+y return carry
 *  @param int y:
 *  @return int: carry
*/
int Tap::add(int y){
    Tap& x = *this, &z = *this;
    int n = x.len();

    for(int i=0; i < n; ++i){
        y += x[i];
        z[i] = y % myBASE;
        y /= myBASE;
    }
    return y;
}


/**
 *  @brief Set *this[0..n) => this-y return borrow
 *  @param int y:
 *  @return int: borrow
*/
int Tap::diff(int y){                              //
    if(y > myBASE) throw yAboveLimit();

    Tap& x = *this, &z = *this;
    int n = len();
    for (int i = 0; i < n; i++) {
        int d = (x[i] + myBASE) - y;
        z[i] = d%myBASE;
        y = 1 - d/myBASE;
    }
    return y;
}


}//namespace mjr



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// -> [BASIC OPERATORS] (-, +, *, /)
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
using mjr::myBASE;

/**
 *  @brief Operator '*' → Multiply x by y
 *  @param const Tap& x:
 *  @param const Tap& y:
 *  @return Tap: result of operation x*y
*/
mjr::Tap operator* (const mjr::Tap& x, const mjr::Tap& y)
{
    unsigned n = x.len(), m = y.len();
    assert(n);
    assert(m);
    //if( (n+m+1) <= int(sizeof(ULL)))   // if possible do a Built-in calculation
    //  return x.to_ul()*y.to_ul();

    if(y.len() > x.len())
        return y*x;


    mjr::Tap z(n+m, true);
    //    z.resize;
    unsigned i, j, carryout = 0;
    for (i = 0; i < n; i++) {
        unsigned carry = 0;
        for (j = 0; j < m; j++) {
            carry += x[i]*y[j] + z[i+j];
            z[i+j] = carry%myBASE;
            carry /= myBASE;
        }
        for ( ; j < n + m - i; j++) {
            carry += z[i+j];
            z[i+j] = carry%myBASE;
            carry /= myBASE;
        }
        carryout |= carry;
    }
    if(carryout)
        z[z.len()] = 1;             // add the carry that spilled out
    z.normalize();
    return z;
}



/**
 *  @brief Compute the sum of bytes in 'x' and bytes in 'y'
 *  @note Algorithm: Given two Tap x[0, n) and y[0, m)
 *  [1] ø set j ← 0 , k ← 0
 *  [2] ø Set wj ← (x[j] + y[j] + k)
 *
 *
 *  @param const Tap& x:
 *  @param const Tap& y:
 *  @return int: borrow
*/
mjr::Tap operator+ (const mjr::Tap& x, const mjr::Tap& y)
{
    using mjr::Tap;
    if(y.len() > x.len())
        return y+x;

    unsigned n = x.len();
    if(n+1 <= sizeof(ULL))              // if possible do a normal calculation
        return Tap(x.to_ul()+y.to_ul());



    Tap zy = y;                        /// @test Make zy a copy of y
    zy.resize(n);

    int carry = 0;
    for (unsigned i = 0; i < n; ++i) {
        carry = (x[i] + zy[i] + carry);
        zy[i] = carry % myBASE;
        carry /= myBASE;
    }
    if(carry)
        zy.resize(n+1, carry);
    return zy;
}


/**
 *  @brief Operator '-' subtraction  → Subtract y from x
 *  @param const Tap& x:
 *  @param const Tap& y:
 *  @return Tap: result of operation x-y
*/
mjr::Tap operator- (const mjr::Tap& x, const mjr::Tap& y)
{
    using mjr::Tap;
    if(y.len() <= 1 and y == 0) return x;

    unsigned n = x.len();
    //    if(n <= sizeof(ULL))          // if possible do a normal calculation
    //        return x.to_ul()-y.to_ul();

    Tap zy = y;                        /// @test Make zy a copy of y
    zy.resize(n);

    int borrow = 0;
    for(unsigned i=0; i < n; ++i){
        int d = (x[i] + myBASE) - borrow - zy[i];
        zy[i] = d%myBASE;
        borrow = 1 - d/myBASE;
    }
    if(borrow){
        std::cerr << "ATTENTION: (substraction) : y > x...\n";
        return mjr::Tap("0");
    }
    return zy;
}


/**
 *  @brief Operator '/' Division  → computes x / x
 *  @param const Tap& x:
 *  @param const Tap& y:
 *  @return Tap: result of operation x/y
*/
mjr::Tap operator/ (mjr::Tap x, mjr::Tap y)
{
    using mjr::Tap;


    Tap u = x;
    Tap v = y;
    size_t n = v.size();
    size_t m = (u.size()-1) - (n-1);

    Tap Q(m+1, true);                          // will hold quotient
    //Tap R(n);                                // TODO will hold remainder
    //Tap resu(n+1, true);                     // will hold result of addition in [D4]
    unsigned B =  mjr::myBASE;


    // [D1] Normalize ========================
    unsigned d = (B-1) / v[n-1];
    if(d == 1)
        u.push_back(0);
    else{
        d = 2;
        while(v[n-1] < B/2){
            //int carr = product(u.size(), &u[0], &u[0], d);
            int carr = mjr::Util::product(u.size(), &u[0], &u[0], d, mjr::myBASE);
            if(carr > 0) u.push_back(carr);
            mjr::Util::product(v.size(), &v[0], &v[0], d, mjr::myBASE);
        }
    }

    // [D2] Initialize j ====================
    for(int j=m; j>=0; --j){
        // [D3] Compute qprime ==============
        unsigned long q2 = (u[j+n]*B + u[j+n-1]) / v[n-1];
        unsigned long r2 = (u[j+n]*B + u[j+n-1]) % v[n-1];

        if(q2 == B)
            --q2;
        while(r2 < B and ( q2*v[n-2] > B*r2+u[n-2] )){
            --q2;
            r2 += v[n-1];
        }

        // [D4] Multiply and substract =====
        Tap resu(n+1, true);
        resu[n] = mjr::Util::product(n, &resu[0], &v[0], q2, mjr::myBASE);
        int bo = 0;                 // borrow
        {// subtract u[j+n...j] - resu[n-1..0]
            unsigned iu = j;
            unsigned ir = 0;
            while(iu <= j+n){
                int d = (u[iu] + B) - bo - resu[ir];
                u[iu] = d%B;
                bo = 1 - d/B;
                ++ir; ++iu;
            }
        }

        // [D5] test remainder =============
        Q[j] = q2;

        // [D6] add back ===================
        if(bo != 0){                            /// @newcode
            Q[j] = Q[j]-1;
            {//add v[0...n-1] to u[j...j+n]
                unsigned iu = j;
                unsigned ir = 0;
                int ka = 0;
                while(iu < j+n){
                    u[iu] = (u[iu]+v[ir]+ka) % B;
                    ka = (u[iu]+v[ir]+ka) / B;
                    ++ir; ++iu;
                }
            }
        }


    }// [D7] rebegin loop ==================
    return Q;
}




//TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
/**
 *  @brief Compute the sum of bytes in 'x' and bytes in 'y'
 *  @note Algorithm: Given two Tap x[0, n) and y[0, m)
 *  [1] ø set j ← 0 , k ← 0
 *  [2] ø Set wj ← (x[j] + y[j] + k)
 *
 *
 *  @param const Tap& x:
 *  @param const Tap& y:
 *  @return int: borrow
*/
mjr::Tap addv2(const mjr::Tap& x, const mjr::Tap& y)
{
    using mjr::Tap;
    if(y.len() > x.len())
        return addv2(y,x);

    unsigned n = x.len();
    if(n+1 <= sizeof(ULL))                  // if possible try a normal calculation
        return Tap(x.to_ul()+y.to_ul());

    if(n%4 == 0){

    }
    else{
        Tap zy = y;                        /// @test Make zy a copy of y
        zy.resize(n);

        int carry = 0;
        for (unsigned i = 0; i < n; ++i) {
            carry = (x[i] + zy[i] + carry);
            zy[i] = carry % myBASE;
            carry /= myBASE;
        }

        if(carry)
            zy.resize(n+1, carry);
    }
    cerr << " bad times in Tap::addv2\n";
    return "0";
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// → [COMPARATION OPERATORS]
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/**
 *  @brief Check if a > b
 *  @param const Tap& a:
 *  @param const Tap& b:
 *  @return bool: true if a > b
*/
bool operator> (const mjr::Tap& a, const mjr::Tap& b){
    int a_sz = a.len(); int b_sz = b.len();
    if(a_sz > b_sz) return true;
    if(a_sz < b_sz) return false;
    while(--a_sz >= 0){     // in case both have the same size
        //Byte at = a[i]; Byte bt = b[i];   //debug
        if(a[a_sz] > b[a_sz]) return true;
        if(a[a_sz] < b[a_sz]) return false;
    }
    return false;
}


/**
 *  @brief Check if a < b
 *  @param const Tap& a:
 *  @param const Tap& b:
 *  @return bool: true if a < b
*/
bool operator< (const mjr::Tap& a, const mjr::Tap& b){
    int a_sz = a.len(); int b_sz = b.len();
    if(a_sz < b_sz) return true;
    if(a_sz > b_sz) return false;
    while(--a_sz >= 0){     // in case both have the same size
        if(a[a_sz] < b[a_sz]) return true;
        if(a[a_sz] > b[a_sz]) return false;
    }
    return false;
}


/**
 *  @brief Check if a == b
 *  @param const Tap& a:
 *  @param const Tap& b:
 *  @return bool: true if a == b
*/
bool operator==(const mjr::Tap& a, const mjr::Tap& b){
    if(a.len() != b.len()) return false;
    mjr::cpByte pa = a.to_rarr();
    mjr::cpByte pb = b.to_rarr();
    int i=a.len();
    for( ; i>0 and (*pa-- == *pb--); --i) // in case both have the same size
    {}
    return (i==0);
}


/**
 *  @brief Check if a != b
 *  @param const Tap& a:
 *  @param const Tap& b:
 *  @return bool: true if a != b, false otherwise
*/
bool operator!=(const mjr::Tap& a, const mjr::Tap& b){
    return !(a==b);
}


/// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
bool is_equal(const mjr::Tap& a, const mjr::Tap& b)            /// @test @compat
{
    int a_sz = a.len(); int b_sz = b.len();
    if(a_sz != b_sz) return false;
    while(--a_sz >= 0){     // in case both have the same size
        if(a[a_sz] != b[a_sz]) return false;
    }
    return true;
}


std::ostream& operator<<(std::ostream& os, const mjr::Tap& tap_number)
{
    os << tap_number.to_s();
    return os;
}






#endif // TAP_H
