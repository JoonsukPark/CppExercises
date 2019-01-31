#include<ctime>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cctype>
#include<cstring>
#include<vector>
#include<stdlib.h> 

using namespace std;

int if_rowsum_is_3(int x[3][3])
{
    int sum = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            sum += x[i][j];    
        }
        if (sum == 3) return 1;    
        else if (sum == -3) return -1;
        else sum = 0;
    }
    return sum;
}

int if_colsum_is_3(int x[3][3])
{
    int sum = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            sum += x[j][i];    
        }
        if (sum == 3) return 1;    
        else if (sum == -3) return -1;
        else sum = 0;
    }
    return sum;
}

int if_trace_is_3(int x[3][3])
{
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0; i<3; i++)
    {
        sum1 += x[i][i];
        sum2 += x[i][2-i];
    }
    if ((sum1 == 3) || (sum2 == 3)) return 1;
    else if ((sum1 == -3) || (sum2 == -3)) return -1;
    else return 0;
}

int check_if_win(int board[3][3])
{
    if ((if_rowsum_is_3(board) == 1) || (if_colsum_is_3(board) == 1) || (if_trace_is_3(board) == 1)) return 1;
    else if ((if_rowsum_is_3(board) == -1) || (if_colsum_is_3(board) == -1) || (if_trace_is_3(board) == -1)) return -1;    
    else return 0;
}

vector<int> check_winning_move(int board[3][3])
{
    int sum = 0;
    vector<int> output1 {};
    
    for(int i=0; i<3; i++)
    {
        sum = 0;
        for(int j=0; j<3; j++)
        {
            sum += board[i][j];
        }
        if (sum == -2)
        {
            for(int k=0; k<3; k++)
            {
                if (board[i][k] == 0)
                {
                    output1.push_back(i);
                    output1.push_back(k);
                    return output1;
                }
            }
        }
    }
    
    for(int i=0; i<3; i++)
    {
        sum = 0;
        for(int j=0; j<3; j++)
        {
            sum += board[j][i];
        }
        if (sum == -2)
        {
            for(int k=0; k<3; k++)
            {
                if(board[k][i]==0)
                {
                    output1.push_back(k);
                    output1.push_back(i);
                    return output1;
                }
            }
        }
    }

    sum = board[0][0]+board[1][1]+board[2][2];
    if (sum == -2)
    {
        for(int j=0; j<3; j++)
        {
            if (board[j][j] == 0)
            {
                output1.push_back(j);
                output1.push_back(j);
                return output1;
            }
        }
    }
    
    sum = board[0][2]+board[1][1]+board[2][0];
    if (sum == -2)
    {
        for(int j=0; j<3; j++)
        {
            if (board[j][2-j] == 0)
            {
                output1.push_back(j);
                output1.push_back(2-j);
                return output1;
            }
        }
    }
    
    for(int i=0; i<3; i++)
    {
        sum = 0;
        for(int j=0; j<3; j++)
        {
            sum += board[i][j];
        }
        if (sum == 2)
        {
            for(int k=0; k<3; k++)
            {
                if (board[i][k] == 0)
                {
                    output1.push_back(i);
                    output1.push_back(k);
                    return output1;
                }
            }
        }
    }
    
    for(int i=0; i<3; i++)
    {
        int sum = 0;
        for(int j=0; j<3; j++)
        {
            sum += board[j][i];
        }
        if (sum == 2)
        {
            for(int k=0; k<3; k++)
            {
                if (board[k][i] == 0)
                {
                    output1.push_back(k);
                    output1.push_back(i);
                    return output1;
                }
            }
        }
    }
    
    sum = board[0][0]+board[1][1]+board[2][2];
    
    for(int i=0; i<3; i++)
    {
        sum += board[i][i];
    }
    if (sum == 2)
    {
        for(int j=0; j<3; j++)
        {
            if (board[j][j] == 0)
            {
                output1.push_back(j);
                output1.push_back(j);
                return output1;
            }
        }
    }
    
    sum = board[0][2]+board[1][1]+board[2][0];
    
    if (sum == 2)
    {
        for(int j=0; j<3; j++)
        {
            if (board[j][2-j] == 0)
            {
                output1.push_back(j);
                output1.push_back(2-j);
                return output1;
            }
        }
    }

    output1 = {-1, -1};
    return output1;
}

int countzero(int board[3][3])
{
    int output = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i][j] == 0) output += 1;
        }
    }
    return output;
}

