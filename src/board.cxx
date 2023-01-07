
/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "board.hxx"
#include <algorithm>
#include <ge211.hxx>


Board::Board(Dimensions dims, int n_mines)
        : NUM_MINES_(n_mines),
        dims_(dims)
{
    if (dims_.width < 2 || dims_.height < 2)
    {
        throw ge211::Client_logic_error("Board::Board: dims too small");
    }
    if(NUM_MINES_>(dims_.width*dims_.height))
    {
        throw ge211::Client_logic_error("Board::Board: too many mines");
    }
    if(NUM_MINES_<0)
    {
        throw ge211::Client_logic_error
            ("Board::Board: no negative number of mines");
    }
    initiate_pos_data_();
    add_bombs_();
    add_numbers_();
}

Board::Dimensions
Board::dimensions() const
{
    return dims_;
}

bool
Board::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}

Board::Rectangle
Board::all_positions() const
{
    return Rectangle::from_top_left(ge211::the_origin, dims_);
}

void
Board::bounds_check_(Position pos) const
{
    if (!good_position(pos))
    {
        throw ge211::Client_logic_error("Board: position out of bounds");
    }
}




///OUR FUNCTIONS

int
Board::pos_to_int(Position pos) const
{
    return (dims_.width*pos.y)+pos.x;
}

Board::Position
Board::int_to_pos(int n) const
{
    int x = n%dims_.width;
    //std::cout<<"x: ("<<n<<"%"<<dims_.width<<") = "<<x<<"; ";
    int y = trunc(n/dims_.width);
    //std::cout<<"y: ("<<n<<"/"<<dims_.width<<") = "<<y<<"\n";
    return {x,y};
}
std::vector<Board::Position>
 Board::adj_directions(Position pos)
 {
    return std::vector<Position>{{pos.x,pos.y-1},{pos.x+1,pos.y-1},
                                 {pos.x+1,pos.y},{pos.x+1,pos.y+1},
                                 {pos.x,pos.y+1},{pos.x-1,pos.y+1},
                                 {pos.x-1,pos.y},{pos.x-1,pos.y-1}};
 }

//GETTERS
Board::pos_states
Board::get_pos_data(Position pos) const
{
    bounds_check_(pos);
    int n = pos_to_int(pos);
    return pos_data_[n];
}

std::vector<Board::Position>
Board::get_pos_mines() const
{
    std::vector<Board::Position> v (NUM_MINES_, {0,0});
    for(int i = 0; i< NUM_MINES_; i++)
    {
        v[i] = int_to_pos(pos_mines_[i]);
    }
    return v;
}

bool
Board::flag_unflag(Position pos)
{
    int n = pos_to_int(pos);
    //IF ALREADY FLAGGED
    if (!pos_data_[n].flagged)
    {
        pos_data_[n].flagged = false;
        return false;
    }
        //IF NOT FLAGGED YET
    else
    {
        pos_data_[n].flagged = true;
        return true;
    }
}

//Modifiers
void
Board::unveil_number(Position pos)
{
    int n = pos_to_int(pos);
    pos_data_[n].unveiled = true;

    //if surrounding mines are 0, also unveiled->USES RECURSION!!
    for(Position adj_pos:adj_directions(pos))
    {
        if(good_position(adj_pos))
        {
            if(pos_data_[pos_to_int(adj_pos)].num_of_mines == 0)
            {
                pos_data_[pos_to_int(adj_pos)].unveiled = true;
                unveil_number(adj_pos);
            }
        }
    }
}

void
Board::unveil_mines()
{
    for(auto n: pos_mines_)
    {
        //unveils all the mines
        pos_data_[n].unveiled = true;

        if(pos_data_[n].flagged)
        {
            //removes the flags from the unveiled mines
            pos_data_[n].flagged = false;
        }
    }
}





//HELPER to init pos_data unordered map: for all positions on the board,
//add the pos in as a key, and an init_struct as the value
void
Board::initiate_pos_data_()
{
    //initial state for all the structs (states)->
    // not flagged, not unveiled, not a mine, no surrounding mines
    struct pos_states init_state = {false, false, false, 0};
    //number of tiles
    int n_pos = dims_.width*dims_.height;
    pos_data_ = std::vector<struct pos_states>(n_pos, init_state);
}

void
Board::add_bombs_()
{
    int width = dims_.width;
    int height = dims_.height;
    pos_mines_ = std::vector<int>(NUM_MINES_,0);
    int i = 0;
    while(i< NUM_MINES_)
    {

        //std::cout<<rand()%width<<"\n";
        int rand_x = rand() % width;
        int rand_y = rand() % height;
        //std::cout<<"rand_x: "<<rand_x<<" & rand_y: "<<rand_y<<"\n";
        int n = pos_to_int({rand_x,rand_y});
        //access list and see if it is valid and mine is false
        /*
        std::cout<<"Mine position: "<<n<<" aka {"<<rand_x<<","
            <<rand_y<<"} is"<<pos_data_[n].mine<<"\n";
        */
        if (good_position({rand_x,rand_y})&&(!pos_data_[n].mine))
        {
            //std::cout<<"       -> it is placed down as mine "<<i<<"\n";
            pos_data_[n].mine = true;
            pos_mines_[i] = n;
            i++;
        }
    }
}

void
Board::add_numbers_()
{
    Position pos = {0,0};
    for(int n = 0; n<dims_.width*dims_.height; n++)
    {
        pos = int_to_pos(n);
        for(Position adj_pos:adj_directions(pos))
        {
            if(good_position(adj_pos))
            {
                if(pos_data_[pos_to_int(adj_pos)].mine)
                {
                    pos_data_[n].num_of_mines++;
                }
            }
        }
    }
}

///FUNCTIONS FOR TESTING
bool
Board::compare_pos(Board::Position pos1, Board::Position pos2)
{
    return pos1.x == pos2.x && pos2.y == pos1.y;
}

bool
Board::compare_boards(Board b1)
{
    for(int i = 0; i<NUM_MINES_; i++)
    {
        if(pos_mines_[i] != b1.pos_mines_[i])
        {
            return false;
        }
    }
    return true;
}

bool
Board::set_mines(std::vector<int> v)
{
    int i =0;
    if(static_cast<int>(v.size())==NUM_MINES_)
    {
        //clear states
        initiate_pos_data_();
        //set mines
        for(int n: v)
        {
            pos_data_[n].mine= true;
            pos_mines_[i] = n;
            i++;
        }
        //set numbers
        add_numbers_();
        return true;
    }
    return false;
}