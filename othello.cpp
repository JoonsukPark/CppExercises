#include<iostream>
#include<vector>
#include<cctype>
#include<array>

const int board_size = 6;
std::array<std::array<int, board_size>, board_size> board;
std::array<std::array<int, board_size>, board_size> board2;

void init_board()
{
    for(int i=0; i<board_size; i++)
    {
        for(int j=0; j<board_size; j++)
        {
            if((i == board_size/2 && j == board_size/2-1) || (i == board_size/2-1 && j == board_size/2))
            {
                board[i][j] = 1;
            }
            else if((i == board_size/2-1 && j == board_size/2-1) || (i == board_size/2 && j == board_size/2))
            {
                board[i][j] = -1;
            }
            else board[i][j] = 0;
        }
    }
}

void draw_board()
{
    for(int i=0; i <= 2*board_size; i++)
    {
        if(i % 2 == 0)
        {
            for(int j=0; j < 4*board_size+1; j++)
            {
                std::cout << '-';
            }
        }
        else
        {
            for(int j=0; j<board_size; j++)
            {
                if(board[i/2][j] == -1)
                {
                    if(j==0) std::cout << '|' << ' ' << "\u25CF" << ' ' << '|';
                    else std::cout << ' ' << "\u25CF" << ' ' << '|';
                }
                else if(board[i/2][j] == 1)
                {
                    if(j==0) std::cout << '|' << ' ' << "\u25CB" << ' ' << '|';
                    else std::cout << ' ' << "\u25CB" << ' ' << '|';
                }
                else
                {
                    if(j==0) std::cout << '|' << ' ' << ' ' << ' ' << '|';
                    else std::cout << ' ' << ' ' << ' ' << '|';
                }
            }
        }
        std::cout << std::endl;
    }
    return;
}

int validate_right(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_col == board_size) return -1;
    int j = input_col;
    if(input*board[input_row-1][j] != -1) return -1;
    else
    {
        ++j;
        while(j < board_size)
        {
            if(board[input_row-1][j] == 0) return -1;
            if(board[input_row-1][j-1]*board[input_row-1][j] == -1) break;
            ++j;
        }
        if(j == board_size) return -1;
        else return j;        
    }
}

int validate_left(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_col == 1) return -1;
    int j = input_col-2;
    if(input*board[input_row-1][j] != -1) return -1;
    else
    {
        --j;
        while(j >= 0)
        {
            if(board[input_row-1][j] == 0) return -1;
            if(board[input_row-1][j]*board[input_row-1][j+1] == -1) break;
            --j;
        }
        if(j == -1) return -1;
        else return j;        
    }
}

int validate_up(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_row == 1) return -1;
    int j = input_row-2;
    if(input*board[j][input_col-1] != -1) return -1;
    else
    {
        --j;
        while(j >= 0)
        {
            if(board[j][input_col - 1] == 0) return -1;
            if(board[j][input_col - 1]*board[j+1][input_col - 1] == -1) break;
            --j;
        }
        if(j == -1) return -1;
        else return j;        
    }
}

int validate_down(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_row == board_size) return -1;
    int j = input_row;
    if(input*board[j][input_col-1] != -1) return -1;
    else
    {
        ++j;
        while(j >= 0)
        {
            if(board[j][input_col - 1] == 0) return -1;
            if(board[j][input_col - 1]*board[j-1][input_col - 1] == -1) break;
            ++j;
        }
        if(j == -1) return -1;
        else return j;        
    }
}

int validate_upperleft(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_row == 1 || input_col == 1) return -1;
    int j = input_row-2;
    int k = input_col-2;
    
    if(input*board[j][k] != -1) return -1;
    else
    {
        --j;
        --k;
        
        while(j >= 0 && k >= 0)
        {
            if(board[j][k] == 0) return -1;
            if(board[j][k]*board[j+1][k+1] == -1) break;
            --j;
            --k;
        }
        if(j == -1 || k==-1) return -1;
        else return j;        
    }
}

