#include <cxxtest/TestSuite.h>

#include "heap_priority_queue.h"

template class HeapPriorityQueue<int>;

class HeapTests : public CxxTest::TestSuite
{
public:
   void testTODO( void )
   {
	   HeapPriorityQueue<int> c;
	   TS_ASSERT(c.isEmpty() == true);
	   c.add(2);
	   TS_ASSERT(c.peek() == 2);
	   TS_ASSERT(c.isEmpty() == false);
	   c.add(3);
	   TS_ASSERT(c.peek() == 3);
	   c.add(1);
	   TS_ASSERT(c.peek() == 3);
	   c.remove();
	   TS_ASSERT(c.peek() == 2);
	   c.remove();
	   TS_ASSERT(c.peek() == 1);
	   c.remove();
	   TS_ASSERT(c.isEmpty() == true);
	   TS_ASSERT_THROWS(c.peek(), std::logic_error);
	   TS_ASSERT_THROWS(c.remove(), std::logic_error);
	   c.add(4);
	   TS_ASSERT(c.peek() == 4);
	   TS_ASSERT(c.isEmpty() == false);
   }  
};
