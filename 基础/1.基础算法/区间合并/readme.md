### 区间合并
> 对于有交集的区间，我们需要将它们合并成一个更大的区间。
> 合并的规则是：如果两个区间有交集，则将它们合并为一个新的区间，其起点为两个区间的最小起点，终点为两个区间的最大终点。

顺序如下：
1. 将所有区间按照左端点从小到大排序，这保证了3中操作的合法性。
2. 初始化一个结果数组，用于存放合并后的区间。小区间不一定能全部合并为**一个**大区间，可能会有多个合并后的区间。
3. 遍历所有区间，对于每个区间：
   - 如果结果数组为空，或者当前区间与结果数组中的**最后一个区间**没有交集，则直接将当前区间加入结果数组。
   - 如果有交集，则需要合并当前区间和结果数组中的最后一个区间，更新最后一个区间的终点。
     - 如果**当前区间**的**右端点 **$\gt$ 结果数组中**最后一个区间**的**右端点**，则更新最后一个区间的右端点为当前区间的右端点。
     - 否则，**当前区间**的**右端点** $\le$ 结果数组中**最后一个区间**的**右端点**，不需要更新。
4. 返回结果数组。
```c++
void mergeIntervals(vector<pair<int, int>>& intervals) {
    // 按照左端点排序
    sort(intervals.begin(), intervals.end());
    
    vector<pair<int, int>> merged;
    // 第一个区间直接加入结果数组，它的左端点是最小的；所以后面进来的就不用与它的左端点相比了
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        auto& last = merged.back();  // 结果数组中的最后一个
        auto& current = intervals[i];
        
        // 如果有交集，合并区间；如果没有，直接加入结果数组
        if (current.first <= last.second) {
            last.second = max(last.second, current.second);
        } else {
            merged.push_back(current);
        }
    }
    
    intervals = merged; // 最后更新原数组，使得调用处的引用得以更新
}
```