int validate_upperright(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_row == 1 || input_col == board_size) return -1;
    int j = input_row-2;
    int k = input_col;
    
    if(input*board[j][k] != -1) return -1;
    else
    {
        --j;
        ++k;
        
        while(j >= 0 && k < board_size)
        {
            if(board[j][k] == 0) return -1;
            if(board[j][k]*board[j+1][k-1] == -1) break;
            --j;
            ++k;
        }
        if(j == -1 || k==board_size) return -1;
        else return j;        
    }
}

int validate_lowerleft(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_row == board_size || input_col == 1) return -1;
    int j = input_row;
    int k = input_col-2;
    
    if(input*board[j][k] != -1) return -1;
    else
    {
        ++j;
        --k;
        
        while(j < board_size && k >= 0)
        {
            if(board[j][k] == 0) return -1;
            if(board[j][k]*board[j-1][k+1] == -1) break;
            ++j;
            --k;
        }
        if(j==board_size || k == -1) return -1;
        else return j;        
    }
}

int validate_lowerright(std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col)
{
    if(input_row == board_size || input_col == board_size) return -1;
    int j = input_row;
    int k = input_col;
    
    if(input*board[j][k] != -1) return -1;
    else
    {
        ++j;
        ++k;
        
        while(j < board_size && k < board_size)
        {
            if(board[j][k] == 0) return -1;
            if(board[j][k]*board[j-1][k-1] == -1) break;
            ++j;
            --k;
        }
        if(j==board_size || k == board_size) return -1;
        else return j;        
    }
}

std::array<std::array<int, board_size>, board_size> execute_right(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int rightlim)
{
    for(int k=input_col-1; k<rightlim; k++)
    {
        board[input_row-1][k] = input;
    }
    return board;
}

std::array<std::array<int, board_size>, board_size> execute_left(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int leftlim)
{
    for(int k=leftlim+1; k<input_col; k++)
    {
        board[input_row-1][k] = input;
    }
    return board;
}

std::array<std::array<int, board_size>, board_size> execute_up(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int lowerlim)
{
    for(int k=lowerlim+1; k<input_row; k++)
    {
        board[k][input_col-1] = input;
    }
    return board;
}

std::array<std::array<int, board_size>, board_size> execute_down(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int upperlim)
{
    for(int k=input_row-1; k<upperlim; k++)
    {
        board[k][input_col-1] = input;
    }
    return board;
}

std::array<std::array<int, board_size>, board_size> execute_upperleft(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int upperleftlim)
{
    int j = input_col - 1;
    for(int i=input_row - 1; i > upperleftlim; i--)
    {
        board[i][j] = input;
        j--;
    }
    return board;
}

std::array<std::array<int, board_size>, board_size> execute_upperright(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int upperrightlim)
{
    int j = input_col - 1;
    for(int i=input_row - 1; i > upperrightlim; i--)
    {
        board[i][j] = input;
        j++;
    }
    return board;
}

std::array<std::array<int, board_size>, board_size> execute_lowerleft(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int lowerleftlim)
{
    int j = input_col - 1;
    for(int i = input_row - 1; i < lowerleftlim; i++)
    {
        board[i][j] = input;
        j--;
    }
    return board;
}

std::array<std::array<int, board_size>, board_size> execute_lowerright(
    std::array<std::array<int, board_size>, board_size> &board,
    int input, int input_row, int input_col, int lowerrightlim)
{
    int j = input_col - 1;
    for(int i = input_row - 1; i < lowerrightlim; i++)
    {
        board[i][j] = input;
        j++;
    }
    return board;
}

int validate_move(std::array<std::array<int, board_size>, board_size> &board, int move, int input_row, int input_col)
{
    if((board[input_row-1][input_col-1] == 0) && 
        (validate_up(board, move, input_row, input_col) != -1 ||
        validate_down(board, move, input_row, input_col) != -1 ||
        validate_left(board, move, input_row, input_col) != -1 ||
        validate_right(board, move, input_row, input_col) != -1 ||
        validate_upperleft(board, move, input_row, input_col) != -1 ||
        validate_upperright(board, move, input_row, input_col) != -1 ||
        validate_lowerleft(board, move, input_row, input_col) != -1 ||
        validate_lowerright(board, move, input_row, input_col) != -1)) return 1;
    else return 0;
}

