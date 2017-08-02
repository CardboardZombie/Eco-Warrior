#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

template<class Datatype> class DListNode;
template<class Datatype> class DLinkedList;
template<class Datatype> class DListIterator;

// -------------------------------------------------------
// Name:        DListNode
// Description: This is the Doubly-linked list node class.
// -------------------------------------------------------
template<class Datatype>
class DListNode
{
public:
	Datatype m_data;
	DListNode<Datatype>* m_next;
	DListNode<Datatype>* m_prev;

	// ----------------------------------------------------------------
	//  Name:           InsertAfter
	//  Description:    This adds a node after the current node.
	//  Arguments:      p_data - The data to store in the new node.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void InsertAfter(Datatype p_data)
	{
		// create the new node.
		DListNode<Datatype>* newNode= new DListNode<Datatype>;
		newNode->m_data = p_data;
		// make the new node point to the next node.
		newNode->m_next = m_next;
		newNode->m_prev = this;

		// make the node before it, point to the new node
		if(m_next != 0)
			m_next->m_prev= newNode;
		
		m_next = newNode;
	}
	// ----------------------------------------------------------------
	//  Name:           InsertBefore
	//  Description:    This adds a node before the current node.
	//  Arguments:      p_data - The data to store in the new node.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void InsertBefore(Datatype p_data)
	{
		//Create new Node
		DListNode<Datatype>* newNode = new DListNode<Datatype>;
		newNode->m_data = p_data;
		//Set up new Node Pointers
		newNode->m_next = this;
		newNode->m_prev = m_prev;
		//if theres a node before it, make it point to new node
		if(m_prev != 0)
			m_prev->m_next = newNode;
		
		m_prev = newNode;
	}
};
// -------------------------------------------------------------
// Name:        DLinkedList
// Description: This is the Doubly-linked list container class.
// -------------------------------------------------------------
template<class Datatype>
class DLinkedList
{
public:
	DListNode<Datatype>* m_head;
	DListNode<Datatype>* m_tail;
	int m_count;

	// -----------------------------------------------------------------------------------------
	//  Name:           DLinkedList
	//  Description:    Constructor, creates a head node, tail node & a count.
	//  Arguments:      m_head: the head node of the list.
	//                  m_tail: the tail node of the list.
	//  Return Value:   None.
	// -----------------------------------------------------------------------------------------
	DLinkedList()
	{
		m_head= 0;
		m_tail= 0;
		m_count= 0;
	}

	// -----------------------------------------------------------------------------------------
	//  Name:           ~DLinkedList
	//  Description:    Destructor, creates a pointer for the head node,
	//					deletes the value in the list and iterates.
	//  Arguments:      m_head: the head node of the list.
	//                  itr:	moves through the list.
	//  Return Value:   None.
	// -----------------------------------------------------------------------------------------
	~DLinkedList()
	{
		// temporary node pointers.
		DListNode<Datatype>* itr= m_head;
		DListNode<Datatype>* next;
		while(itr != 0)
		{
			// save the pointer to the next node.
			next = itr->m_next;
			// delete the current node.
			delete itr;
			// make the next node the current node.
			itr= next;
		}
	}
	// ----------------------------------------------------------------
	//  Name:           Length
	//  Description:    Gets the size of the list
	//  Arguments:      None.
	//  Return Value:   size of the list.
	// ----------------------------------------------------------------
	int Length()
	{
		return m_count;
	}
	// -------------------------------------------------------------------------------------
	//  Name:           Append
	//  Description:    This adds a node to the end of the list, then points to the newNode
	//  Arguments:      p_data - The data to store in the new node.
	//					m_count is increased.
	//  Return Value:   None.
	// -------------------------------------------------------------------------------------
	void Append(Datatype p_data)
	{
		if(m_head == 0)
		{
			// create a new head node.
			m_head= m_tail= new DListNode<Datatype>;
			m_head->m_data= p_data;
			m_head->m_next= 0;
			m_head->m_prev= 0;
		}
		else
		{
			// insert a new node after the tail and reset the tail.
			m_tail->InsertAfter(p_data);
			m_tail= m_tail->m_next;
		}
		m_count++;
	}
	// -----------------------------------------------------------------------------------
	//  Name:           Prepend
	//  Description:    This adds a node before the head node, then points to the newNode
	//  Arguments:      p_data - The data to store in the new node.
	//					m_count is increased.
	//  Return Value:   None.
	// -----------------------------------------------------------------------------------
	void Prepend(Datatype p_data)
	{
		// create the new node.
		DListNode<Datatype>* newNode= new DListNode<Datatype>;
		newNode->m_data= p_data;

		newNode->m_next= m_head;
		// set the head node and the tail node if needed.
		m_head= newNode;
		if(m_tail== 0)
			m_tail= m_head;
		m_count++;
	}
	// ----------------------------------------------------------------------------------------------------------------
	//  Name:           Insert
	//  Description:    Inserts data before the iterator, this works whether the iterator is backwards of forwards
	//					through the list.Inserts at the end of the list if iterator is invalid.
	//  Arguments:      p_iterator: The iterator to insert before
	//                  p_data: the data to insert
	//  Return Value:   None.
	// ----------------------------------------------------------------------------------------------------------------
	void Insert(DListIterator<Datatype>& p_itr, Datatype p_data)
	{
		if(p_itr.m_node != 0)
		{
			// insert the data before the iterator
			p_itr.m_node->InsertBefore(p_data);

			//if the iterator was at the head of the list,
			//reset the head pointer
			if(p_itr.m_node == m_head)
			{
				m_head = m_head->m_prev;
			}
			// increment the count
			m_count++;
		}
		else
		{
			Append(p_data);
		}
	}

