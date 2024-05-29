#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../CMyList/CMyList.h"

TEST_CASE("Check constructors")
{
	WHEN("Use default constructor")
	{
		CMyList<int> list;
		THEN("List must be empty")
		{
			REQUIRE(list.GetSize() == 0);
		}
	}

	WHEN("Use copy constructor")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		CMyList<int> copyList(list);
		auto it = copyList.begin();
		THEN("Size == 3, every elements must be equality copied list")
		{
			REQUIRE(copyList.GetSize() == 3);
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 3);
			++it;
		}
	}

	WHEN("Use move constructor")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		CMyList<int> moveList(std::move(list));
		auto it = moveList.begin();
		THEN("list must be empty, size moveList == 3, every elements must be equality copied list")
		{
			REQUIRE(list.GetSize() == 0);
			REQUIRE(moveList.GetSize() == 3);
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 3);
			++it;
		}
	}
}

TEST_CASE("Check operators")
{
	WHEN("Use copy =")
	{
		CMyList<int> list1;
		list1.push_back(1);
		list1.push_back(2);
		list1.push_back(3);

		CMyList<int> list2;
		list2 = list1;
		auto it = list2.begin();
		THEN("size list1 == lize list2, elements list1 == elements list2")
		{
			REQUIRE(list1.GetSize() == 3);
			REQUIRE(list1.GetSize() == list2.GetSize());
			REQUIRE(list2.GetSize() == 3);
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 3);
			++it;
		}
	}

	WHEN("Use move =")
	{
		CMyList<int> list1;
		list1.push_back(1);
		list1.push_back(2);
		list1.push_back(3);

		CMyList<int> list2;
		list2 = std::move(list1);
		auto it = list2.begin();
		THEN("size list1 == 0, size list2 == 3, elements list1 == elements list2")
		{
			REQUIRE(list1.GetSize() == 0);
			REQUIRE(list2.GetSize() == 3);
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 3);
			++it;
		}
	}
}

TEST_CASE("Check push_front, push_back")
{
	CMyList<int> list;
	list.push_back(1);
	list.push_front(2);
	list.push_back(3);
	auto it = list.begin();

	REQUIRE(list.GetSize() == 3);
	REQUIRE(*it == 2);
	++it;
	REQUIRE(*it == 1);
	++it;
	REQUIRE(*it == 3);
	++it;
}

TEST_CASE("Check insert")
{
	WHEN("Use copy insert")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		auto it = list.begin();
		++it;
		list.insert(it, 666);

		THEN("666 insert on second position, size list == 3")
		{
			REQUIRE(list.GetSize() == 3);
			auto it = list.begin();
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 666);
			++it;
			REQUIRE(*it == 2);
			++it;
		}
	}

	WHEN("Use move insert")
	{
		int a = 666;
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		auto it = list.begin();
		++it;
		list.insert(it, std::move(a));

		THEN("666 insert on second position, size list == 3")
		{
			REQUIRE(list.GetSize() == 3);
			auto it = list.begin();
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 666);
			++it;
			REQUIRE(*it == 2);
			++it;
		}
	}
}

TEST_CASE("Check erase")
{
	CMyList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	auto it = list.begin();
	++it;
	++it;
	list.erase(it);

	REQUIRE(list.GetSize() == 2);

	it = list.begin();

	REQUIRE(*it == 1);
	++it;
	REQUIRE(*it == 2);
}

TEST_CASE("Check begin() end() rbegin() rend()")
{
	WHEN("Use begin() end()")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.begin();
		THEN("1->2->3")
		{
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 3);
			++it;
			REQUIRE(it == list.end());
		}
	}

	WHEN("Use rbegin() rend()")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.rbegin();
		THEN("3->2->1")
		{
			REQUIRE(*it == 3);
			++it;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 1);
			++it;
			REQUIRE(it == list.rend());
		}
	}
}

TEST_CASE("Use different types list")
{
	WHEN("Use int list")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.begin();
		THEN("1->2->3")
		{
			REQUIRE(*it == 1);
			++it;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 3);
			++it;
			REQUIRE(it == list.end());
		}
	}

	WHEN("Use string list")
	{
		CMyList<std::string> list;
		list.push_back("Hello");
		list.push_back("World");
		list.push_back("!");

		auto it = list.begin();
		THEN("Hello->World->!")
		{
			REQUIRE(*it == "Hello");
			++it;
			REQUIRE(*it == "World");
			++it;
			REQUIRE(*it == "!");
			++it;
			REQUIRE(it == list.end());
		}
	}

	WHEN("Use bool list")
	{
		CMyList<bool> list;
		list.push_back(true);
		list.push_back(false);
		list.push_back(true);

		auto it = list.begin();
		THEN("true->false->true")
		{
			REQUIRE(*it == true);
			++it;
			REQUIRE(*it == false);
			++it;
			REQUIRE(*it == true);
			++it;
			REQUIRE(it == list.end());
		}
	}

	WHEN("Use double list")
	{
		CMyList<double> list;
		list.push_back(1.2);
		list.push_back(1.3);
		list.push_back(1.4);

		auto it = list.begin();
		THEN("1.2->1.3->1.4")
		{
			REQUIRE(*it == 1.2);
			++it;
			REQUIRE(*it == 1.3);
			++it;
			REQUIRE(*it == 1.4);
			++it;
			REQUIRE(it == list.end());
		}
	}
}