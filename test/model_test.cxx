#include "model.hxx"
#include <catch.hxx>
#include "board.hxx"

////BOARD TEST FUNCTIONS

TEST_CASE("board: init has correct states ")
{
    Board b({5,5},0);
    for(Board::Position pos: b.all_positions())
    {
        Board::pos_states state = b.get_pos_data(pos);
        CHECK_FALSE(state.mine);
        CHECK_FALSE(state.unveiled);
        CHECK_FALSE(state.flagged);
        CHECK(state.num_of_mines ==0);
    }
}

TEST_CASE("board: has correct number of mines ")
{
    Board b({5,4},10);
    CHECK(static_cast<int>(b.get_pos_mines().size())==b.get_num_mines());
}
/*
TEST_CASE("board: int_to_pos")
{
    Board b({3,3},0);
    CHECK(b.compare_pos(b.int_to_pos(0),{0,0}));
    CHECK(b.compare_pos(b.int_to_pos(3),{0,1}));
    CHECK(b.compare_pos(b.int_to_pos(7),{1,2}));

    Board b1({4,3},0);

    CHECK(b1.compare_pos(b1.int_to_pos(1),{1,0}));
    //std::cout<<"Position {1,0} == {"<<b1.int_to_pos(1).x<<", "<<b1.int_to_pos
    //(1).y<<"}\n";

    CHECK(b1.compare_pos(b1.int_to_pos(3),{3,0}));
    //std::cout<<"Position {3,0} == {"<<b1.int_to_pos(3).x<<", "<<b1.int_to_pos
   // (1).y<<"}\n";

    Board::Position pos = b1.int_to_pos(6);
    CHECK(b1.compare_pos(pos,{2,1}));
    //std::cout<<"Position {2,1} == {"<<pos.x<<","<<pos.y<<"}\n";
}

TEST_CASE("board: pos_to_int")
{
    Board b({4,3},0);
    CHECK(b.pos_to_int({0,0})==0);
    CHECK(b.pos_to_int({1,2})==9);
    CHECK(b.pos_to_int({2,1})==6);
}

TEST_CASE("board: random mine placement")
{
    //Same conditions
    Board b1({5,4},10);
    Board b2({5,4},10);
    //same # of mines
    CHECK(b1.get_pos_mines().size()==b2.get_pos_mines().size());
    int count = 1;
    for(Board::Position pos:b1.get_pos_mines())
    {
        std::cout<<"mine position "<<count<<" : {"<<pos.x<<","<<pos.y<<"}\n";
        count++;
    }
    //Different placement
    CHECK_FALSE(b2.compare_boards(b1));
}

TEST_CASE("board: correct number of surrounding mines")
{
    //Init: no mines -> all number tiles should be 0
    Board b1({2, 2}, 0);
    CHECK(b1.get_pos_data({0, 0}).num_of_mines == 0);

    //Init: 1 randomly placed mine, relocated to {1,1}
    //all number tiles should be 1
    Board b2({3, 3}, 1);
    b2.set_mines(std::vector<int>(1, 4));
    CHECK(b2.compare_pos(b2.get_pos_mines()[0], {1, 1}));
    CHECK(b2.get_pos_data({0, 0}).num_of_mines == 1);
    CHECK(b2.get_pos_data({2, 1}).num_of_mines == 1);

    //Init: 1 randomly placed mine, relocated to {0,0}
    //3 number tiles should be 1: {1,0}, {1,1}, {0,1}
    //5 number tiles should be 0: {0,2},{1,2},{2,2},{2,1},{2,0}
    Board b3({3, 4}, 1);
    b3.set_mines(std::vector<int>(1, 0));
    CHECK(b3.get_pos_data({1, 1}).num_of_mines == 1);
    CHECK(b3.get_pos_data({2, 2}).num_of_mines == 0);

    //Init: 3 randomly placed mines, relocated to {1,0}, {3,0}, {2,1}
    Board b4({4, 3}, 3);
    b4.set_mines(std::vector<int> {1, 3, 6});
    CHECK(b4.get_pos_data({1,0}).mine);
    CHECK(b4.get_pos_data({3,0}).mine);
    CHECK(b4.get_pos_data({2,1}).mine);
    CHECK(b4.get_pos_data({1, 2}).num_of_mines == 1);
    CHECK(b4.get_pos_data({0, 2}).num_of_mines == 0);
    CHECK(b4.get_pos_data({2, 0}).num_of_mines == 3);
}

TEST_CASE("board: unveiling correct mine tiles")
{
    Board b({3,3},2);
    b.set_mines(std::vector<int>{1,0});
    CHECK(b.get_pos_data({0,0}).mine);
    CHECK(b.get_pos_data({1,0}).mine);
    b.unveil_mines();
    CHECK(b.get_pos_data({0,0}).unveiled);
    CHECK(b.get_pos_data({1,0}).unveiled);

}
/*
////MODEL TEST CASES
/*
TEST_CASE("correct initial states")
{
    Model m(10,10, 0);
    CHECK(m.check_unveiled_({5,4})==false);
    CHECK(m.check_mine_({6,2})==false);
    CHECK(m.check_flagged_({1,9})==false);
}

TEST_CASE("check unveil_tiles: mines")
{
    Model m(3,3, 2);
    Board b = m.change_board();
    b.set_mines(std::vector<int>{0,1});
    CHECK(b.get_pos_data({0,0}).mine==true);
    CHECK(b.get_pos_data({1,0}).mine==true);
    m.unveil_tile({0,0});
    //CHECK(m.get_unveiled_tiles_()==1);
    //CHECK(b.get_pos_data({0,0}).unveiled);
    //CHECK();
    //CHECK();
    //m.check_mi
    //CHECK(m.check_unveiled_({0,1}));
    //CHECK(m.is_game_over());
    CHECK_FALSE(m.win_or_loss());
}
*/
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//

