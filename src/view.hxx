/*#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;
};
*/


#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    void draw(ge211::Sprite_set& set, Position mouse_position);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    Position board_to_screen (Model :: Position logical ) const ;
    Position screen_to_board (Position physical) const ;
    bool check_mine_(Position pos) const;


    /*Circle_sprite
    Image_sprite
    Rectangle_sprite
    Text_sprite*/

    //bottom tiles 0
    //mine, number sprites 1
    //top tiles 2
    //flag 3
    //mouse position sprite 4

private:
    ge211::Font sans{"sans.ttf", 25};
    ge211::Font big_sans{"sans.ttf", 75};
    Model const& model_;
    std::string counter_str = std::to_string(model_.get_board().get_num_mines());

    ge211::Rectangle_sprite const bottom_tile_sprite;
    ge211::Rectangle_sprite const top_tile_sprite;
    ge211::Rectangle_sprite const ending_tile_sprite;

    ge211::Circle_sprite const mine_sprite;

    ge211::Text_sprite const number_sprite;
    ge211::Text_sprite const number_sprite1;
    ge211::Text_sprite const number_sprite2;
    ge211::Text_sprite const number_sprite3;
    ge211::Text_sprite const number_sprite4;
    ge211::Text_sprite const number_sprite5;
    ge211::Text_sprite const number_sprite6;
    ge211::Text_sprite const number_sprite7;
    ge211::Text_sprite const number_sprite8;

    ge211::Text_sprite const win_sprite;
    ge211::Text_sprite const lose_sprite;
    ge211::Text_sprite const counter_sprite;

    //can change this to ge211::Image_sprite when functioning
    ge211::Circle_sprite const flag_sprite;

    //can change this to ge211::Image_sprite when functioning
    ge211::Circle_sprite const mouse_sprite;
    ge211::Circle_sprite const valid_mouse_sprite;

};
