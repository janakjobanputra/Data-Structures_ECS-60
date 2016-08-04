// Janak Jobanputra             Chirag Kashyap
// 998189389                    IDIDIDIDIDIDID
// jjobanputra@ucdavis.edu      ckashyap@ucdavis.edu

#ifndef _LONGINT_DEF_
#define _LONGINT_DEF_

#include <stdio.h>
#include <iostream>
#include "dsexceptions.h"

using namespace std;


class LongInt
{
public:    
    // + overload
    friend LongInt & operator+( LongInt& list2,  LongInt & list1);
    // << overload
    friend ostream & operator<<(ostream & output,  LongInt & sol);
    // >> overload
    friend istream & operator>>(istream & input,  LongInt & num);

    // constructor, destructor
    LongInt( );
    ~LongInt( );
    
    // other functions
    bool isEmpty( );
    int & top( );
    void makeEmpty( );
    void pop( );
    void push(int x);
    int topAndPop( );
    
private:
    // ListNode Definition
    struct ListNode
    {
        int   element;
        ListNode *next;
        ListNode( const int & theElement, ListNode * n = NULL )
        : element( theElement ), next( n ) { }
    };
    ListNode *topOfStack;
    
}; // end class definition

#endif