	// -------------------------------------------------------------------------------------------------------
	//  Name:           Remove
	//  Description:    Removes the node that the iterator points to, moves iterator forward to the next node.
	//  Arguments:      p_iterator: The iterator to remove
	//					isForward: Tells which direction the iterator was going through the list
	//  Return Value:   None.
	// -------------------------------------------------------------------------------------------------------
	void Remove(DListIterator<Datatype>& p_itr, bool isForward)
	{
		// temporary node pointer.
		DListNode<Datatype>* newNode;

		// if node is invalid, do nothing.
		if(p_itr.m_node == 0)
			return;

		// save the pointer to the node we want to delete.
		newNode = p_itr.m_node;

		// if the node we want to remove is the head or the tail
        // nodes, then move the head or tail to the next or
        // previous node.
		if(newNode == m_head)
		{
			m_head = m_head->m_next;
		}
		else if(newNode == m_tail)
		{
			m_tail = m_tail->m_prev;
		}
		// if moving from head to tail, move the iterator forward 
		// to the next valid node
		if(isForward == true)
		{
			p_itr.Forth();
			
		}
		//else, we are moving from tail to head, so move the iterator
		// to the previous valid node
		else
		{
			p_itr.Back();
		}

		if(newNode->m_prev != 0)
			newNode->m_prev->m_next = newNode->m_next;
		else if(newNode->m_next != 0)
			newNode->m_next->m_prev = newNode->m_prev;
		// delink and delete the node.
		delete newNode;

		// if the head is 0, then set the tail to 0 as well.
		if(m_head == 0)
			m_tail = 0;

		m_count--;


	}
	// -----------------------------------------------------------------------------------
	//  Name:           RemoveHead
	//	Description:	Removes the Head of the List and points to the New Node
	//	Arguments:		None
	//	Return Value:	None.
	// -----------------------------------------------------------------------------------
	void RemoveHead()
	{
		DListNode<Datatype>* newNode = 0;
		if(m_head!= 0)
		{
			// make node point to the next node.
			newNode = m_head->m_next;
			// then delete the head and make the pointer
			// point to node.
			delete m_head;
			m_head= newNode;
			// if the head is null, then you’ve just deleted the only node
			// in the list. set the tail to 0.
			if(m_head== 0)
				m_tail= 0;
			m_count--;
		}
	}