void nextmove(int board[3][3])
{
    vector<int> next = check_winning_move(board);
    vector<int> temp = {-1, -1};
    int zeros = 0;
    
    if (next != temp)
    {
        board[next[0]][next[1]] = -1;
        return;
    }
    else
    {
        int randnum;
        zeros = countzero(board);
        if(zeros > 1)
        {
            srand(static_cast<unsigned int>(time(0)));
            randnum = rand() % zeros;
        }
        else randnum = 0;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(board[i][j]==0)
                {
                    if(randnum == 0)
                    {
                        board[i][j] = -1;
                        return;
                    }
                    else randnum--;
                }
            }
        }
    }
}

int fullmoves(int board[3][3])
{
    int temp = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i][j] != 0) temp++;
        }
    }
    if(temp==9) return 1;
    else return 0;
}

int main()
{
    char selection = ' ';    
    do {
        
        const int rows = 3;
        const int cols = 3;
        int board[rows][cols] = {{0,0,0}, {0,0,0}, {0,0,0}};

        int input_row;
        int input_col;
        
        cout << endl;
        
        srand(static_cast<unsigned int>(time(0)));
        if(rand() % 2 == 1)
        {
            cout << "Player first! " << endl << endl;
        }
        else
        {
            cout << "Computer first! " << endl << endl;
            nextmove(board);
        }
            
        cout << "Current state of the board is: " << endl;
        
        for (int i = 0; i < cols; i++)
        {
            if (i > 0)
            {
                cout << "------------" << endl;
            }
            for (int j = 0; j < rows; j++) 
            {
                if(board[i][j] == 1)
                {
                    cout << " " << 'O' << " " << '|';
                }
                else if (board[i][j] == -1)
                {
                    cout << " " << 'X' << " " << '|';
                }
                else
                {
                    cout << " " << ' ' << " " << '|';
                }
                if (j == rows - 1)
                {
                    cout << endl;
                }
            }
        }

        while (true)
        {
            while(true)
            {
                cout << endl << "Which row? (99 to exit): ";
                
                cin >> input_row;
                
                if (input_row == 99)
                {
                    cout << endl << "Bye" << endl << endl;
                    return 0;
                }
                
                else if (!cin || input_row > rows || input_row < 1)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Not a valid input." << endl << endl;
                    continue;
                }
                
                cout << "Which column? (99 to exit): ";
                cin >> input_col;
                
                if (input_col == 99)
                {
                    cout << endl << "Bye" << endl << endl;
                    return 0;
                }
                
                else if (!cin || input_col > cols || input_col < 1)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Not a valid input." << endl << endl;
                    continue;
                }
                
                cout << endl;

                if (board[input_row - 1][input_col - 1] == -1 || board[input_row - 1][input_col - 1] == 1)
                {
                    cout << "That cell is filled, try again! " << endl;
                }
                if (board[input_row - 1][input_col - 1] == 0 && input_row <= rows && input_col <= cols)
                {
                    break;
                }
            }

            board[input_row - 1][input_col - 1] = 1;
            
            if(!fullmoves(board)) nextmove(board);
            
            cout << "Current state of the board is: " << endl;
            
            for (int i = 0; i < cols; i++)
            {
                if (i > 0)
                {
                    cout << "------------" << endl;
                }
                for (int j = 0; j < rows; j++) 
                {
                    if(board[i][j] == 1)
                    {
                        cout << " " << 'O' << " " << '|';
                    }
                    else if (board[i][j] == -1)
                    {
                        cout << " " << 'X' << " " << '|';
                    }
                    else
                    {
                        cout << " " << ' ' << " " << '|';
                    }
                    if (j == rows - 1)
                    {
                        cout << endl;
                    }
                }
            }
            
            cout << endl;
            
            if (check_if_win(board) == 1)
            {
                do {
                    for(int i=0; i<rows; i++)
                    {
                        for(int j=0; j<cols; j++)
                        {
                            board[i][j] = 0;
                        }
                    }
                    cout << "\'O\'" << " has won! Play again (y/n)? ";
                    cin >> selection;
                } while (selection != 'y' && selection != 'Y' && selection != 'n' && selection != 'N');
                break;
            }

            else if (check_if_win(board) == -1)
            {
                do {
                    for(int i=0; i<rows; i++)
                    {
                        for(int j=0; j<cols; j++)
                        {
                            board[i][j] = 0;
                        }
                    }
                    cout << "\'X\'" << " has won! Play again (y/n)? ";
                    cin >> selection;
                } while (selection != 'y' && selection != 'Y' && selection != 'n' && selection != 'N');
                break;
            }
            
            if(fullmoves(board))
            {
                do {
                    for(int i=0; i<rows; i++)
                    {
                        for(int j=0; j<cols; j++)
                        {
                            board[i][j] = 0;
                        }
                    }
                    cout << "Draw! Play again (y/n)? ";
                    cin >> selection;
                } while (selection != 'y' && selection != 'Y' && selection != 'n' && selection != 'N');
                break;
            }
        }
	} while(selection != 'n' && selection != 'N');
	return 0;
}