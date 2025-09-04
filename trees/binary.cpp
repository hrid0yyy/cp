#include <bits/stdc++.h>
using namespace std;

// Binary Tree Node
struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Create a tree from array input (for testing, level-order style)
Node* buildTree(const vector<int>& nodes, int i, int n) {
    if (i >= n || nodes[i] == -1) return nullptr;
    Node* root = new Node(nodes[i]);
    root->left = buildTree(nodes, 2 * i + 1, n);
    root->right = buildTree(nodes, 2 * i + 2, n);
    return root;
}

// Recursive Pre-order Traversal (Root -> Left -> Right)
void preOrder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Iterative Pre-order Traversal
void preOrderIterative(Node* root) {
    if (!root) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        cout << curr->data << " ";
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}

// Recursive In-order Traversal (Left -> Root -> Right)
void inOrder(Node* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

// Iterative In-order Traversal
void inOrderIterative(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

// Recursive Post-order Traversal (Left -> Right -> Root)
void postOrder(Node* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

// Iterative Post-order Traversal (using two stacks)
void postOrderIterative(Node* root) {
    if (!root) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// Level-order Traversal (BFS)
void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// Height of the Tree
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Size of the Tree (number of nodes)
int size(Node* root) {
    if (!root) return 0;
    return 1 + size(root->left) + size(root->right);
}

// Check if Tree is Balanced (height difference of left and right <= 1)
pair<bool, int> isBalancedUtil(Node* root) {
    if (!root) return {true, 0};
    auto left = isBalancedUtil(root->left);
    if (!left.first) return {false, 0};
    auto right = isBalancedUtil(root->right);
    if (!right.first) return {false, 0};
    if (abs(left.second - right.second) > 1) return {false, 0};
    return {true, 1 + max(left.second, right.second)};
}
bool isBalanced(Node* root) {
    return isBalancedUtil(root).first;
}

// Lowest Common Ancestor (LCA)
Node* lca(Node* root, int n1, int n2) {
    if (!root) return nullptr;
    if (root->data == n1 || root->data == n2) return root;
    Node* left = lca(root->left, n1, n2);
    Node* right = lca(root->right, n1, n2);
    if (left && right) return root;
    return left ? left : right;
}

int main() {
    // Example input: nodes in level-order, -1 for null
    vector<int> nodes = {1, 2, 3, 4, 5, -1, 6}; // Tree:     1
                                                //          / \
                                                //         2   3
                                                //        / \   \
                                                //       4   5   6
    int n = nodes.size();
    Node* root = buildTree(nodes, 0, n);

    // Test Traversals
    cout << "Pre-order (Recursive): "; preOrder(root); cout << endl;
    cout << "Pre-order (Iterative): "; preOrderIterative(root); cout << endl;
    cout << "In-order (Recursive): "; inOrder(root); cout << endl;
    cout << "In-order (Iterative): "; inOrderIterative(root); cout << endl;
    cout << "Post-order (Recursive): "; postOrder(root); cout << endl;
    cout << "Post-order (Iterative): "; postOrderIterative(root); cout << endl;
    cout << "Level-order (BFS): "; levelOrder(root); cout << endl;

    // Test Basic Operations
    cout << "Height: " << height(root) << endl;
    cout << "Size: " << size(root) << endl;
    cout << "Is Balanced: " << (isBalanced(root) ? "Yes" : "No") << endl;

    // Test LCA
    int n1 = 4, n2 = 5;
    Node* lca_node = lca(root, n1, n2);
    cout << "LCA of " << n1 << " and " << n2 << ": " << (lca_node ? lca_node->data : -1) << endl;

    return 0;
}
