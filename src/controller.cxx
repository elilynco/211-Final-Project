/*#include "controller.hxx"


Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    //view_.draw(set);
}
*/


#include "controller.hxx"

Controller::Controller(int size, int n_mines)
        : Controller(size,size, n_mines)
{ }

Controller::Controller(int width, int height, int n_mines)
        : model_(width, height, n_mines),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites, mouse_position_);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

//place a tile and plays move once mouse is clicked
void
Controller::on_mouse_down(ge211::Mouse_button button, ge211::Posn<int> position)
{
    //unveil_tile(Position pos);
    //flag_tile(Position pos);
    Model::Position board_pos = view_.screen_to_board(position);
    //left click is uncover mine
    //right is put flag

    //to unveil tile: game not over, left click, and tile is not unveiled
    // and there is no flag

    if(button == ge211::Mouse_button::left &&
    !model_.check_unveiled_(board_pos) && !model_.check_flagged_(board_pos))
    {
        std::cout << "left click";
        model_.unveil_tile(board_pos);

    }

    //put or remove a flag
    if(!model_.is_game_over() && button == ge211::Mouse_button::right)
    {
        model_.flag_tile(board_pos);
    }


}

//follows position of the mouse
void
Controller::on_mouse_move(View::Position screen_position)
{
    mouse_position_ = screen_position;
}

