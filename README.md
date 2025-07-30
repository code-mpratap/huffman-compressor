
# 📦 Huffman File Compressor (C++ Project)

A terminal-based file compression tool built using **Huffman Coding** in **C++**. Mimics real-world file compressors by applying frequency-based encoding.

## 🚀 Features

- Reads text file and builds frequency map
- Constructs Huffman Tree using Min-Heap (priority queue)
- Encodes file using binary Huffman codes
- Outputs compressed binary data to `.huff` file

## 🛠 Technologies Used

- Language: C++
- Concepts: OOP, Min-Heap, Binary Trees, File I/O, Greedy Algorithm

## 📂 Input/Output

- Input file: `input.txt`
- Output file: `compressed.huff`

## 💻 How to Run

```bash
g++ main.cpp -o compressor
./compressor
```

## 🧠 Learning Outcomes

- Built complete Huffman tree from scratch
- Worked with STL (`priority_queue`, `unordered_map`)
- Applied file streams in C++ (`ifstream`, `ofstream`)
- Simulated memory-efficient compression — relevant in embedded systems

---

> Created to showcase algorithmic thinking + systems-level coding — perfect for roles at Qualcomm, NVIDIA, and system software companies.
