#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <cmath>

typedef long long int li;
typedef long double ld;
using namespace std;

// Node class for Huffman Tree
class Node {
public:
    char c;
    int freq;
    Node *left, *right;

    Node(char c, int freq, Node* left, Node* right) {
        this->c = c;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

// Comparator for priority queue
struct comparatorFunc {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void encodeHuffMan(Node* root, string str, map<char, string>& HuffManCodes) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        HuffManCodes[root->c] = str;
    }
    encodeHuffMan(root->left, str + '0', HuffManCodes);
    encodeHuffMan(root->right, str + '1', HuffManCodes);
}

string decodeString(Node* root, string encodedString) {
    string ans = "";
    Node* curr = root;
    for (int i = 0; i < encodedString.size(); i++) {
        if (encodedString[i] == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if (curr->left == NULL && curr->right == NULL) {
            ans += curr->c;
            curr = root;
        }
    }
    return ans;
}

void makingHuffManCode(const string& input) {
    map<char, int> frequencies;
    for (auto i : input) {
        frequencies[i]++;
    }

    priority_queue<Node*, vector<Node*>, comparatorFunc> HuffmanTree;
    for (auto x : frequencies) {
        Node* newNode = new Node(x.first, x.second, NULL, NULL);
        HuffmanTree.push(newNode);
    }

    while (HuffmanTree.size() != 1) {
        Node* left = HuffmanTree.top();
        HuffmanTree.pop();
        Node* right = HuffmanTree.top();
        HuffmanTree.pop();
        Node* newNode = new Node('$', left->freq + right->freq, left, right);
        HuffmanTree.push(newNode);
    }

    Node* root = HuffmanTree.top();
    map<char, string> HuffManCodes;
    encodeHuffMan(root, "", HuffManCodes);

    string encodedString = "";
    for (auto c : input) {
        encodedString += HuffManCodes[c];
    }

    string decodedString = decodeString(root, encodedString);

    int originalSizeInBits = 8 * input.length();
    int encodedSizeInBits = encodedString.length();
    double compressionRate = (double)encodedSizeInBits / originalSizeInBits * 100;

    // Write results to output file
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        outputFile << "Original string: " << input << endl;
        outputFile << "Encoded string: " << encodedString << endl;
        outputFile << "Decoded string: " << decodedString << endl;
        outputFile << "Compression rate: " << 100 - compressionRate << "% of the original string" << endl;
        outputFile << "Huffman Codes:\n";
        for (auto i : HuffManCodes) {
            outputFile << i.first << " : " << i.second << endl;
        }
        outputFile.close();
    } else {
        cout << "Unable to open output file." << endl;
    }
}

int main() {
    string input;
    
    // Read input from file
    ifstream inputFile("sample.txt");
    if (inputFile.is_open()) {
        getline(inputFile, input, '\0'); // Read entire file content
        inputFile.close();
    } else {
        cout << "Unable to open input file." << endl;
        return 1;
    }

    makingHuffManCode(input);
    return 0;
}
