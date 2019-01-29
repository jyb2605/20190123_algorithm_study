#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
p 14502

*/

int N, M;

vector<vector<int>> map;
vector<pair<int, int>> virus;

int cnt;
int maxSafeSection;

void spreadVirus(int x, int y) {
	map[x][y] = 2;

	if (map[x - 1][y] == 0)
		spreadVirus(x - 1, y);
	if (map[x + 1][y] == 0)
		spreadVirus(x + 1, y);
	if (map[x][y -1] == 0)
		spreadVirus(x, y - 1);
	if (map[x][y + 1] == 0)
		spreadVirus(x, y + 1);
	
	return;
}

int countSafeSection() {
	int cnt = 0;
	
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			if (map[i][j] == 0)
				cnt++;
			else if (map[i][j] == 2)
				map[i][j] = 0;
		}
	}

	for (int i = 0; i < virus.size(); i++) {
		map[virus[i].first][virus[i].second] = 2;
	}

	return cnt;
}

void dfs(int x, int y) {
	if (map[x][y] != 0)
		return;

	cnt++;
	map[x][y] = 1;

	if (cnt == 3) {
		for (int i = 0; i < virus.size(); i++) {
			spreadVirus(virus[i].first, virus[i].second);
		}

		maxSafeSection = max(maxSafeSection, countSafeSection());

		cnt--;
		map[x][y] = 0;
		return;
	}

	for (int i = x; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			if (i == x && j == 1) {
				j = y + 1;
			}
			dfs(i, j);
		}
	}

	cnt--;
	map[x][y] = 0;
}

int main()
{
	std::ios::sync_with_stdio(false);

	cin >> N >> M;

	map = vector<vector<int>>(N + 2, vector<int>(M + 2, 1));

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus.push_back(make_pair(i, j));
			}
		}
	}

	cnt = 0;

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			dfs(i, j);
		}
	}

	cout << maxSafeSection << endl;


	return 0;
}

