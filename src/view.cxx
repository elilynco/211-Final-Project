/*#include "view.hxx"

View::View(Model const& model)
        : model_(model)
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
}
*/



#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

//Constants (size and color）
static int const padding = 2;
static int const grid_size = 50;
static int const tile_size= (grid_size - 2*padding);
static int const mine_size= 23;    //size of each tile + (padding = 2)
static ge211::Color const gray_color {100, 100, 100};



View::View(Model const& model)
        : model_(model),
          bottom_tile_sprite({tile_size,tile_size}, Color::medium_green()),
          top_tile_sprite({tile_size,tile_size}, gray_color),
          ending_tile_sprite({tile_size,tile_size}, Color::black()),
          mine_sprite(mine_size, Color::medium_red()),
          number_sprite1("1", sans),
          number_sprite2("2", sans),
          number_sprite3("3", sans),
          number_sprite4("4", sans),
          number_sprite5("5", sans),
          number_sprite6("6", sans),
          number_sprite7("7", sans),
          number_sprite8("8", sans),
          win_sprite("You won!", big_sans),
          lose_sprite("You lost!", big_sans),
          counter_sprite(counter_str,
                         big_sans),
          flag_sprite(mine_size, Color::medium_yellow()),
          mouse_sprite(mine_size, Color::medium_cyan()),
          valid_mouse_sprite(mine_size, Color::medium_blue())
{ }


bool
View::check_mine_(Position pos) const
{
    return model_.check_mine_(pos);
}


void View::draw(Sprite_set& set, Position mouse_position)
{
    //draw tiles
    //draw mines & numbers
    //draw veiled tiles
    //draw flags
    set.add_sprite(counter_sprite, {model_.get_dims_().width,model_.get_dims_
    ().height}, 7);

    for (auto pos: model_.board())
    {
        std::cout<<"number of mines" << model_.get_board().get_num_mines()
            <<"\n";

        Position tile_pos = {(board_to_screen(pos).x+ padding),board_to_screen
                             (pos).y+padding};
        //drawing all the background tiles
        set.add_sprite(bottom_tile_sprite, tile_pos, 0);

        //drawing mines
        if(model_.check_mine_(pos))
        {
            set.add_sprite(mine_sprite, tile_pos, 1);
        }


        //drawing number tiles depending on how many surrounding mines are
        //around the tile

        if(model_.surrounding_mines_(pos) == 1)
        {
            set.add_sprite(number_sprite1, tile_pos, 1);
        }
        if(model_.surrounding_mines_(pos) == 2)
        {
            set.add_sprite(number_sprite2, tile_pos, 1);
        }
        if(model_.surrounding_mines_(pos) == 3)
        {
            set.add_sprite(number_sprite3, tile_pos, 1);
        }
        if(model_.surrounding_mines_(pos) == 4)
        {
            set.add_sprite(number_sprite4, tile_pos, 1);
        }
        if(model_.surrounding_mines_(pos) == 5)
        {
            set.add_sprite(number_sprite5, tile_pos, 1);
        }
        if(model_.surrounding_mines_(pos) == 6)
        {
            set.add_sprite(number_sprite6, tile_pos, 1);
        }
        if(model_.surrounding_mines_(pos) == 7)
        {
            set.add_sprite(number_sprite7, tile_pos, 1);
        }
        if(model_.surrounding_mines_(pos) == 8)
        {
            set.add_sprite(number_sprite8, tile_pos, 1);
        }


        //if tile has not been unveiled, draw top tile
        if(!model_.check_unveiled_(pos))
        {
            //set.add_sprite(top_tile_sprite, tile_pos, 2);
        }

        //drawing flags
        if(model_.check_flagged_(pos))
        {
            set.add_sprite(flag_sprite, tile_pos, 3);
        }

        //if tile is unveiled then draw regular mouse sprite, otherwise if
        //tile is uncovered, mouse should change color since it's a valid tile
        //to uncover
        if(!model_.check_unveiled_(pos))
        {
            set.add_sprite(mouse_sprite, mouse_position, 6);
        }
        else
        {
            set.add_sprite(valid_mouse_sprite, mouse_position, 6);
        }

        //when you lose (game is over because you clicked on mine), expose all
        //mines (and get rid of upper tile) and highlight mine you clicked on

        //when you win, mines remain covered and flag are drawn on the mine
        //positions if they haven't already


        if (model_.is_game_over() && model_.win_or_loss()) {
            set.add_sprite(ending_tile_sprite, tile_pos, 4);
            set.add_sprite(win_sprite, {model_.get_dims_().width/4,model_
            .get_dims_
                                                                               ().height}, 5);
        }

        if (model_.is_game_over() && !model_.win_or_loss())
        {
            set.add_sprite(ending_tile_sprite, tile_pos, 4);
            set.add_sprite(lose_sprite, {model_.get_dims_().width/4,model_
            .get_dims_
                                                                                ().height}, 5);
        }

    }
}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Minesweeper";
}


View::Position View::board_to_screen(Model::Position logical) const {
    logical.x *= grid_size;
    logical.y *= grid_size;
    return logical;
}

Model::Position View::screen_to_board(View::Position physical) const {
    physical.x /= grid_size;
    physical.y /= grid_size;
    return physical;
}


