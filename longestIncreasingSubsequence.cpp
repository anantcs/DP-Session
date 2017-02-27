#include <iostream>
#include <vector>
using namespace std;

int main() {
	int i, j, len;
	vector<int> nums = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
	len = nums.size();
	vector<int> result(len, 1);
	result[0] = 1;
	for(i=1; i<len; i++) {
		for(j=0; j < i; j++) {
			if(nums[i] > nums[j])
				result[i] = max(result[i], result[j] + 1);
		}
	}
	cout << result[len-1] << endl;
	return 0;
}
