#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <sstream>  // 🔥 Required for ostringstream
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, string str, unordered_map<char, string>& huffCode) {
    if (!root) return;
    if (!root->left && !root->right)
        huffCode[root->ch] = str;
    buildCodes(root->left, str + "0", huffCode);
    buildCodes(root->right, str + "1", huffCode);
}

// 🔁 Generalized ostream version for both file & string
void serializeTree(Node* root, ostream &out) {
    if (!root) {
        out << "# ";
        return;
    }

    if (!root->left && !root->right) {
        if (root->ch == '\n') out << "\\n ";
        else if (root->ch == ' ') out << "_ ";
        else out << root->ch << " ";
    } else {
        out << "* ";
    }

    serializeTree(root->left, out);
    serializeTree(root->right, out);
}


void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void compressFile(const string& inputPath, const string& outputPath) {
    ifstream in(inputPath, ios::binary);
    if (!in) {
        cout << "❌ Could not open input.txt\n";
        return;
    }

    unordered_map<char, int> freqMap;
    char ch;
    while (in.get(ch)) freqMap[ch]++;
    in.clear(); in.seekg(0);

    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto& pair : freqMap)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('*', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();
    unordered_map<char, string> huffCode;
    buildCodes(root, "", huffCode);

    // ✅ Save serialized tree to string (single line)
    ostringstream oss;
    serializeTree(root, oss);
    string treeSerialized = oss.str();

    // ✅ Write to output .huff file
    ofstream out(outputPath);
    out << treeSerialized << "\n";

    in.clear(); in.seekg(0);
    while (in.get(ch)) out << huffCode[ch];

    in.close(); out.close();
    freeTree(root);

    cout << "✅ Compression complete. Output written to " << outputPath << "\n";
}

int main() {
    string inputFile = "input.txt";
    string outputFile = "compressed.huff";
    compressFile(inputFile, outputFile);
    return 0;
}
