#include <iostream>
#include <utility>
#include <vector>

namespace std2 {

int lower_bound(std::vector<int> nums, int target) {
    if (nums.empty() || nums.front() > target || nums.back() < target) {
        return -1;
    }
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

int upper_bound(std::vector<int> nums, int target) {
    if (nums.empty() || nums.front() > target || nums.back() < target) {
        return -1;
    }
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return right;
}

std::pair<int, int> equal_range(std::vector<int> nums, int target) {
    if (nums.empty() || nums.front() > target || nums.back() < target) {
        return {-1, -1};
    }
    int left = lower_bound(nums, target);
    int right = upper_bound(nums, target);
    std::cout << nums[left] << std::endl;
    if (nums[left + 1] != target) {
        return {-1, -1};
    }

    return {left + 1, right - 1};
}

}  // end of namespace std2

int main(int argc, char const *argv[]) {
    // std::vector<int> nums = {5, 7, 7, 8, 8, 8, 10}; //3, 5
    // std::vector<int> nums = {5, 7, 7, 10};  // -1, -1
    // int target = 8;
    // std::vector<int> nums = {5, 7, 7, 8, 8, 8, 10}; //-1, -1
    // int target = 11;
    // std::vector<int> nums = {5, 7, 7, 8, 8, 8, 10}; //-1, -1
    // std::vector<int> nums = {}; //-1, -1

    // TODO: 该用例还存在问题，需要调整...
    std::vector<int> nums = {4}; //?
    int target = 4;

    std::pair<int, int> res = std2::equal_range(nums, target);
    std::cout << res.first << ", " << res.second << std::endl;

    return 0;
}