	// -----------------------------------------------------------------------------------------
	//  Name:           RemoveTail
	//  Description:    The tail node is removed - but at a much slower pace than the head node, 
	//	this is because the node has to search through the list to find the node before the tail
	//	node and set it to the new tail node then deleting the tail node
	//  Arguments:      None.
	//  Return Value:   None.
	// -----------------------------------------------------------------------------------------
	void RemoveTail()
	{
		DListNode<Datatype>* newNode = m_head;
		// if the list isn’t empty, then remove a node.
		if(m_head!= 0)
		{
			// if the head is equal to the tail, then
			// the list has 1 node, and you are removing it.
			if(m_head == m_tail)
			{
				// delete the node and set both pointers
				// to 0.
				delete m_head;
				m_head= m_tail= 0;
			}
			else
			{
				// skip ahead until you find the node
				// right before the tail node
				while(newNode->m_next!= m_tail)
					newNode = newNode->m_next;
				// make the tail point to the node before the
				// current tail and delete the old tail.
				m_tail= newNode;
				delete newNode->m_next;
				newNode->m_next= 0;
			}
			m_count--;
		}
	}

	// ------------------------------------------------------------------------------
	//  Name:           GetIterator
	//  Description:    Generates an iterator pointing towards the current head node
	//  Arguments:      None.
	//  Return Value:   <Datatype> Iterator
	// ------------------------------------------------------------------------------
	DListIterator<Datatype> GetIterator()
	{
		return DListIterator<Datatype>(this, m_head);
	}
};
// ----------------------------------------------------------
// Name:        DListIterator
// Description: This is the basic linked list iterator class.
// ----------------------------------------------------------
template<class Datatype>
class DListIterator
{
public:
	// ----------------------------------------------------------------
	//  Name:           m_node
	//  Description:    pointer to the current node
	// ----------------------------------------------------------------
	DListNode<Datatype>* m_node;

	// ----------------------------------------------------------------
	//  Name:           m_list
	//  Description:    pointer to the current list.
	// ----------------------------------------------------------------
	DLinkedList<Datatype>* m_list;

	// -----------------------------------------------------------------------------------------
	//  Name:           DListIterator
	//  Description:    Constructor, creates an iterator that points to the given list and node.
	//  Arguments:      p_list: pointer to the list the iterator belongs to.
	//                  p_node: pointer to the current node.
	//  Return Value:   None.
	// -----------------------------------------------------------------------------------------
	DListIterator(DLinkedList<Datatype>* p_list= 0, DListNode<Datatype>* p_node= 0)
	{
		m_list= p_list;
		m_node= p_node;
	}
	
	// ------------------------------------------------------------------
	//  Name:           Start
	//  Description:    Resets the iterator to the beginning of the list.
	//  Arguments:      None.
	//  Return Value:   None.
	// ------------------------------------------------------------------
	void Start()
	{
		if(m_list!= 0)
			m_node= m_list->m_head;
	}

	// ----------------------------------------------------------------
	//  Name:           End
	//  Description:    Resets the iterator to the end of the list
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void End()
	{
		if(m_list!= 0)
			m_node = m_list->m_tail;
	}

	// ----------------------------------------------------------------
	//  Name:           Forth
	//  Description:    Moves the iterator forward by one position
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Forth()
	{
		if(m_node!= 0)
			m_node= m_node->m_next;
	}

	// ----------------------------------------------------------------
	//  Name:           Back
	//  Description:    Moves the iterator backward by one position.
	//  Arguments:      None.
	//  Return Value:   None.
	// ----------------------------------------------------------------
	void Back()
	{
		if(m_node!= 0)
			m_node = m_node->m_prev;
	}

	// ----------------------------------------------------------------
	//  Name:           Item
	//  Description:    Gets the item that the iterator is pointing to.
	//  Arguments:      None.
	//  Return Value:   Reference to the data in the node.
	// ----------------------------------------------------------------
	Datatype& Item()
	{
		return m_node->m_data;
	}

	// ----------------------------------------------------------------
	//  Name:           Valid
	//  Description:    Determines if the node is valid.
	//  Arguments:      None.
	//  Return Value:   true if valid
	// ----------------------------------------------------------------
	bool Valid()
	{
		return (m_node!= 0);
	}
	// ----------------------------------------------------------------
	//  Name:           operator==
	//  Description:    Determines if two iterators point to the same
	//                  node.
	//  Arguments:      None.
	//  Return Value:   true if they point to the same node.
	// ----------------------------------------------------------------
    bool operator==( DListIterator<Datatype>& p_rhs )
    {
        if( m_node == p_rhs.m_node && m_list == p_rhs.m_list )
        {
            return true;
        }
        return false;
    }
};
#endif