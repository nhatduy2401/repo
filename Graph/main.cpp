#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename);
vector<vector<int>> convertListToMatrix(const string& filename);
bool isDirected(const vector<vector<int>>& adjMatrix);
int countVertices(const vector<vector<int>>& adjMatrix);
int countEdges(const vector<vector<int>>& adjMatrix);
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix);
bool isCompleteGraph(const vector<vector<int>>& adjMatrix);
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix);
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix);
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix);
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix);
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix);
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);

vector<vector<int>> convertMatrixToList(const string& filename) {
	ifstream inFile(filename);
	int n;
	inFile >> n;
	vector<vector<int>> matrix(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			inFile >> matrix[i][j];
		}
	}
	vector<vector<int>> list(n);
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				count++;
			}
		}
		if (count == 0) {
				list[i].push_back(0);
		}
		else {
			list[i].push_back(count);
			for (int j = 0; j < n; j++) {
			if (matrix[i][j] != 0) {
				list[i].push_back(j);
				}
			}
		}
	}
	return list;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream inFile(filename);
	int n;
	inFile >> n;
	inFile.ignore();
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		string line;
		getline(inFile, line);
		stringstream dong(line);
		int k;
		dong >> k;
		int v;
		for (int j = 0; j < k; j++) {
			dong >> v;
			matrix[i][v] = 1;
		}
	}
	return matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
	int count = 0;
	if (isDirected(adjMatrix)) {
		for (int i = 0; i < adjMatrix.size(); i++) {
			for (int j = 0; j < adjMatrix.size(); j++) {
				if (adjMatrix[i][j] != 0) {
					count++;
				}
			}
		}
		return count;
	}
	else {
		for (int i = 0; i < adjMatrix.size(); i++) {
			if (adjMatrix[i][i] != 0) {
				count++;
			}
			for (int j = i + 1; j < adjMatrix.size(); j++) {
				if (adjMatrix[i][j] != 0) {
					count++;
				}
			}
		}
		return count;
	}
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	vector<int> isolated;
	for (int i = 0; i < adjMatrix.size(); i++) {
		bool isIsolated = true;
		for (int j = 0; j < adjMatrix.size(); j++) {
			if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
				isIsolated = false;
				break;
			}
		}
		if (isIsolated) {
			isolated.push_back(i);
		}
	}
	return isolated;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	for (int i = 0; i < adjMatrix.size(); i++) {
		if (adjMatrix[i][i] != 0) {
			return false;
		}
		for (int j = i + 1; j < adjMatrix.size(); j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return false;
			}
			if (adjMatrix[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	queue<int> q;
	for (int start = 0; start < n; start++) {
		if (color[start] == -1) {
			q.push(start);
			color[start] = 0;
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int v = 0; v < n; v++) {
					if (adjMatrix[u][v] == 1) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
							q.push(v);
						}
						else if (color[v] == color[u]) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	queue<int> q;
	for (int start = 0; start < n; start++) {
		if (color[start] == -1) {
			q.push(start);
			color[start] = 0;
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int v = 0; v < n; v++) {
					if (adjMatrix[u][v] == 1) {
						if (color[v] == -1) {
							color[v] = 1 - color[u];
							q.push(v);
						}
						else if (color[v] == color[u]) {
							return false;
						}
					}
				}
			}
		}
	}
	for (int u = 0; u < n; u++) {
		for (int v = u + 1; v < n; v++) {
			if (color[u] == color[v]) {
				if (adjMatrix[u][v] == 1) {
					return false;
				}
			}
			else {
				if (adjMatrix[u][v] == 0) {
					return false;
				}
			}
		}
	}
	return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> undirectedGraph(n, vector<int>(n, 0));
	for (int u = 0; u < n; u++) {
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] == 1) {
				undirectedGraph[u][v] = undirectedGraph[v][u] = 1;
			}
		}
	}
	return undirectedGraph;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> complementGraph(n, vector<int>(n, 0));
	for (int u = 0; u < n; u++) {
		complementGraph[u][u] = 0;
		for (int v = u + 1; v < n; v++) {
			if (adjMatrix[u][v] == 0) {
				complementGraph[u][v] = complementGraph[v][u] = 1;
			}
			else {
				complementGraph[u][v] = complementGraph[v][u] = 0;
			}
		}
	}
	return complementGraph;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> graph = adjMatrix;
	int start = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] == 1) {
				start = i;
				
				break;
			}
		}
	}
	if (start == -1) {
		return {};
	}
	vector<int> circuit;
	vector<int> currPath;
	currPath.push_back(start);
	while (!currPath.empty()) {
		int curr = currPath.back();
		bool edge = false;
		for (int next = 0; next < n; next++) {
			if (graph[curr][next] == 1) {
				graph[curr][next] = graph[next][curr] = 0;
				currPath.push_back(next);
				edge = true;
				break;
			}
		}
		if (!edge) {
			circuit.push_back(currPath.back());
			currPath.pop_back();
		}
	}
	reverse(circuit.begin(), circuit.end());
	return circuit;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	stack<int> s;
	s.push(start);
	while (!s.empty()) {
		int u = s.top();
		s.pop();
		if (!visited[u]) {
			visited[u] = true;
			for (int v = n - 1; v >= 0; v--) {
				if (adjMatrix[u][v] == 1 && !visited[v]) {
					tree[u][v] = tree[v][u] = 1;
					s.push(v);
				}
			}
		}
	}
	return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	queue<int> q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] == 1 && !visited[v]) {
				visited[v] = true;
				tree[u][v] = tree[v][u] = 1;
				q.push(v);
			}
		}
	}
	return tree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	if (u == v) {
		return true;
	}
	vector<bool> visited(v, false);
	stack<int> s;
	s.push(u);
	while (!s.empty()) {
		int curr = s.top();
		s.pop();
		if (curr = v) {
			return true;
		}
		if (!visited[curr]) {
			visited[curr] = true;
			for (int next = 0; next < n; next++) {
				if (adjMatrix[curr][next] == 1 && !visited[next]) {
					s.push(next);
				}
			}
		}
	}
	return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX);
	vector<int> parent(n, -1);
	vector<bool> visited(n, false);
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dist[start] = 0;
	pq.push({ 0,start });
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		if (visited[u]) {
			continue;
		}
		visited[u] = true;
		if (u == end) {
			break;
		}
		for (int v = 0; v < n; v++) {
			int w = adjMatrix[u][v];
			if (w > 0 && w != INT_MAX) {
				if (dist[u] + w < dist[v] && !visited[v]) {
					dist[v] = dist[u] + w;
					parent[v] = u;
					pq.push({ dist[v],v });
				}
			}
		}
	}
	if (dist[end] == INT_MAX) {
		return {};
	}
	vector<int> path;
	for (int curr = end; curr != -1; curr = parent[curr]) {
		path.push_back(curr);
	}
	reverse(path.begin(), path.end());
	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX);
	vector<int> parent(n, -1);
	dist[start] = 0;
	for (int i = 0; i < n; i++) {
		bool up = false;
		for (int u = 0; u < n; u++) {
			if (dist[u] == INT_MAX) {
				continue;
			}
			for (int v = 0; v < n; v++) {
				int w = adjMatrix[u][v];
				if (w != 0 && w != INT_MAX) {
					if (dist[u] + w < dist[v]) {
						dist[v] = dist[u] + w;
						parent[v] = u;
						up = true;
					}
				}
			}
		}
		if (!up) {
			break;
		}
	}
	for (int u = 0; u < n; u++) {
		if (dist[u] == INT_MAX) {
			continue;
		}
		for (int v = 0; v < n; v++) {
			int w = adjMatrix[u][v];
			if (w != 0 && w != INT_MAX) {
				if (dist[u] + w < dist[v]) {
					return {};
				}
			}
		}
	}
	if (dist[end] == INT_MAX) {
		return {};
	}
	vector<int> path;
	for (int curr = end; curr != -1; curr = parent[curr]) {
		path.push_back(curr);
	}
	reverse(path.begin(), path.end());
	return path;
}