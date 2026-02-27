# Quiz Answer Auto-Grader (DSA Project)

## 📌 Overview
This project is a C-based automated grading system for short-answer quizzes. 
It evaluates student answers by comparing them with model answers using efficient data structures.

## 🚀 Key Features
- Automatic short-answer grading
- Word-level similarity matching
- Partial credit scoring
- Case-insensitive comparison
- CSV file input support

## 🧠 Data Structures Used
- **Array** – Stores questions and student responses
- **Hash Map (with chaining)** – O(1) average lookup for question-answer mapping
- **Trie** – Efficient word insertion and search (O(L))

## ⚙️ Algorithm Approach
1. Load model answers from `quiz.csv`
2. Store answers in HashMap
3. Insert model answer words into Trie
4. Compare student responses word-by-word
5. Calculate similarity score:
   matched_words / total_model_words

## 🏗 Tech Stack
- Language: C
- File Handling: CSV
- Data Structures: Array, HashMap, Trie

## 📈 Time Complexity
- HashMap Lookup: O(1) average
- Trie Search: O(L) per word
- Overall efficient for large datasets

## 🔮 Future Enhancements
- Semantic similarity detection
- Spell correction using edit distance
- Multi-student grading
- GUI integration
