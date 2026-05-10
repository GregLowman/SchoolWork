#include <gtest/gtest.h>
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"
#include "hash.hpp"
#include <string>
#include <vector>
using namespace std;

class CrawlTest : public ::testing::Test {
protected:
    EnemyGraph* graph1;
    
    void SetUp() override {
        // This runs before each test to instantiate 

            graph1 = new EnemyGraph();
        
    }
    
    void TearDown() override {
        // This runs after each test
        delete graph1;
    }
};


TEST_F(CrawlTest, searchgraphHappyPath) {

        //Given a graph with a vertex
        graph1->addVertex("fong");

        // When we search for that vertex
        Vertex* result = graph1->searchVertex("fong");

        //Then we expect the vertex return to Not equal a nullptr (EXPECT_NE means expect not equal)
        EXPECT_NE(result, nullptr);
        EXPECT_EQ(result->id, "fong");

}

TEST_F(CrawlTest, searchGraphErrorPath) {
    //Given an empty graph

    //When we try to search for a vertex
    //We expect an invalid argument error to be thrown
    EXPECT_THROW(graph1->searchVertex("doesnt exist"), std::invalid_argument);


}
// TODO Add an Edge Case test of the graph here

TEST_F(CrawlTest, edgeCase)
{
    //Given
    Vertex* v1 = graph1->addVertex("room1");
    ASSERT_NE(v1, nullptr);
    EXPECT_TRUE(v1->adjacent.empty());

    //When 
    graph1->addEdge("room1", "doesnt_exist", "Vile Beast");

    //Then
    EXPECT_TRUE(v1->adjacent.empty());
}



//  ********   ******* PRIORITY QUEUE TESTS   ***** ****** *******
//When testing priority Queue you may wish to update line 63 to specify the capacity of the queue in the constructor

class PriorityTest : public ::testing::Test {
protected:

    PriorityQ* priority1;
    
    void SetUp() override {
        // This runs before each test to instantiate 
            priority1 = new PriorityQ(5);
        
    }
    
    void TearDown() override {
        // This runs after each test
        delete priority1;
    }
};


TEST_F(PriorityTest, PriorityQueueInsertHappyPath) {

        // GIVEN: A priority queue with capacity

        ItemInfo item;
        item.characterName = "Great Daniel";
        item.itemName = "Greatsword";
        item.damage = 2000;
        item.comment = "Big sword";

        // WHEN: We insert a valid item 

        priority1->insertElement(item);

        // THEN: The item should be retrievable via peek 

        ItemInfo* top = priority1->peek();
        ASSERT_NE(top, nullptr);
        EXPECT_EQ(top->itemName, "Greatsword");
        EXPECT_EQ(top->damage, 2000);

}

// TO DO add  more tests of your priority queue here

TEST_F(PriorityTest, emptyPeekEdgeCase)
{
    //Given : Empty Priority Queue

    //When 
    ItemInfo* top = priority1->peek();

    //Then
    EXPECT_EQ(top, nullptr);
}

TEST_F(PriorityTest, popEmptyEdgeCase)
{
    //Given: Empty Priority Queue 

    //When
    priority1->pop();

    //Then 
    EXPECT_TRUE(priority1->isEmpty());
    EXPECT_EQ(priority1->peek(), nullptr);
}