std::array<std::array<int, board_size>, board_size> execute_move(
    std::array<std::array<int, board_size>, board_size> &board, int input, int input_row, int input_col)
{
    if(input_col != board_size)
    {
        int rightlim = validate_right(board, input, input_row, input_col);
        if(rightlim != -1)
        {
            execute_right(board, input, input_row, input_col, rightlim);
        }
    }
    
    if(input_col != 1)
    {
        int leftlim = validate_left(board, input, input_row, input_col);
        if(leftlim != -1)
        {
            execute_left(board, input, input_row, input_col, leftlim);
        }
    }

    if(input_row != 1)
    {
        int lowerlim = validate_up(board, input, input_row, input_col);
        if(lowerlim != -1)
        {
            execute_up(board, input, input_row, input_col, lowerlim);
        }
    }
    
    if(input_row != board_size)
    {
        int upperlim = validate_down(board, input, input_row, input_col);
        if(upperlim != -1)
        {
            execute_down(board, input, input_row, input_col, upperlim);
        }
    }
    
    if(input_row != 1 && input_col != 1)
    {
        int upperleftlim = validate_upperleft(board, input, input_row, input_col);
        if(upperleftlim != -1)
        {
            execute_upperleft(board, input, input_row, input_col, upperleftlim);
        }
    }
    
    if(input_row != 1 && input_col != board_size)
    {
        int upperrightlim = validate_upperright(board, input, input_row, input_col);
        if(upperrightlim != -1)
        {
            execute_upperright(board, input, input_row, input_col, upperrightlim);
        }
    }

    if(input_row != board_size && input_col != board_size)
    {
        int lowerrightlim = validate_lowerright(board, input, input_row, input_col);
        if(lowerrightlim != -1)
        {
            execute_lowerright(board, input, input_row, input_col, lowerrightlim);
        }
    }
    
    if(input_row != board_size && input_col != 1)
    {
        int lowerleftlim = validate_lowerleft(board, input, input_row, input_col);
        if(lowerleftlim != -1)
        {
            execute_lowerleft(board, input, input_row, input_col, lowerleftlim);
        }
    }
    return board;
}


int game_over(std::array<std::array<int, board_size>, board_size> &board)
{
    int zeros = 0;
    int whites = 0;
    int blacks = 0;
    for(int i=0; i<board_size; i++)
    {
        for(int j=0; j<board_size; j++)
        {
            if(board[i][j] == 0) zeros++;
            else if(board[i][j] == 1) blacks++;
            else whites++;
        }
    }
    if(zeros == 0 || whites== 0 || blacks == 0) return 1;
    else return 0;
}

std::vector<int> scores(std::array<std::array<int, board_size>, board_size> &x)
{
    int whites = 0;
    int blacks = 0;
    std::vector<int> output(2);
    
    for(int i=0; i<board_size; i++)
    {
        for(int j=0; j<board_size; j++)
        {
            if(x[i][j]==1) whites += 1;
            else if(x[i][j]==-1) blacks += 1;
        }
    }
    output[0] = whites;
    output[1] = blacks;
    return output;
}

