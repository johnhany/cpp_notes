#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
#include <cstring>
#include <list>

using namespace std;


int main() {
    static const int arr[] = {16,2,77,29};
    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

    for (int i : vec)
        cout << i << ", ";
    cout << endl;


    int array[8][10];
    memset(array, 0, sizeof array);
    // If `array` is not in the same scope, use:
    memset(array, 0, sizeof(array[0][0]) * 8 * 10);


    // `vector.size() == 0` is slightly faster than `vector.empty()`


    list<int> a{1,2,3,4}, b{5,6,7};
    // a.insert(a.end(), b.begin(), b.end());
    a.splice(a.end(), b);
    for (int i : a)
        cout << i << ", ";
    cout << endl;


    // vector<int> vec2{begin(a), end(a)};
    vector<int> vec2{make_move_iterator(begin(a)), make_move_iterator(end(a))};
    for (int i : vec2)
        cout << i << ", ";
    cout << endl;


    map<int, string> mymap{{1, "string1"}, {2, "string2"}, {4, "string4"}};
    map<int, string>::iterator lb = mymap.lower_bound(3);
    if(lb != mymap.end() && !(mymap.key_comp()(3, lb->first))) {
        lb->second += "!!!";
    } else {
        mymap.insert(lb, map<int, string>::value_type(3, "string3"));
    }

    for (const auto& kv : mymap)
        cout << kv.first << ": " << kv.second << endl;


    // `unordered_set` of `vector`s
    struct VectorHash {
        size_t operator()(const std::vector<int>& v) const {
            std::hash<int> hasher;
            size_t seed = 0;
            for (int i : v) {
                seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            }
            return seed;
        }
    };

    using MySet = std::unordered_set<std::vector<int>, VectorHash>;

    return 0;
}