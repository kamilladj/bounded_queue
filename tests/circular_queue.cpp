#include "circular_queue.hpp"
#include "catch_amalgamated.hpp"


TEST_CASE("Checking circular queue")
{
	SECTION("FRONT<=REAR")
	{
		circular_queue<size_t> q (5);
		REQUIRE(q.empty());
		REQUIRE(q.size() == 0);
		for (size_t i = 0; i < 4; i++)
		{
			q.push(i);
		}
		q.push(4);
		REQUIRE(q.full());
		REQUIRE(q.size() == q.capacity());
		REQUIRE(!q.push(5));

		size_t arr[5];
		for (size_t i = 0; i < 5; i++)
		{
			arr[i] = q.pop();
			REQUIRE(arr[i] == i);
		}
		REQUIRE(q.empty());
		REQUIRE_THROWS_AS(q.pop(), std::runtime_error);
	}

	SECTION("FRONT>REAR")
	{
		circular_queue<size_t> q(5);
		for (size_t i = 0; i < 5; i++)
		{
			q.push(i);
		}
		REQUIRE(q.full());
		REQUIRE(q.size() == 5);
		q.pop();
		q.pop();
		q.pop();
		REQUIRE(q.size() == 2);
		q.push(5);
		q.push(0);
		REQUIRE(q.size() == 4);
		q.push(1);
		REQUIRE(q.size() == 5);
		REQUIRE(q.full());
		REQUIRE(!q.push(6));
	}
}