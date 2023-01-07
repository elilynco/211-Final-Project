#pragma once

#include <ge211.hxx>
#include "board.hxx"

#include <ge211.hxx>

#include <iostream>
#include <vector>
class Model
{
public:
    using Dimensions = Board::Dimensions;
    using Position = Board::Position;
    using Rectangle = Board::Rectangle;

    //CONSTRUCTORS
    Model(int width, int height, int n_mines);
    Model(int size, int n_mines);

    //METHODS
    bool is_game_over() const
    {
        return game_over_;
    }
    bool win_or_loss() const
    {
        return victory_;
    }
    //GETTERS
    ////gets board_ in terms of positions
    Rectangle board() const;
    ////gets board_ in as a vector<pos_states>
    Board get_board() const
    {
        return board_;
    }
    ////gets unveiled_tiles_
    int get_unveiled_tiles_()
    {
        return unveiled_tiles_;
    }
    ////gets dims_ of board
    Board::Dimensions get_dims_() const
    {
        return board_.dimensions();
    }
    ////checks whether tile is a mine
    bool check_mine_(Position pos) const;
    ////checks whether the tile is flagged(true) or not(false)
    bool check_flagged_(Position pos) const;
    ////checks whether the tile is unveiled(true) or not(false)
    bool check_unveiled_(Position pos) const;
    ////returns the # of surrounding mines, will return 0 if a mine
    int surrounding_mines_(Position pos) const;

    //MODIFIERS
    ///left click: unveils the tile and checks if its a mine (PLAY MOVE)
    void unveil_tile(Position pos);
    ///right click: flags/unflags changes flag_counter_
    void flag_tile(Position pos);


    //TESTING HELPER
    Board change_board()
    {
        return board_;
    }

private:
    //PRIVATE MEMBER VARIABLES
    Board board_;
    bool victory_;
    bool game_over_;
    int flag_counter_;
    int unveiled_tiles_;
};