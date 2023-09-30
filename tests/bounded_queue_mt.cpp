#define _CRT_SECURE_NO_WARNINGS

#include "bounded_queue_mt.hpp"
#include "catch_amalgamated.hpp"
#include <thread>
#include <vector>


TEST_CASE("BOUNDED MULTITHREADED QUEUE behaviour", "[threads]")
{
	SECTION("Single producer - single consumer")
	{
		bounded_queue_mt<int> q;
		std::vector<int> vec;
		std::thread t1([&] { for (int i = 1; i <= 5; i++) q.push(i); });
		std::thread t2([&] { while (vec.size() != 5) { vec.push_back(q.pop()); }});
		
		t1.join();
		t2.join();

		for (int i = 1; i <= 5; i++)
		{
			REQUIRE(vec[i - 1] == i);
		}
	}

	SECTION("Two producers - one consumer")
	{
		bounded_queue_mt<int> q;
		std::vector<int> vec;
		std::thread t1([&] {q.push(1); });
		std::thread t2([&] {q.push(2); });
		std::thread t3([&] { while (vec.size() != 2) { vec.push_back(q.pop()); }});
		t1.join();
		t2.join();
		t3.join();
		
		REQUIRE(std::find(vec.begin(), vec.end(), 1) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 2) != vec.end());
	}

	SECTION("One producer - two consumers")
	{
		bounded_queue_mt<int> q;
		std::vector<int> vec;
		std::thread t1([&] { q.push(1); q.push(2); });
		std::thread t2([&] { vec.push_back(q.pop()); });
		std::thread t3([&] { vec.push_back(q.pop()); });
		t1.join();
		t2.join();
		t3.join();

		REQUIRE(vec[0] == 1);
		REQUIRE(vec[1] == 2);
	}

	SECTION("Two producers - two consumers")
	{
		bounded_queue_mt<int> q;
		std::vector<int> vec;
		std::thread t1([&] { q.push(1); });
		std::thread t2([&] { q.push(2); });
		std::thread t3([&] { vec.push_back(q.pop()); });
		std::thread t4([&] { vec.push_back(q.pop()); });
		t1.join();
		t2.join();
		t3.join();
		t4.join();

		REQUIRE(std::find(vec.begin(), vec.end(), 1) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 2) != vec.end());
	}

	SECTION("More elements")
	{
		bounded_queue_mt<int> q(7);
		std::vector<int> vec;
		std::thread t1([&] {q.push(1); });
		std::thread t2([&] {q.push(2); });
		std::thread t3([&] {q.push(3); });
		std::thread t4([&] {q.push(4); });
		std::thread t5([&] {q.push(5); });
		std::thread t6([&] {q.push(6); });
		std::thread t7([&] {q.push(7); });
		std::thread t8([&] { while (vec.size() != 7) { vec.push_back(q.pop()); }});
		
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();

		REQUIRE(std::find(vec.begin(), vec.end(), 1) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 2) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 3) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 4) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 5) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 6) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 7) != vec.end());
		REQUIRE(std::find(vec.begin(), vec.end(), 8) == vec.end());
	}
}