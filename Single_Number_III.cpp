#include<iostream>
#include<vector>
using namespace std;
/*
	discription:

	Given an array of numbers nums, in which exactly two elements appear only once and all 
	
	the other elements appear exactly twice. Find the two elements that appear only once.

	For example:

	Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

	Note:

	The order of the result is not important. So in the above example, [5, 3] is also correct.

	Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

	solution:

	Once again, we need to use XOR to solve this problem.But this time, we need to do it in two passes :

	In the first pass, we XOR all elements in the array, and get the XOR of the two numbers we need to find.
	
	Note that since the two numbers are distinct, so there must be a set bit(that is, the bit with value '1') 
	
	in the XOR result.Find out an arbitrary set bit(for example, the rightmost set bit).

	In the second pass, we divide all numbers into two groups, one with the aforementioned bit set, another 
	
	with the aforementinoed bit unset.Two different numbers we need to find must fall into thte two distrinct
	
	groups.XOR numbers in each group, we can find a number in either group.

	Complexity :

	Time : O(n)

	Space : O(1)
*/
vector<int> singleNumber(vector<int>& nums) {
	int xorAll = 0;
	int ansX = 0, ansY = 0;
	int filter = 1;
	int i;
	vector<int> ans(2,0);
	for ( i = 0;i < nums.size();i++)
		xorAll ^= nums[i];
	i = 0;
	while ((filter & xorAll) == 0)
		filter <<= 1;

	for (i = 0;i < nums.size();i++)
	{
		if (filter & nums[i])
			ansX ^= nums[i];
	}
	ansY = ansX ^ xorAll;
	ans[0] = ansX;
	ans[1] = ansY;
	return ans;
}
int main()
{
	vector<int>nums(2,0);
	nums[0] = 0;
	nums[1] = 1;
	singleNumber(nums);
	return 0;
}