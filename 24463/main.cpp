#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<bool>> data(n, vector<bool>(m, false));
    vector<vector<bool>> result(data);

    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));

    // to distinct unassigned position using {-1, -1}
    pair<int,int> start = {-1, -1}, end = {-1, -1};

    for(int row=0;row<n;++row)
    {
        string input;
        cin >> input;

        int column = 0;
        for(char ch : input)
        {
            data[row][column] = (ch == '+');

            if(row == 0 || row == n-1 || column == 0 || column == m-1)
            {
                if(ch == '.')
                {
                    if(start.first < 0)
                        start = {row, column};
                    else
                        end = {row, column};
                }
            }
            ++column;
        }
    }

    queue<pair<int,int>> targetPostions;
    const vector<pair<int,int>> delta = {{0,1},{0,-1},{1,0},{-1,0}};

    targetPostions.push(start);

    bool found = false;

    while(!targetPostions.empty() && !found)
    {
        int count = targetPostions.size();

        for(int round = 1; round <= count; ++round)
        {
            pair<int,int> element = targetPostions.back();
            for(const pair<int,int> & d : delta)
            {
                pair<int,int> targetPos = {
                    element.first + d.first, 
                    element.second + d.second
                };

                if(targetPos.first < 0 || targetPos.first >= n)
                    continue;
                
                if(targetPos.second < 0 || targetPos.second >= m)
                    continue;

                if(parent[targetPos.first][targetPos.second].first != -1)
                    continue;

                targetPostions.push(targetPos);
                parent[targetPos.first][targetPos.second] = {element.first, element.second};

                if(targetPos == end)
                {
                    found = true;
                    break;
                }
            }

            if(found)
            {
                break;
            }            
        }
    }

    vector<pair<int,int>> path;
    path.push_back(end);

    cout << end.first << ", " <<  end.second << endl;

    while(path.back() != start)
    {
        cout << path.back().first << ", " <<  path.back().second << endl;
        path.push_back(parent[end.first][end.second]);
    }
    

    return 0;
}