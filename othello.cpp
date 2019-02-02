#include<iostream>
#include<vector>
#include<cctype>
#include<array>

const int board_size = 6;
std::array<std::array<int, board_size>, board_size> board;

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

int validate_right(int input, int input_row, int input_col)
{
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

int validate_left(int input, int input_row, int input_col)
{
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

int validate_up(int input, int input_row, int input_col)
{
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

int validate_down(int input, int input_row, int input_col)
{
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

int validate_upperleft(int input, int input_row, int input_col)
{
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

int validate_upperright(int input, int input_row, int input_col)
{
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

int validate_lowerleft(int input, int input_row, int input_col)
{
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

int validate_lowerright(int input, int input_row, int input_col)
{
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

void execute_right(int input, int input_row, int input_col, int rightlim)
{
    for(int k=input_col-1; k<rightlim; k++)
    {
        board[input_row-1][k] = input;
    }
}

void execute_left(int input, int input_row, int input_col, int leftlim)
{
    for(int k=leftlim+1; k<input_col; k++)
    {
        board[input_row-1][k] = input;
    }
}

void execute_up(int input, int input_row, int input_col, int lowerlim)
{
    for(int k=lowerlim+1; k<input_row; k++)
    {
        board[k][input_col-1] = input;
    }
}

void execute_down(int input, int input_row, int input_col, int upperlim)
{
    for(int k=input_row-1; k<upperlim; k++)
    {
        board[k][input_col-1] = input;
    }
}

void execute_upperleft(int input, int input_row, int input_col, int upperleftlim)
{
    int j = input_col - 1;
    for(int i=input_row - 1; i > upperleftlim; i--)
    {
        board[i][j] = input;
        j--;
    }
}

void execute_upperright(int input, int input_row, int input_col, int upperrightlim)
{
    int j = input_col - 1;
    for(int i=input_row - 1; i > upperrightlim; i--)
    {
        board[i][j] = input;
        j++;
    }
}

void execute_lowerleft(int input, int input_row, int input_col, int lowerleftlim)
{
    int j = input_col - 1;
    for(int i = input_row - 1; i < lowerleftlim; i++)
    {
        board[i][j] = input;
        j--;
    }
}

void execute_lowerright(int input, int input_row, int input_col, int lowerrightlim)
{
    int j = input_col - 1;
    for(int i = input_row - 1; i < lowerrightlim; i++)
    {
        board[i][j] = input;
        j++;
    }
}

int game_over()
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

std::vector<int> scores()
{
    int whites = 0;
    int blacks = 0;
    std::vector<int> output(2);
    
    for(int i=0; i<board_size; i++)
    {
        for(int j=0; j<board_size; j++)
        {
            if(board[i][j]==1) whites += 1;
            else if(board[i][j]==-1) blacks += 1;
        }
    }
    output[0] = whites;
    output[1] = blacks;
    return output;
}

int main()
{
    std::cout << std::endl << "Othello C++ version 1.0" << std::endl << std::endl;
    
    int input_row;
    int input_col;
    
    int rightlim;
    int leftlim;
    int upperlim;
    int lowerlim;
    
    int upperleftlim;
    int upperrightlim;
    int lowerleftlim;
    int lowerrightlim;
    
    int input = 1;
    int moved = 0;
    int passed = 0;
    int move_possible = 0;
    
    char playagain;
    std::vector<int> score(2);
    
    do
    {
        init_board();
        draw_board();

        do
        {
            moved = 0;
            move_possible = 0;
            
            for(int i=1; i<=board_size; i++)
            {
                for(int j=1; j<=board_size; j++)
                {
                    if(board[i-1][j-1] == 0)
                    {
                        if(validate_right(input, i, j) != -1 ||
                        validate_left(input, i, j) != -1 ||
                        validate_up(input, i, j) != -1 ||
                        validate_down(input, i, j) != -1 ||
                        validate_upperleft(input, i, j) != -1 ||
                        validate_upperright(input, i, j) != -1 ||
                        validate_lowerleft(input, i, j)  != -1 ||
                        validate_lowerright(input, i, j)  != -1)
                        {
                            move_possible = 1;
                            break;
                        }
                    }
                }
            }
            
            if(move_possible == 0)
            {
                std::cout << "There is no possible move! Passing this turn..." << std::endl;
                passed += 1;
                input *= -1;
                continue;
            }

            if(input == 1) std::cout << "\u25CB \'s turn!" << std::endl;
            else std::cout << "\u25CF \'s turn!" << std::endl;
                
            std::cout << std::endl << "Input row (0: pass, 99=quit): ";
            std::cin >> input_row;
            
            if(input_row == 99) return 0;
            else if(input_row == 0)
            {
                passed += 1;
                input *= -1;
                continue;
            }
            
            std::cout << std::endl << "Input col (0: pass, 99= quit): ";
            std::cin >> input_col;
            if(input_col == 99) return 0;
            else if(input_row == 0)
            {
                passed += 1;
                input *= -1;
                continue;
            }
            std::cout << std::endl;
            
            if(board[input_row-1][input_col-1] != 0)
            {
                std::cout << "Invalid move" << std::endl << std::endl;
                continue;
            }
            
            if(input_col != board_size)
            {
                rightlim = validate_right(input, input_row, input_col);
                if(rightlim != -1)
                {
                    execute_right(input, input_row, input_col, rightlim);
                    moved = 1;
                    passed = 0;
                }
            }
            
            if(input_col != 1)
            {
                leftlim = validate_left(input, input_row, input_col);
                if(leftlim != -1)
                {
                    execute_left(input, input_row, input_col, leftlim);
                    moved = 1;
                    passed = 0;
                }
            }

            if(input_row != 1)
            {
                lowerlim = validate_up(input, input_row, input_col);
                if(lowerlim != -1)
                {
                    execute_up(input, input_row, input_col, lowerlim);
                    moved = 1;
                    passed = 0;
                }
            }
            
            if(input_row != board_size)
            {
                upperlim = validate_down(input, input_row, input_col);
                if(upperlim != -1)
                {
                    execute_down(input, input_row, input_col, upperlim);
                    moved = 1;
                    passed = 0;
                }
            }
            
            if(input_row != 1 && input_col != 1)
            {
                upperleftlim = validate_upperleft(input, input_row, input_col);
                if(upperleftlim != -1)
                {
                    execute_upperleft(input, input_row, input_col, upperleftlim);
                    moved = 1;
                    passed = 0;
                }
            }
            
            if(input_row != 1 && input_col != board_size)
            {
                upperrightlim = validate_upperright(input, input_row, input_col);
                if(upperrightlim != -1)
                {
                    execute_upperright(input, input_row, input_col, upperrightlim);
                    moved = 1;
                    passed = 0;
                }
            }

            if(input_row != board_size && input_col != board_size)
            {
                lowerrightlim = validate_lowerright(input, input_row, input_col);
                if(lowerrightlim != -1)
                {
                    execute_lowerright(input, input_row, input_col, lowerrightlim);
                    moved = 1;
                    passed = 0;
                }
            }
            
            if(input_row != board_size && input_col != 1)
            {
                lowerleftlim = validate_lowerleft(input, input_row, input_col);
                if(lowerleftlim != -1)
                {
                    execute_lowerleft(input, input_row, input_col, lowerleftlim);
                    moved = 1;
                    passed = 0;
                }
            }
            
            if(moved != 1)
            {
                std::cout << "Invalid move. " <<std::endl;
                draw_board();
                continue;
            }
            
            else
            {
                draw_board();    
                input *= -1;
                score = scores();
                std::cout << std::endl << "Score: " << score[0] << " vs " << score[1] << ". ";    
            }
            
        } while(!game_over() && passed < 2);
        
        score = scores();
        
        if(score[0] == 0 || score[0] < score[1])
        {
            std::cout << std::endl << "Game over! \u25CF  has won, " << "Score: \u25CB " << score[0] << " vs \u25CF " << score[1] << '.' << std::endl;    
        }
        else if(score[1] == 0 || score[0] > score[1])
        {
            std::cout << std::endl << "Game over! \u25CB has won, " << "Score: \u25CB " << score[0] << " vs \u25CF " << score[1] << '.' << std::endl;    
        }
        else std::cout << "Draw!" << std::endl;
        
        std::cout << std::endl << "Play again (y/n)?: " << std::endl;
        std::cin >> playagain;
        
    } while(playagain != 'N' && playagain != 'n');
        
    return 0;
}