/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // graded in MP3.1

  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  //  graded in MP3.1
  return List<T>::ListIterator(nullptr);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  _destroy();
  head_=nullptr;
  tail_=nullptr;
  length_=0;
  /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if(head_==nullptr)
  return;
  ListNode* temp=head_;
  ListNode* prev=temp;
  while(temp!=nullptr){
    temp=temp->next;
    delete prev;
    prev=temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if(empty()==1){
    ListNode* new_head=new ListNode(ndata);
    head_=new_head;
    tail_=new_head;
    new_head->next=nullptr;
    new_head->prev=nullptr;
  }
  else{
    ListNode* new_head=new ListNode(ndata);
    ListNode* old_head=head_;
    head_=new_head;
    new_head->next=old_head;
    new_head->prev=nullptr;
    old_head->prev=new_head;
  }
  length_+=1;
  return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(empty()==1){
    ListNode* new_head=new ListNode(ndata);
    head_=new_head;
    tail_=new_head;
    new_head->next=nullptr;
    new_head->prev=nullptr;
  }
  else{
    ListNode* new_tail=new ListNode(ndata);
    ListNode* old_tail=tail_;
    tail_=new_tail;
    new_tail->prev=old_tail;
    new_tail->next=nullptr;
    old_tail->next=new_tail;
  }
  length_+=1;
  return;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if(startPoint==endPoint)
  return;
  ListNode* temp=startPoint;
  ListNode* pre=temp;

  temp=startPoint->next;                          //first node
  startPoint->next=endPoint->next;
  ListNode* reserve=startPoint->prev;
  startPoint->prev=temp;
  pre=temp;
  while(pre!=endPoint){
    temp=temp->next;
    pre->next=pre->prev;
    pre->prev=temp;
    pre=temp;
 }
 temp=temp->next;                               //last node
 pre->next=pre->prev;
 pre->prev=reserve;

  ListNode* exchange_sd=startPoint;            //change startpoint and end point
  startPoint=endPoint;
  endPoint=exchange_sd;
  return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
 int already_reverse=0;
 int list_length=length_;
 int blocknum=n;
 ListNode* end=head_;
 ListNode* start=end;
 ListNode* hold=start;

 while(blocknum+already_reverse<list_length){
   for(int i=0;i<blocknum;i++){
      end=end->next;
   }
   hold=end;                                           //store the current block+1 node
   if(start==head_)
   reverse(head_,end->prev);
   else
   reverse(start->prev->next,end->prev);
   start=hold;
   end=start;
   already_reverse+=blocknum;
 }
                                                        //deal with the last block; absolute case
   reverse(start->prev->next,tail_);
return;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if((length_==0)||(length_==1))
  return;
  else{
  ListNode* temp=head_;
  ListNode* hold=head_;
  while(temp->next!=tail_){
    temp=temp->next;
    hold=temp->next;
    temp->prev->next=temp->next;
    temp->next->prev=temp->prev;
    temp->next=nullptr;
    temp->prev=tail_;
    tail_->next=temp;
    tail_=temp;
    temp=hold;
  }
}
  return;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
ListNode* new_head=start;
ListNode* pre_tail=start;
  for(int i=0;i<splitPoint;i++){
    new_head=new_head->next;
  }
  pre_tail=new_head->prev;
  pre_tail->next=nullptr;
  new_head->prev=nullptr;
  return new_head;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* track_first=first;
  ListNode* track_second=second;
  ListNode* new_head=first;
  ListNode* first_tail=first;
  ListNode* second_tail=second;
  if(first==nullptr&&second==nullptr)
  return nullptr;
  if(first==nullptr&&second!=nullptr)
  return second;
  if(first!=nullptr&&second==nullptr)
  return first;

  while(first_tail->next!=nullptr)
  first_tail=first_tail->next;
  while(second_tail->next!=nullptr)
  second_tail=second_tail->next;

  if(track_first->data<track_second->data){                        //decide head
    track_first=track_first->next;
  }
  else{
    new_head=second;
    track_second=track_second->next;
  }
  ListNode* keeptrack=new_head;
  while(track_first!=nullptr&&track_second!=nullptr){
    if(track_first->data<track_second->data){
      track_first->prev=keeptrack;
      keeptrack->next=track_first;
      keeptrack=track_first;
      track_first=track_first->next;
    }
    else{
      track_second->prev=keeptrack;
      keeptrack->next=track_second;
      keeptrack=track_second;
      track_second=track_second->next;
    }
  }
if(track_first==nullptr){                                       //end case when one list has gone to null
first_tail->next=track_second;
track_second->prev=first_tail;
}
else if(track_second==nullptr){
second_tail->next=track_first;
track_first->prev=second_tail;
}
return new_head;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  //base case
  if(length_==1){
    std::cout << "test 5" << '\n';
  return start;
}
  //recursive case
  else{
    List secondlist=split(chainLength/2);
    mergesort(start,length_);
    secondlist.mergesort(secondlist.head_,secondlist.length_);
    mergeWith(secondlist);
    return head_;
  }

}
