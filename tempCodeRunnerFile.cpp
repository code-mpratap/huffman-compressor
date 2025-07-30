#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
    char ch;
    Node *left, *right;
    Node(char c) : ch(c), left(nullptr), right(nullptr) {}
};

// Deserialize the Huffman tree from pre-order serialized string
Node* deserializeTree(istringstream &ss) {
    string val;
    ss >> val;

    if (val == "#") return nullptr;

    // 🧠 Decode special symbols
    if (val == "_") val = " ";        // Space
    else if (val == "\\n") val = "\n"; // Newline

    Node* node;
    if (val == "*")
        node = new Node('*');
    else
        node = new Node(val[0]);

    node->left = deserializeTree(ss);
    node->right = deserializeTree(ss);
    return node;
}


void decodeFile(Node* root, const string& data, const string& outputPath) {
    ofstream out(outputPath);
    Node* curr = root;

    for (char bit : data) {
        if (bit == '0') curr = curr->left;
        else if (bit == '1') curr = curr->right;

        // Leaf node reached
        if (!curr->left && !curr->right) {
            out.put(curr->ch);
            curr = root;
        }
    }
    out.close();
}

int main() {
    ifstream in("compressed.huff");
    if (!in) {
        cout << "❌ Cannot open compressed.huff\n";
        return 1;
    }

    string treeLine, bitstream, temp;
    
    // Read full tree line (first line only)
    getline(in, treeLine);

    // Read the rest as bitstream
    while (getline(in, temp)) bitstream += temp;

    if (treeLine.empty() || bitstream.empty()) {
        cout << "❌ Invalid or empty compressed file.\n";
        return 1;
    }

    istringstream ss(treeLine);
    Node* root = deserializeTree(ss);

    decodeFile(root, bitstream, "output.txt");

    cout << "✅ Decompression complete. Output written to output.txt\n";
    return 0;
}
