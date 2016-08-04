// Janak Jobanputra             Chirag Kashyap
// 998189389                    IDIDIDIDIDIDID
// jjobanputra@ucdavis.edu      ckashyap@ucdavis.edu


#include "LongInt.h"
#include "dsexceptions.h"
#include <iostream>
#include <cctype>


//overloads the + operator
LongInt & operator+( LongInt & list1,  LongInt & list2)
{
    LongInt *temp;
    int num1 = 0, num2 = 0, num3 = 0, carry = 0, temp2 = 0;

    while(!list1.isEmpty() || !list2.isEmpty())
    {
        num3 = 0;
        if(list2.isEmpty())
            num2 = 0;
        else
            num2 = list2.topAndPop();
        if(list1.isEmpty())
            num1 = 0;
        else
            num1 = list1.topAndPop();
        if(carry)
        {
            num3++;
            carry = 0;
        } //end if carry exists
        num3 += num1 + num2;
        if (num3 > 9)
        {
            num3 -= 10;
            carry = 1;
        } // end creating carry
        temp->push(num3);
    }
    return *temp;
}// end + overload


//overloads the << operator
ostream & operator<<(ostream & output, LongInt & sol)
{
    int num;
    while(!sol.isEmpty())
        cout << sol.topAndPop(); //put into solution stacklist
    cout << " ";
} // ends << overload


// overloads the >> operator
istream & operator>>(istream & input, LongInt & num)
{
    int num1;
    char c;
    c = cin.get();
    while(isdigit(c))
    {
        num1 = c - '0';
        num.push(num1);
        c = cin.get();
    }
}// end >> overload


// constructor
LongInt::LongInt( )
{
    topOfStack = NULL;
} // end constructor


// destructor
LongInt::~LongInt( )
{
    makeEmpty( );
}// end destructor


// returns true if stack empty, fase if not empty
bool LongInt::isEmpty( )
{
    return topOfStack == NULL;
}// end isEmpty


// pops top element
void LongInt::pop( )
{
    if( isEmpty( ) )
        throw new Underflow( );
    
    ListNode *oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;
}// end pop


// returns top element
int & LongInt::top( ) 
{
    if( isEmpty( ) )
        throw Underflow( );
    return topOfStack->element;
} // end top

// returns and pops top element
int LongInt::topAndPop( )
{
    int topItem = top( );
    pop( );
    return topItem;
} // end topAndPop

// makes the stack empty
void LongInt::makeEmpty( )
{
    while( !isEmpty( ) )
        pop( );
}// makeEmpty


// pushes in an integer
void LongInt::push(int x )
{
    topOfStack = new ListNode( x, topOfStack );
}// end push
