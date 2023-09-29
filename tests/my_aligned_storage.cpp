#include <string>
#include "catch_amalgamated.hpp"
#include "my_aligned_storage.hpp"


TEST_CASE("Checking alignment")
{
	SECTION("Example with int type")
	{
	    my::aligned_storage<int> as (4);
		//my::aligned_storage<int, 4> as;
		REQUIRE((uintptr_t)as[0] % alignof(int) == 0);
		REQUIRE((uintptr_t)as[1] % alignof(int) == 0);
		REQUIRE((uintptr_t)as[2] % alignof(int) == 0);
		REQUIRE((uintptr_t)as[3] % alignof(int) == 0);
		REQUIRE((uint8_t*)as[1] - (uint8_t*)as[0] == sizeof(int));
		REQUIRE((uint8_t*)as[2] - (uint8_t*)as[1] == sizeof(int));
		REQUIRE((uint8_t*)as[3] - (uint8_t*)as[2] == sizeof(int));
	}

	SECTION("Example with one element")
	{
		my::aligned_storage<int> as (1);
		//my::aligned_storage<int, 1> as;
		REQUIRE((uintptr_t)as[0] % alignof(int) == 0);
	}

	SECTION("Example with string type")
	{
		my::aligned_storage<std::string> as (7);
		//my::aligned_storage<std::string, 7> as;
		REQUIRE((uintptr_t)as[0] % alignof(std::string) == 0);
		REQUIRE((uintptr_t)as[1] % alignof(std::string) == 0);
		REQUIRE((uintptr_t)as[2] % alignof(std::string) == 0);
		REQUIRE((uintptr_t)as[3] % alignof(std::string) == 0);
		REQUIRE((uintptr_t)as[4] % alignof(std::string) == 0);
		REQUIRE((uintptr_t)as[5] % alignof(std::string) == 0);
		REQUIRE((uintptr_t)as[6] % alignof(std::string) == 0);
		REQUIRE((uint8_t*)as[1] - (uint8_t*)as[0] == sizeof(std::string));
		REQUIRE((uint8_t*)as[4] - (uint8_t*)as[2] == 2*sizeof(std::string));
		REQUIRE((uint8_t*)as[6] - (uint8_t*)as[5] == sizeof(std::string));
	}
}
