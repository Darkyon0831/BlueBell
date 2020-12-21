#ifndef __BB_LINKEDLIST_H__
#define __BB_LINKEDLIST_H__

namespace BlueBell
{
	template<typename HStruct>
	class LinkedList
	{
	public:

		LinkedList() = default;
		~LinkedList() = default; 

		struct Node
		{
			HStruct header;
			Node* pNext;
		};

		/**
		* Sets the head node of the linked list
		* 
		* @param pNode: The new head node
		**/
		void SetHead(Node* pNode) { m_headNode = pNode; }

		/**
		* Gets the head node from this linked list
		**/
		Node* GetHead() { return m_headNode; }

		/**
		* Adds an new node to the linked list
		*
		* @param preNode: The previous node from currentNode. if null, headerNode is assumed
		* @param currentNode: The node to add to the linked list
		**/
		void Push(Node* preNode, Node* currentNode);

		/**
		* Removes an node from the linked list
		*
		* @param preNode The previous node from currentNode. if null, headerNode is assumed
		* @param currentNode The node to remove from the linked list
		**/
		void Pop(Node* preNode, Node* currentNode); 

	private:

		Node* m_headNode;
	};

#endif // !__BB_LINKEDLIST_H__

	template<typename HStruct>
	inline void LinkedList<HStruct>::Push(Node* preNode, Node* currentNode)
	{
		if (preNode == nullptr)
		{
			Node* headNext = m_headNode;
			currentNode->pNext = headNext;
			m_headNode = currentNode;
		}
		else
		{
			Node* preNext = preNode->pNext;
			preNode->pNext = currentNode;
			currentNode->pNext = preNext;
		}
	}

	template<typename HStruct>
	inline void LinkedList<HStruct>::Pop(Node* preNode, Node* currentNode)
	{
		if (preNode == nullptr)
			m_headNode = currentNode->pNext;
		else
			preNode->pNext = currentNode->pNext;
			

	}
}
