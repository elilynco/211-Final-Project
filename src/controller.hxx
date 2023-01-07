/*#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;

private:
    Model model_;
    View view_;
};
*/

#pragma once

#include "model.hxx"
#include "view.hxx"

// The main game class for Reversi.
class Controller : public ge211::Abstract_game
{
public:

    // Constructs a game with `size` as both its width and height.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if `size` is less than
    explicit Controller(int size = 8, int n_mines = 4);

    // Constructs a game with the given width and height.
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if either dimension is less
    //    than 2
    Controller(int width, int height, int n_mines);

    // `protected` means that GE211 (via base class `ge211::Abstract_game`)
    // can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //

    void on_mouse_down(ge211::Mouse_button, View::Position) override;
    void on_mouse_move(View::Position) override;

    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View  view_;

    View::Position mouse_position_{0,0};
};
