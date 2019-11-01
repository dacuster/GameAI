/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <queue>
#include <map>


// Dean Library
#include "Trackable.h"


// Game Library
#include "PriorityQueueHack.h"


// Push element to the queue. True if value was updated or element is new. False if value is the same or higher.
bool PriorityQueueHack::push(nodeDistancePair* element)
{
	// Use map to find if the element exists in the queue already.
	std::map<Node*, nodeDistancePair*>::iterator findElement = mMap.find(element->first);
	if (findElement != mMap.end())
	{
		// Cost to go to this node is cheaper.
		if (element->second < findElement->second->second)
		{
			// Update cost.
			findElement->second->second = element->second;

			return true;
		}

		// Cost is higher or the same.
		return false;
	}

	// Push the element into the queue.
	mQueue.push(element);

	// Add insert the Node into the map for quick reference.
	mMap.insert(std::make_pair(element->first, element));

	return true;
}

// Remove the first element in the queue.
void PriorityQueueHack::pop()
{
	if (!mQueue.empty())
	{
		mMap.erase(mQueue.top()->first);
		mQueue.pop();
	}

	return;
}

// Get the first element in the queue.
nodeDistancePair* PriorityQueueHack::top()
{
	if (!mQueue.empty())
	{
		return mQueue.top();
	}

	return nullptr;
}

// Get the first element in the queue and remove it.
nodeDistancePair* PriorityQueueHack::popTop()
{
	nodeDistancePair* topElement = top();

	pop();

	return topElement;
}

// Clear the queue.
void PriorityQueueHack::clear()
{
	while (!mQueue.empty())
	{
		delete popTop();
	}

	mMap.clear();

	return;
}

bool CompareDistance::operator()(const nodeDistancePair* left, const nodeDistancePair* right)
{
	return (*left > *right);
}