#include "model.hxx"
#include "model.hxx"

using namespace ge211; //i dunno what this means lol

//CONSTRUCTORS
Model::Model(int size, int n_mines)
        : Model(size, size, n_mines)
{ }

Model::Model(int width, int height, int n_mines)
        : board_({width, height}, n_mines),
          victory_(false),
          game_over_(false),
          flag_counter_(0),
          unveiled_tiles_(0)
{}

//METHOD BODIES
Model::Rectangle
Model::board() const
{
    return board_.all_positions();
}

bool
Model::check_mine_(Position pos) const
{
    /*
    std::cout<<"check_mine_: Position={"<<pos.x<<","<<pos.y
        <<"}, mine?="<<board_.get_pos_data(pos).mine<<"\n";
        */
    int count =1;
    for(Board::Position pos:board_.get_pos_mines())
    {
        std::cout<<"mine position "<<count<<" : {"<<pos.x<<","<<pos.y<<"}\n";
        count++;
    }
    return board_.get_pos_data(pos).mine;

}

bool
Model::check_flagged_(Position pos) const
{
    return board_.get_pos_data(pos).flagged;
}

bool
Model::check_unveiled_(Position pos) const
{
    return board_.get_pos_data(pos).unveiled;
}

int
Model::surrounding_mines_(Position pos) const
{
    if(board_.get_pos_data(pos).mine)
    {
        return 0;
    }
    else
    {
       return board_.get_pos_data(pos).num_of_mines;
    }

}

void
Model::flag_tile(Position pos)
{
    //if flagged-> flag, and then increase counter
    if(board_.flag_unflag(pos))
    {
        flag_counter_++;
    }
    //if not flagged-> remove flag, decrease counter
    else
    {
        flag_counter_--;
    }
}

void
Model::unveil_tile(Position pos)
{
    //only can unveil tiles that aren't flagged
    if(!check_flagged_(pos))
    {
        //std::cout<<"(1) not flagged \n";
        //if unveiled pos is a mine: unveil ALL mines, end game as a loss

        if(board_.get_pos_data({0,0}).mine)
        {
            //std::cout<<"(2) found a mine \n";
            board_.unveil_mines(); //(0,0) is always uncovered when a mine is
            // clicked
            game_over_ = true;
        }
        else
        {
            //std::cout<<"(2) found a number \n";
            unveiled_tiles_++;
            //board_.unveil_number(pos); //giving segfualt errors
            //if all number tiles have been unveiled: end game as win
            // (# unveiled tiles == # total tile - num_mines)
            if(unveiled_tiles_ == (board_.dimensions().width*board_.dimensions().height)- board_.get_num_mines())
            {
                game_over_= true;
                victory_ = true;
            }
        }
    }
}


/*
//is position valid-> check tile (USED ONLY WHEN MOUSE IS LEFT CLICK)
 -position as argument
 -if there is a flag on a position, if you left click it nothing will happen//ONLY IF POSITION IS UNFLAGGED
 -is this position a mine? -> game over (LOSS)
 -is the a number -> unveil == true
    -check if all tiles that aren't mines have been cleared-> game over (WIN) //mines counter = # of set mines and check counter for amount of tiles unveiled

//unflagging/flagging a tile-> change state of tile (USED ONLY WHEN MOUSE IS RIGHT CLICK)
 -position as argument
 -if the position already flagged -> unflag and change flag counter
 -if the position not flagged -> flag and change flag counter
 */