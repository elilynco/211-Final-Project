
//
// Created by elily on 11/19/2021.
//

#ifndef FINAL_PROJECT_BOARD_HXX
  #define FINAL_PROJECT_BOARD_HXX

#endif //FINAL_PROJECT_BOARD_HXX

/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#pragma once

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>


/// Represents the state of the board.
class Board
{
public:
    //STRUCT USED TO HOLD INFO ABOUT STATES
    struct pos_states
    {
        bool flagged;
        bool unveiled;
        bool mine;
        int num_of_mines;
    };

    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;
    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;
    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

private:
    // PRIVATE DATA MEMBERS
    int NUM_MINES_;
    ///Dimensions of Board(size)
    Dimensions dims_;
    ////LINKS POSITION(key) ON BOARD TO ITS INFORMATION(value)->pos_states struct
    //std::unordered_map<Position, pos_states> pos_data_;
    std::vector<struct pos_states> pos_data_;
    ///LIST OF POSITIONS OF MINES
    std::vector<int> pos_mines_;


public:
    // PUBLIC CONSTRUCTOR & FUNCTION MEMBERS
    /// Constructs a board with the given dimensions.
    /// ## Errors:
    ///  - Throws `ge211::Client_logic_error` if either dimension is less than 2 or greater than 8.
    explicit Board(Dimensions dims, int n_mines);

    /// Returns the same `Dimensions` value passed to the constructor.
    Dimensions dimensions() const;

    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;
    void bounds_check_(Position where) const;
    /// Returns the `Player` stored at `pos`.
    /// ## Errors
    ///  - throws `ge211::Client_logic_error` if `!good_position(pos)`.

    //
    // PUBLIC CONSTRUCTOR & FUNCTION MEMBERS
    //

    /// Returns a rectangle containing all the positions of the board. This
    /// can be used to iterate over the positions:

    /// for (Position pos : a_board.all_positions()) {
    ///     ... a_board[pos] ...;
    /// }

    /// Note that `Rectangle`s are considered to be closed on the top
    /// and left, but open on the bottom and right. The iterator will visit
    /// the correct positions for the board.
    Rectangle all_positions() const;

    ///HELPER to change position to int, vice-versa
    int pos_to_int(Position pos) const;
    Position int_to_pos(int n) const;
    //HELPER that returns a vector of directions based on position
    std::vector<Position> adj_directions(Position pos);

    //Getters
    ///gets the pos_states struct as the position
    pos_states get_pos_data(Position pos)const;
    ///gets NUM_MINES_
    int get_num_mines() const
    {
        return NUM_MINES_;
    }
    std::vector<Position> get_pos_mines()const;

    //Modifiers
    ///if unflagged(True), flags tile and vice-versa(False)
    bool flag_unflag(Position pos);
    ///unveils tile and surrounding tiles if they are 0
    void unveil_number(Position pos);
    ///unveils all mines
    void unveil_mines();

    //FUNCTIONS FOR TESTING
    bool compare_pos(Position pos1, Position pos2);
    bool compare_boards(Board b1);
    ///sets mines at all positions within the vector. v.size() == NUM_MINES_
    bool set_mines(std::vector<int> v);

private:
    //
    // PRIVATE HELPER FUNCTION MEMBERS
    //


    ///THE FOLLOWING HELPERS HAVE TO BE CALLED IN THE FOLLOWING ORDER TO WORK

    ///HELPER to init pos_data vector
    void initiate_pos_data_() ;
    ///HELPER to add bombs to map
    void add_bombs_();
    ///HELPER to add number of surrounding mines to map
    void add_numbers_();
};
