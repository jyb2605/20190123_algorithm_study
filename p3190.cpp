#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
snake
p 3190
simulation
*/

int N, K, L;
int x, y;
char _dir;

char curDir;
int headX, headY, tailX, tailY;

vector<vector<char>> map;

queue<int> sec;
queue<char> dir;

int curSec = 0;


void print() {
	cout << "####################################" << endl;
	cout << "curSec: " << curSec << endl;
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
}

char changeDir(char dir) {
	if (dir == 'L') {
		switch(curDir){
		case 'R':
			return 'U';
		case 'U':
			return 'L';
		case 'L':
			return 'D';
		case 'D':
			return 'R';
		}
	}
	else {
		switch (curDir) {
		case 'R':
			return 'D';
		case 'U':
			return 'R';
		case 'L':
			return 'U';
		case 'D':
			return 'L';
		}
	}
}

void nextHead() {
	switch (curDir) {
	case 'R':
		headY++;
		return;
	case 'U':
		headX--;
		return;
	case 'L':
		headY--;
		return;
	case 'D':
		headX++;
		return;
	}
}


void nextTail() {
	switch (map[tailX][tailY]) {
	case 'R':
		map[tailX][tailY] = 'E';
		tailY++;
		return;
	case 'U':
		map[tailX][tailY] = 'E';
		tailX--;
		return;
	case 'L':
		map[tailX][tailY] = 'E';
		tailY--;
		return;
	case 'D':
		map[tailX][tailY] = 'E';
		tailX++;
		return;
	}
}


int main()
{
	std::ios::sync_with_stdio(false);

	cin >> N >> K;

	// map initialize
	map = vector<vector<char>>(N + 2, vector<char>(N + 2, 'E'));

	// construct wall
	map[0] = vector<char>(N + 2, 'W');
	map[N+1] = vector<char>(N + 2, 'W');

	for (int i = 1; i < N + 1; i++) {
		map[i][0] = 'W';
		map[i][N+1] = 'W';
	}

	// construct apple
	for (int i = 0; i < K; i++) {
		cin >> x >> y;
		map[x][y] = 'A';
	}

	cin >> L;

	for (int i = 0; i < L; i++) {
		cin >> x >> _dir;
		sec.push(x);
		dir.push(_dir);
	}

	// init snake
	headX = headY = tailX = tailY = 1;
	map[1][1] = 'R';
	curDir = 'R';

	while (true) {
		if (curSec != 0) {
			// move head
			nextHead();

			// find Apple
			if (map[headX][headY] == 'A') {
				map[headX][headY] = curDir;
				// print();

				// check changing direction
				if (!sec.empty() && curSec == sec.front()) {
					curDir = changeDir(dir.front());
					sec.pop();
					dir.pop();
					map[headX][headY] = curDir;
				}

				curSec++;
				continue;
			}

			// crush Wall or Body
			if (map[headX][headY] != 'E') {
				break;
			}

			// set head value
			map[headX][headY] = curDir;

			// move and set tail
			nextTail();

			// print();

		}

		// check changing direction
		if (!sec.empty() && curSec == sec.front()) {
			curDir = changeDir(dir.front());
			sec.pop();
			dir.pop();
			map[headX][headY] = curDir;
		}

		curSec++;
	}

	cout << curSec<< endl;

	return 0;
}

