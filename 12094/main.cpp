#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

constexpr int searchDepth = 10;

void printBoard(const vector<vector<int>> &board) {
    for (const auto &row : board) {
        for (const auto &cell : row) {
            cout << cell << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isEqual(vector<vector<int>> & boardA, vector<vector<int>> & boardB)
{
    bool isSame = true;
    int n = boardA.size();

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(boardA[i][j] != boardB[i][j])
            {
                isSame = false;
                break;
            }
        }

        if(isSame == false)
            break;
    }

    return isSame;

}

int fall(vector<vector<int>> & board, int direction)
{
    // 0 : down, 1 : right, 2 : up, 3 : left
    int n = board.size();
    int max = -1;

    for(int i=0;i<n;++i)
    {
        list<int> line;
        list<int> newLine;
        for(int j=0;j<n;++j)
        {
            if(direction % 2 == 1 && board[i][j] != 0)
            {
                line.push_back(board[i][j]);
            }

            else if(direction % 2 == 0 && board[j][i] != 0)
            {
                line.push_back(board[j][i]);
            }

        }        

        while(!line.empty())
        {
            int top;
            if(direction / 2 == 1)
            {
                top = line.front();
                line.pop_front();

                
                if(!line.empty() && top == line.front())
                {
                    newLine.push_back(top * 2);
                    line.pop_front();
                }
                else
                {
                    newLine.push_back(top);
                }
            }
            else
            {
                top = line.back();
                line.pop_back();

                
                if(!line.empty() && top == line.back())
                {
                    newLine.push_front(top * 2);
                    line.pop_back();
                }
                else
                {
                    newLine.push_front(top);
                }
            }
        }

        if(direction / 2 == 1)
        {
            while(newLine.size() < n)
            {
                newLine.push_back(0);
            }
        }
        
        else
        {
            while(newLine.size() < n) 
            {                
                newLine.push_front(0);
            }
        }

        int j = 0;
        for(auto item : newLine)
        {
            if(max < item) max = item;

            if(direction % 2 == 1)
            {
                board[i][j] = item;
            }
            else
            {
                board[j][i] = item;
            }
            ++j;
        }
    }

    return max;
}

bool roll(vector<vector<int>> board)
{
    vector<vector<int>> newBoard(board);
    bool isSame = true;
    int n = board.size();

    for(int i=0;i<4;++i)
    {
        fall(newBoard, i);
    }

    return isEqual(board, newBoard);
}

int biggest(vector<vector<int>> & board)
{
    int result = 0;
    for(auto & line : board)
    {
        for(auto & item : line)
        {
            if(result < item) result = item;
        }
    }

    return result;
}

int simulate(vector<vector<int>> & board, int searchDepth) {
    if (searchDepth == 0 || roll(board)) 
    {
        return biggest(board);
    }
    
    int max = biggest(board);
    for(int i=0;i<4;++i) {
        vector<vector<int>> newBoard(board);
        int localMax = fall(newBoard, i);
        
        if(localMax != -1) {
            int result = simulate(newBoard, searchDepth-1);
            if(max < result) max = result;
        }
    }
    return max;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cin >> board[i][j];
        }
    }

    cout << simulate(board, searchDepth) << endl;

    return 0;
}