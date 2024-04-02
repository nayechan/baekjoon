#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Node;

class Connection{
	shared_ptr<Node> from;
	shared_ptr<Node> to;
	int distance;

public:
	Connection(shared_ptr<Node> from, shared_ptr<Node> to, int distance) 
        : from(from), to(to), distance(distance) {}

	shared_ptr<Node> GetFrom(){return from;}
	shared_ptr<Node> GetTo(){return to;}

	int GetDistance()
	{
		return distance;
	}
};

class Node{
	int value;
	vector<shared_ptr<Connection>> connections;

public:
	Node(int value) : value(value){}

    std::shared_ptr<Node> shared_from_this() {
        return std::shared_ptr<Node>(this);
    }

	int GetValue(){return value;}

	void Connect(shared_ptr<Node> node, int distance){
		ConnectSingleDirection(node, distance);
		node->Connect(shared_from_this(), distance);
	}

	void ConnectSingleDirection(shared_ptr<Node> node, int distance){
		connections.push_back(make_shared<Connection>(shared_from_this(), &node, distance));
	}

	int GetLongestLength(bool ** visited)
	{
		int visition = 0;
		int maxDist = 0;
		
		*visited[value] = true;

		for (auto && connection : connections)
		{
			int to = connection->GetTo()->GetValue();

			if(!*visited[to])
			{
				int dist = connection->GetTo()->GetLongestLength(visited);
				if(maxDist < dist) maxDist = dist;
			}

		}
		
		*visited[value] = false;

		return maxDist;
	}
};

int main()
{
	int inputCount;

	cin >> inputCount;

	Node ** node = new Node*[inputCount+1];
	
	for(int i=0; i<=inputCount; ++i)
	{
		node[i] = new Node(i);
	}

	for(int i=1; i<=inputCount; ++i)
	{
		int from, to, distance;

		cin >> from >> to >> distance;

		node[from]->Connect(make_shared<Node>(node[to]), distance);
	}

	int max = -1;
	for(int i=1; i<=inputCount; ++i)
	{
		bool * visited = new bool[inputCount+1];
	
		for(int j=0; j<=inputCount; ++j)
		{
			visited[j] = false;
		}

		int length = node[i]->GetLongestLength(&visited);

		if (max < length) max = length;

		delete[] visited;
	}

	cout << max << endl;

	return 0;
}