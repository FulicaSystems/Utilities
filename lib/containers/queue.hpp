#pragma once

namespace Utils
{
	template<typename T>
	class Node
	{
	private:

	public:
		Node() = default;

		/**
		 * Create a node used in the queue.
		 *
		 * @param t
		 */
		Node(const T& t);

		T			data;
		Node<T>*	next = nullptr;
	};

	/**
	 * This Queue class works like a chained list.
	 * Using std::queue or std::deque is recommended.
	 */
	template<typename T>
	class Queue
	{
	private:
		Node<T>*	head = nullptr;
		//queue size, number of elements
		unsigned int		size = 0;

	public:
		/**
		 * The queue is not tribially copyable.
		 */
		~Queue();

		/**
		 * Get the front node's data or specify the node's index.
		 */
		T& frontData(const int iterator = 0);

		/**
		 * Add a node at the end of the queue.
		 */
		void pushBackNode(const T& t);

		/**
		 * Erase front node or specify the index of the node to erase.
		 */
		void popFrontNode(const int iterator = 0);

		/**
		 * Is the queue empty?
		 *
		 * @return
		 */
		bool isQueueEmpty();

		/**
		 * Get the size of the queue.
		 *
		 * @return
		 */
		unsigned int sizeQueue() const;
	};
}

template<typename T>
inline Utils::Node<T>::Node(const T& t)
{
	data = t;
}

template<typename T>
inline Utils::Queue<T>::~Queue()
{
	while (!isQueueEmpty())
		popFrontNode();
}

template<typename T>
inline T& Utils::Queue<T>::frontData(const int iterator)
{
	if (iterator >= size)
		assert(("out of range", 0));

	Node<T>* node = head;

	for (int i = 0; i < iterator; ++i)
	{
		if (node->next)
			node = node->next;
		else
			break;
	}

	return node->data;
}

template<typename T>
void Utils::Queue<T>::pushBackNode(const T& t)
{
	Node<T>* node = new Node<T>(t);

	if (!head)
		head = node;
	else
	{
		Node<T>* temp = head;

		for (;;)
		{
			if (temp->next)
				temp = temp->next;
			else
				break;
		}

		temp->next = node;
	}

	++size;
}

template<typename T>
void Utils::Queue<T>::popFrontNode(const int iterator)
{
	if (isQueueEmpty())
		return;

	Node<T>* node = head;
	Node<T>* prev = nullptr;

	if (node)
	{
		for (int i = 0; i < iterator; ++i)
		{
			if (node->next)
			{
				prev = node;
				node = node->next;
			}
			else
				break;
		}
	}
	else
		return;

	if (prev)
		prev->next = node->next;
	else
		head = node->next;

	delete node;

	--size;
}

template<typename T>
bool Utils::Queue<T>::isQueueEmpty()
{
	return size == 0;
}

template<typename T>
unsigned int Utils::Queue<T>::sizeQueue() const
{
	return size;
}