int main()
{
    std::cout << std::endl << "Othello C++ version 2.0" << std::endl << std::endl;
    
    int input_row;
    int input_col;
    
    std::vector<int> nextmove_computer(2);
    int current_gain;
    
    char playagain;
    std::vector<int> score(2);
    
    do
    {
        init_board();
        draw_board();
        
        char first;
        int input = 1;            
        int moved = 0;
        int passed = 0;

        std::cout << "Will you go first (y/n)? ";
        std::cin >> first;
        
        while(!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Will you go first (y/n)? ";
            std::cin >> first;
        }
        
        if(first == 'Y' || first == 'y')
        {
            std::cout << std::endl << std::endl;
        }
        else
        {
            board = execute_move(board, input, 2, 3);
            draw_board();
            std::cout << "Computer's next move is (" << 0 << ',' << 0 << ")." << std::endl;
            input *= -1;
            score = scores(board);
            moved = 1;
            passed = 0;
            std::cout << std::endl << "Score: " << score[0] << " vs " << score[1] << ". " << std::endl;    
        }

        do
        {
            moved = 0;

            if(input == 1) std::cout << "\u25CB \'s turn!" << std::endl;
            else std::cout << "\u25CF \'s turn!" << std::endl;
                
            std::cout << std::endl << "Input row (0: pass, 99=quit): ";
            std::cin >> input_row;
            
            if(!std::cin || input_row < 0 || (input_row > board_size &&
                input_row != 99))
            {
                std::cout << "Not a valid input! " << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }
            
            if(input_row == 99) return 0;
            
            else if(input_row == 0)
            {
                passed += 1;
                input *= -1;
                continue;
            }
            
            std::cout << std::endl << "Input col (0: pass, 99=quit): ";
            std::cin >> input_col;
            
            if(!std::cin || input_row < 0 || (input_row > board_size 
                && input_row != 99))
            {
                std::cout << "Not a valid input! " << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }

            if(input_col == 99) return 0;
            
            else if(input_row == 0)
            {
                passed += 1;
                input *= -1;
                continue;
            }
            std::cout << std::endl;
            
            if(validate_move(board, input, input_row, input_col) == 1)
            {
                execute_move(board, input, input_row, input_col);
                moved = 0;
                passed = 0;
                draw_board();    
                input *= -1;
                score = scores(board);
                std::cout << std::endl << "Score: " << score[0] << " vs " << score[1] << ". " << std::endl;    
            }
            
            else
            {
                std::cout << "Invalid move. " <<std::endl;
                draw_board();
                continue;
            }
            
            if(game_over(board)) break;
            
            nextmove_computer = {-1, -1};
            current_gain = 0;
            
            for(int i=1; i<=board_size; i++)
            {
                for(int j=1; j<=board_size; j++)
                {
                    board2 = board;
                    if(validate_move(board2, input, i, j) == 1)
                    {
                        board2 = execute_move(board2, input, i, j);
                        if(first == 'Y' || first == 'y')
                        {
                            if(scores(board2)[1]-scores(board)[1] > current_gain)
                            {
                                nextmove_computer = {i, j};
                                current_gain = scores(board2)[1] - scores(board)[1];
                            }
                        }
                        else
                        {
                            if(scores(board2)[0]-scores(board)[0] > current_gain)
                            {
                                nextmove_computer = {i, j};
                                current_gain = scores(board2)[0] - scores(board)[0];
                            }
                        }
                    }
                }
            }
            
            if(nextmove_computer[0] != -1)
            {
                board = execute_move(board, input, nextmove_computer[0], nextmove_computer[1]);
                draw_board();
                std::cout << "Computer's next move is (" << nextmove_computer[0] << ',' << nextmove_computer[1] << ")." << std::endl;
                input *= -1;
                score = scores(board);
                moved = 1;
                passed = 0;
                std::cout << std::endl << "Score: " << score[0] << " vs " << score[1] << ". " << std::endl;    
            }
            else
            {
                std::cout << "Cannot make next move, passing" << std::endl;
                input *= -1;
                passed = 1;
                continue;
            }
            
        } while(!game_over(board) && passed < 2);
        
        score = scores(board);
        
        if(score[0] == 0 || score[0] < score[1])
        {
            std::cout << std::endl << "Game over! \u25CF  has won, " << "Score: \u25CB " << score[0] << " vs \u25CF " << score[1] << '.' << std::endl;    
        }
        else if(score[1] == 0 || score[0] > score[1])
        {
            std::cout << std::endl << "Game over! \u25CB has won, " << "Score: \u25CB " << score[0] << " vs \u25CF " << score[1] << '.' << std::endl;    
        }
        else std::cout << "Draw!" << std::endl;
        
        std::cout << std::endl << "Play again (y/n)?: ";
        std::cin >> playagain;
        
    } while(playagain != 'N' && playagain != 'n');
        
    return 0;
}