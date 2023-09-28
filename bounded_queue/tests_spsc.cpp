//#define _CRT_SECURE_NO_WARNINGS
//
//#include "bounded_queue_spsc.hpp"
//#include "catch_amalgamated.hpp"
//#include <thread>
//#include <vector>
//#include <exception>
//#include <iostream>
//#include <time.h>
//
//
//void pthread_start(int n, bounded_queue_spsc<int>& q)
//{
//	try
//	{
//		for (int i = 1; i <= n;)
//		{
//			bool res = false;
//			for (int j = 1; j <= 3; j++)
//			{
//				if (q.push(i))
//				{
//					res = true;
//					i++;
//					break;
//				}
//			}
//
//			if (!res)
//				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
//		}
//	}
//	catch (const std::exception& e)
//	{
//		std::cout << e.what();
//	}
//	catch (...)
//	{
//		std::cout << "Exception thrown!!!" << std::endl;
//	}
//}
//
//
//void cthread_start(int n, bounded_queue_spsc<int>& q, std::vector<int>& vec)
//{
//	try
//	{
//		while (vec.size() != n)
//		{
//			bool res = false;
//			for (int i = 1; i <= 3; i++)
//			{
//				std::optional<int> temp = q.pop();
//
//				if (temp.has_value())
//				{
//					vec.push_back(temp.value());
//					res = true;
//					break;
//				}
//			}
//
//			if (!res)
//				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
//		}
//	}
//	catch (const std::exception& e)
//	{
//		std::cout << e.what();
//	}
//	catch (...)
//	{
//		std::cout << "Exception thrown!!!" << std::endl;
//	}
//}
//
//
//TEST_CASE("BOUNDED SPSC QUEUE behaviour", "[threads]")
//{
//	SECTION("Single producer - single consumer")
//	{
//		const int N = 2000000;
//		bounded_queue_spsc<int> q(100);
//		std::vector<int> vec;
//
//		std::thread producer(pthread_start, N, std::ref(q));
//		std::thread consumer(cthread_start, N, std::ref(q), std::ref(vec));
//
//		producer.join();
//		consumer.join();
//
//		for (int i = 1; i <= N; i++)
//		{
//			REQUIRE(vec[i - 1] == i);
//		}
//	}
//}