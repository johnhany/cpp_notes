#include <iostream>
#include <algorithm>
#include <deque>
#include <iterator>
#include <list>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    int Partition(vector<int>& input, int start, int end)
    {
        if(input.empty() || start>end) return -1;
        int temp = input[end];
        int j = start - 1;
        for(int i=start;i<end;++i){
            if(input[i]<=temp){
                ++j;
                if(i!=j) swap(input[i],input[j]);
            }
        }
        swap(input[j+1],input[end]);
        return (j+1);
    }

    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        if (input.empty() || k <= 0 || k > input.size()) return vector<int>{};
        int low = 0, high = input.size()-1;
        int idx = Partition(input, low, high);
        while (idx != k-1) {
            if (idx > k-1) {
                high = idx-1;
                idx = Partition(input, low, high);
            } else {
                low = idx+1;
                idx = Partition(input, low, high);
            }
        }
        return vector<int>(input.begin(), input.begin()+k);
    }

    vector<int> QuickSort(vector<int> input) {
        vector<int> rst(input);
        if (rst.empty()) return rst;
        QSort(rst, 0, rst.size()-1);
        return rst;
    }

    void QSort(vector<int>& input, int start, int end) {
        if (start >= end) return;
        int idx = Partition(input, start, end);
        QSort(input, start, idx-1);
        QSort(input, idx+1, end);
    }
};

int main()
{
    vector<int> input{4,5,1,6,2,7,3,8};

    Solution sol;
    vector<int> array(sol.GetLeastNumbers_Solution(input, 4));
    for (vector<int>::iterator itr = array.begin(); itr != array.end(); ++itr)
        cout << *itr << ",";
    cout << endl;
    array = sol.QuickSort(input);
    for (vector<int>::iterator itr = array.begin(); itr != array.end(); ++itr)
        cout << *itr << ",";

    return EXIT_SUCCESS;
}
