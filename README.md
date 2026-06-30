# NLP Lexical Processor

A C implementation of a basic NLP lexical preprocessing pipeline using singly linked lists. The program tokenizes raw text, removes common stop words, and computes word frequencies, all built from scratch without external libraries.

## Features

- **Tokenization:** splits raw text into individual word tokens using whitespace and punctuation as delimiters, storing each token in a singly linked list.
- **Stop Word Removal:** filters out common English stop words (e.g. *the, is, and, with*) from the token list, case-insensitively.
- **Word Frequency Count:** builds a second, alphabetically sorted linked list that tracks how many times each unique word occurs.
- **Interactive CLI:** menu-driven interface to run each step independently and inspect the list at any stage.
- **Two input modes:** read text from `input.txt` or type it directly into the terminal.

## How It Works

The program uses two custom linked list structures:

| Structure | Purpose |
|---|---|
| `WordNode` | Stores each token as it's tokenized and as stop words are removed |
| `repeatedWords` | Stores each unique word with its frequency, kept sorted alphabetically as it's built |

The pipeline is sequential and stateful: text is loaded once, then processed step-by-step through the menu (tokenize → remove stop words → view → compute frequencies), with each step operating on the list left behind by the previous one.

## Getting Started

### Prerequisites

A C compiler (GCC or Clang).

### Build

```bash
gcc NLP-Lexical-Processor.c -o nlp-processor
```

### Run

```bash
./nlp-processor
```

You'll be prompted to choose an input source:

```
1 for Read from 'input.txt'
2 for Read from terminal
```

A sample `input.txt` is included in this repo, or you can type your own text directly when choosing option 2.

### Usage

Once text is loaded, use the menu to run each stage:

```
1 for Tokenisation
2 for Removing Stop Words
3 for Showing Words
4 for Calculate and show Frequencies
5 for Exit
```

Run them in order (1 → 2 → 3 → 4) for the full pipeline, or jump to option 3 at any point to inspect the current state of the list.

## Example

**Input:**
```
Natural language processing is a field of artificial intelligence.
```

**After tokenization (option 1, then 3):**
```
| Natural | language | processing | is | a | field | of | artificial | intelligence |
```

**After stop word removal (option 2, then 3):**
```
| Natural | language | processing | field | artificial | intelligence |
```

**Frequencies (option 4):**
```
Word                 | Frequency
-------------------------------------
artificial           | 1
field                | 1
intelligence         | 1
language             | 1
Natural              | 1
processing           | 1
-------------------------------------
```

## Known Limitations

- `system("cls")` is used to clear the screen, which is Windows-specific. On Linux or macOS this call will fail silently and the screen simply won't clear — the program still works correctly otherwise. Swap it for `system("clear")` if you're building on a Unix-based system.
- Input text is capped at 999 characters (`char text[1000]`).
- Words longer than 49 characters are truncated (`wordLen`).

## Project Structure

```
.
├── NLP-Lexical-Processor.c   # Main source file
├── input.txt                 # Sample input text
├── .gitignore
└── README.md
```

## Author

**Amine Ghezal**
