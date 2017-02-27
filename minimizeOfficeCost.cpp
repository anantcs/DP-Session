#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

void print_vector(const vector<vector<int>>& cost) {
	int i, j;
	for(i=0; i<cost.size(); i++) {
		for(j=0; j<cost[0].size(); j++)
			cout << cost[i][j] << "\t";
		cout << endl;
	}
	return;
}

int main() {
	int i, j, m, len;
	m = 2;
	vector<int> new_york = {1, 6, 9, 20, 3, 5, 10, 20, 50, 1, 1, 1, 1, 60, 70, 90, 100, 1, 1, 10};
	vector<int> seattle = {10, 23, 5, 21, 8, 50, 10, 20, 1, 50, 80, 10, 10, 60, 40, 9000, 1, 50, 40, 1};
	vector<int> sum_ny(new_york);
	vector<int> sum_seattle(seattle);
	int temp_cost_ny, temp_cost_seattle;
	len = new_york.size();
	vector<vector<int>> cost(2, vector<int>(len, 0));
	vector<vector<int>> path(2, vector<int>(len, 0));
	vector<string> result;
	
	//find the cumulative sum of new york and seattle
	for(i=1; i<sum_ny.size(); i++)
		sum_ny[i] += sum_ny[i-1];
	for(i=1; i<sum_seattle.size(); i++)
		sum_seattle[i] += sum_seattle[i-1];
		
	cost[0] = new_york;
	cost[1] = seattle;
	
	for(i=1; i<len; i++) {
		temp_cost_ny = numeric_limits<int>::max();
		temp_cost_seattle = numeric_limits<int>::max();
		for(j=0; j<i; j++) {
			temp_cost_ny = min(temp_cost_ny, cost[1][j]+sum_ny[i-1]-sum_ny[j]+m);
			temp_cost_seattle = min(temp_cost_seattle, cost[0][j] + sum_seattle[i-1]-sum_seattle[j]+m);
		}
		cost[0][i] += min(temp_cost_ny, cost[0][i-1]);
		//1-leftdown, 2-left, 3-leftup
		if(temp_cost_ny == min(temp_cost_ny, cost[0][i-1]))
			path[0][i] = 1;
		else
			path[0][i] = 2;
		cost[1][i] += min(temp_cost_seattle, cost[1][i-1]);
		if(temp_cost_seattle == min(temp_cost_seattle, cost[1][i-1]))
			path[1][i] = 3;
		else
			path[1][i] = 2;
	}

	cout << min(cost[0][len-1], cost[1][len-1]) << endl;
	
	i = len-1;
	if(cost[0][len-1] == min(cost[0][len-1], cost[1][len-1]))	j = 0;
	else	j = 1;
		
	while(i>-1) {
		if(j == 0)
			result.push_back("NY");
		else
			result.push_back("SF");
		switch(path[j][i]) {
			case 1:	j = 1;
					break;
			case 2:
					break;
			case 3:	j = 0;
					break;
		}
		i--;
	}
	
	reverse(result.begin(), result.end());
	for(i=0; i<result.size(); i++)
		cout << result[i] << " ";
	cout << endl;
	return 0;
}
