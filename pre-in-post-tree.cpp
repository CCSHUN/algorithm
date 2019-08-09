#include <iostream>
#include <string>
using namespace std;

typedef struct node_t {
    node_t(char val) : value(val), left(nullptr), right(nullptr) {}
    char value;
    struct node_t* left;
    struct node_t* right;
} tree_node_t;

tree_node_t* construct(const char* start_prev_order, const char* end_prev_order,
                       const char* start_in_order, const char* end_in_order) {
    char root_value = start_prev_order[0];
    tree_node_t* root = new tree_node_t(root_value);
    if (start_prev_order == end_prev_order) { //只剩下一个节点了
        if (start_in_order == end_in_order &&
            start_prev_order[0] == start_in_order[0]) { //必须剩余的值相同，否则throw
            return root;
        } else {
            throw std::invalid_argument("Invalid input");
        }
    }

    const char* root_in_order = start_in_order; //在中序遍历结果中找到root_value
    while (root_in_order <= end_in_order && *root_in_order != root_value) {
        ++root_in_order;
    }
    //如果中序遍历中不存在root_value，肯定throw
    if (root_in_order == end_in_order && *root_in_order != root_value) {
        throw std::invalid_argument("Invalid input");
    }

    int left_length = root_in_order - start_in_order;
    const char* left_prev_end = start_prev_order + left_length;
    if (left_length > 0) {
        root->left = construct(start_prev_order + 1, left_prev_end,//前序，左子树区间
                               start_in_order, root_in_order - 1); //中序，左子树区间
    }
    if (left_length < end_prev_order - start_prev_order) {
        root->right = construct(left_prev_end + 1, end_prev_order,//前序，右子树区间
                                root_in_order + 1, end_in_order); //中序，右子树区间
    }
    return root;
}

void lrv_tree(tree_node_t* root, string&res) {
    if (root != nullptr) {
        lrv_tree(root->left, res);
        lrv_tree(root->right, res);
        res += root->value;
    }
}

string generate_post_order(const string& pre_order, const string& in_order) {
    if (pre_order.empty() || in_order.empty() ||
        pre_order.size() != in_order.size()) {
        throw std::invalid_argument("Invalid input");
    }

    int length = pre_order.size();
    tree_node_t* root =
        construct(pre_order.c_str(), pre_order.c_str() + length - 1,
                  in_order.c_str(), in_order.c_str() + length - 1);
    
    string res;
    lrv_tree(root, res);

    return res;
}

int main(int argc, char const* argv[]) { 
    string pre_order = "12473568";
    string in_order = "47215386";

    string post_order = generate_post_order(pre_order, in_order);

    cout << post_order << endl;//74258631

    return 0; 
}
