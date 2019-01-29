#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
p 15686

*/

class chickenDistance;

int N, M;
vector<pair<int, int>> house;
vector<vector<chickenDistance>> distances;

vector<pair<int, int>> shop;
vector<int> drop;

int shopNumber;
int minDistance;

class chickenDistance {
public:
	int x, y, distance;

	chickenDistance(int x, int y, int distance) {
		this->x = x;
		this->y = y;
		this->distance = distance;
	}

	bool operator<(chickenDistance& a) {
		return (this->distance < a.distance);
	}
};

void dfs(int idx) {
	shopNumber--;
	drop.push_back(idx);

	if (shopNumber == M) {

	}

	for (int i = idx + 1; i < shop.size(); i++) {
		dfs(i);
	}

	shopNumber++;
	for (vector<int>::iterator ptr = drop.begin(); ptr != drop.end(); ptr++) {
		if (*ptr == idx) {
			drop.erase(ptr);
			break;
		}
	}
}

int calcWholeDistance() {
	int num = 0;

	for (int i = 0; i < distances.size(); i++) {
		for (int j = 0; j < distances[i].size(); j++) {
			if(!isDrop(distances[i][j].x, distances[i][j].y))
		}
	}
}

bool isDrop(int x, int y) {
	for (int i = 0; i < drop.size(); i++) {
		if (shop[drop[i]].first == x && shop[drop[i]].second == y)
			return true;
	}

	return false;
}

int main()
{
	std::ios::sync_with_stdio(false);

	cin >> N >> M;

	int info;

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cin >> info;
			if (info == 1)
				house.push_back(make_pair(i, j));
			else if (info == 2)
				shop.push_back(make_pair(i, j));
		}
	}

	for (int i = 0; i < house.size(); i++) {
		vector<chickenDistance> tmpV;
		for (int j = 0; j < shop.size(); j++) {
			chickenDistance tmp(shop[j].first, shop[j].second, (abs(house[i].first - shop[j].first) + abs(house[i].second - shop[j].second)));
			tmpV.push_back(tmp);
		}
		sort(tmpV.begin(), tmpV.end());
		distances.push_back(tmpV);
	}

	shopNumber = shop.size();
	minDistance = 1e9;

	for (int i = 0; i < shop.size(); i++) {
		dfs(i);
	}

	return 0;
}
