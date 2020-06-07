#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<float>> nms(vector<vector<float>>& box, float threshold) {
    if (box.empty()) return vector<vector<float>>{};
    vector<int> idx;
    for (int i = 0; i < box.size(); i++) {
        idx.push_back(i);
    }

    sort(idx.begin(), idx.end(), [&](int a, int b){
        return box[a][4] > box[b][4];
    });

    vector<vector<float>> rst;
    vector<bool> flag(idx.size(), false);
    int cur = 0;
    while (true) {
        while (cur < idx.size()-1 && flag[idx[cur]])
            cur++;
        if (cur >= idx.size()-1)
            break;
        rst.push_back(box[idx[cur]]);
        for (int j = cur+1; j < idx.size(); j++) {
            float x1 = rst.back()[0] > box[idx[j]][0] ? rst.back()[0] : box[idx[j]][0];
            float x2 = rst.back()[2] < box[idx[j]][2] ? rst.back()[2] : box[idx[j]][2];
            float y1 = rst.back()[3] > box[idx[j]][3] ? rst.back()[3] : box[idx[j]][3];
            float y2 = rst.back()[1] < box[idx[j]][1] ? rst.back()[1] : box[idx[j]][1];
            float w = x2 - x1 + 1 > 0 ? x2 - x1 + 1 : 0;
            float h = y2 - y1 + 1 > 0 ? y2 - y1 + 1 : 0;
            float overlap = w * h;
            float area1 = (rst.back()[2] - rst.back()[0] + 1) * (rst.back()[1] - rst.back()[3] + 1);
            float area2 = (box[idx[j]][2] - box[idx[j]][0] + 1) * (box[idx[j]][1] - box[idx[j]][3] + 1);
            if (overlap / (area1 + area2 - overlap) < threshold && !flag[idx[j]]) {
                flag[idx[j]] = true;
            }
        }
        cur++;
    }
    return rst;
}


int main() {
    // x1, y1, x2, y2, score
    vector<vector<float>> box{
        {1, 6, 4, 3, 0.5},
        {2, 5, 5, 2, 0.6},
        {3, 4, 6, 1, 0.7}
    };
    float threshold = 0.5;

    vector<vector<float>> result =  nms(box, threshold);

    return 0;
}
