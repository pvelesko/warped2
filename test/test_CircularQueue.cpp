#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"

#include <memory>
#include <utility>

#include "CircularQueue.hpp"
#include "Event.hpp"
#include "mocks.hpp"

TEST_CASE("Circular Queue operations") {

    warped::CircularQueue q(1);
    std::shared_ptr<warped::Event> e, e_temp;
    REQUIRE(q.empty());

    SECTION("Insert, read and erase event on a Circular Queue") {

        // Check for single entry
        q.insert(std::shared_ptr<warped::Event>(new test_Event {"r1", 10}));
        e = q.read_front();
        REQUIRE(e != nullptr);
        CHECK(e->receiverName() == "r1");
        CHECK(e->timestamp() == 10);
        q.erase(e);
        REQUIRE(q.empty());

        // Check for priority ordering
        q.insert(std::shared_ptr<warped::Event>(new test_Event {"r1", 10}));
        q.insert(std::shared_ptr<warped::Event>(new test_Event {"r2", 10}));
        q.insert(std::shared_ptr<warped::Event>(new test_Event {"r1", 9}));

        e = q.read_front();
        REQUIRE(e != nullptr);
        CHECK(e->receiverName() == "r1");
        CHECK(e->timestamp() == 9);
        REQUIRE(q.size() == 3);

        REQUIRE(e == q.pop_front());

        e = q.read_front();
        REQUIRE(e != nullptr);
        CHECK(e->receiverName() == "r1");
        CHECK(e->timestamp() == 10);
        REQUIRE(q.size() == 2);

        REQUIRE(e == q.pop_front());

        e = q.read_front();
        REQUIRE(e != nullptr);
        CHECK(e->receiverName() == "r2");
        CHECK(e->timestamp() == 10);
        REQUIRE(q.size() == 1);

        q.insert(std::shared_ptr<warped::Event>(new test_Event {"r1", 9}));

        q.erase(e);
        REQUIRE(q.size() == 1);

        e == q.read_front();
        REQUIRE(e != nullptr);
        //CHECK(e->receiverName() == "r1");
        //CHECK(e->timestamp() == 9);
    }
}
