// jjobanputra@ucdavis.edu Jobanputra, Janak
// ckashyap@ucdavis.edu Kashyap, Chirag

#include <iostream>
#include <climits>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
  if(pos == internalSize)
    return ptr;

  BTreeNode *last = children[count - 1];

  for(int i = count - 2; i >= pos; i--)
  {
    children[i + 1] = children[i];
    keys[i + 1] = keys[i];
  } // shift things to right to make room for ptr, i can be -1!

  children[pos] = ptr;  // i will end up being the position that it is inserted
  keys[pos] = ptr->getMinimum();
  ptr->setParent(this);
  return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
  ((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
  {
    children[i] = children[i + 1];
    keys[i] = keys[i + 1];
  }

  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMinimum(this);
} // InternalNode::ToLeft()


void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
  ((InternalNode*) rightSibling)->insert(last);
  if(ptr == children[0] && parent)
    parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
  int i;

  for(i = count - 1; i >= pos; i--)
  {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
  } // shift to the right to make room at pos

  children[pos] = ptr;
  keys[pos] = ptr->getMinimum();
  count++;
  ptr->setParent(this);

  if(pos == 0 && parent)
    parent->resetMinimum(this);
} // InternalNode::addToThis()



int InternalNode::getMaximum() const
{
  if(count > 0) // should always be the case
    return children[count - 1]->getMaximum();
  else
    return INT_MAX;
}  // getMaximum();


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{  // count must always be >= 2 for an internal node
  //cout << "INTERNAL INSERT 1\n";
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *last, *ptr = children[pos]->insert(value);
  if(!ptr)  // child had room.
    return NULL;

  if(count < internalSize)
  {
    addToThis(ptr, pos + 1);
    return NULL;
  } // if room for value

  last = addPtr(ptr, pos + 1);

  if(leftSibling && leftSibling->getCount() < internalSize)
  {
    addToLeft(last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < internalSize)
    {
      addToRight(ptr, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(last);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  //cout << "INTERNAL INSERT 2\n";
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  count = 2;
  children[0]->setLeftSibling(NULL);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[1]->setRightSibling(NULL);
  oldRoot->setParent(this);
  node2->setParent(this);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
  //cout << "INTERNAL INSERT 3\n";
  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)


void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


BTreeNode* InternalNode::remove(int value)
{
  //cout << "INTERNAL REMOVE\n";
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *ptr = children[pos]->remove(value);


  int i=0;//, borrow=0;
  BTreeNode* tempPtr=0;
  //int temp = 0; 
  // ENTER HERE IF LeafRemove RETURNED
  // ptr, SO DELETE LEAF RETURNED
  if(ptr && children[pos]==ptr)
  {
    for(i=pos; i<count ; i++)
    {
      tempPtr = children[i];
      children[i]=children[i+1];
      children[i+1]=tempPtr;
    }
    //update keys
    count--;
  }

  // CHECK BORROW AND MERGE CONDITIONS
    // ENTER IF PTR EXISTS AND COUNT UNDER SIZE
  if(ptr && count < (internalSize+1)/2)
  {
    if(leftSibling && leftSibling->getCount() > (internalSize+1)/2)
    {
      // BORROW LEFT
      //cout << "            BORROW LEFT\n";
      
    }

    else if(rightSibling && rightSibling->getCount() > (internalSize+1)/2)
    {
      /*
      // BORROW RIGHT
      cout << "            BORROW RIGHT\n";
      //take left sibling's max child
      keys[count-1]=((InternalNode*)rightSibling)->keys[0];
      tempPtr = ((InternalNode*)rightSibling)->children[count-1];
      insert(tempPtr);
      rightSibling->remove(tempPtr);

      //take left sibling's max key
      borrow = ((InternalNode*)rightSibling)->keys[count-1];
      insert(borrow);
      rightSibling->remove(borrow);*/
      //delete those two from left sibling
    }

    else if(leftSibling)
    {
      /*
      // MERGE LEFT
      cout << "            MERGE LEFT\n";
      // copy keys values
      for(i=0; i<count; i++)
      {
        temp = keys[i];
        remove(temp);
        leftSibling->insert(temp);
      }
      // copy over children ptrs
      for(i=0; i<count; i++)
      {
        tempPtr = children[i];
        delete children[i];
        ((InternalNode*)leftSibling)->insert(tempPtr);
      }
      // set siblings
      leftSibling->setRightSibling(rightSibling);
      if(rightSibling)
        rightSibling->setLeftSibling(leftSibling);
      return this;*/
    }

    else if(rightSibling)
    {
      /*
      // MERGE RIGHT
      cout << "            MERGE RIGHT\n";
      // copy keys values
      for(i=0; i<count; i++)
      {
        temp = keys[i];
        remove(temp);
        rightSibling->insert(temp);
      }
      // copy over children ptrs
      for(i=0; i<count; i++)
      {
        tempPtr = children[i];
        delete children[i];
        ((InternalNode*)rightSibling)->insert(tempPtr);
      }
      // set siblings
      rightSibling->setLeftSibling(leftSibling);
      if(leftSibling)
        leftSibling->setRightSibling(rightSibling);
      return this;*/
    }
  } // end borrow merge internal

  // NOW UPDATE ALL KEYS OF ALL INTERNAL NODES
  for(i=0; i<count; i++)
    keys[i] = children[i]->getMinimum();

  return NULL; // filler for stub
} // InternalNode::remove(int value)

BTreeNode* InternalNode::removeChild(int pos)
{


  return this;
}


void InternalNode::resetMinimum(const BTreeNode* child)
{
  for(int i = 0; i < count; i++)
    if(children[i] == child)
    {
      keys[i] = children[i]->getMinimum();
      if(i == 0 && parent)
        parent->resetMinimum(this);
      break;
    }
} // InternalNode::resetMinimum()


InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
    parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
  {
    newptr->children[newptr->count] = children[i];
    newptr->keys[newptr->count++] = keys[i];
    children[i]->setParent(newptr);
  }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
} // split()

