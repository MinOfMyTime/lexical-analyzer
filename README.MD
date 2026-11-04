# Lexical Analyzer in C++

A compiler-front-end learning project that explores **lexical analysis (tokenization)** in two ways:

1. A **handwritten scanner in C++** that reads source text and identifies tokens.
2. A separate **Flex/Lex specification** that expresses token-recognition rules using regular expressions.

The project was developed as part of compiler-related coursework to practice string processing, token classification, file handling, and lexical error reporting. It is a **scanner**, not a complete compiler or parser.

## Features

The handwritten C++ scanner implements recognition of:

- **Keywords:** for example, `program`, `var`, `if`, `while`, `begin`, and `end`.
- **Identifiers:** names containing letters, digits, and underscores (subject to identifier-start rules).
- **Numeric literals:** integers and decimal-number syntax.
- **String literals:** double-quoted strings.
- **Operators:** arithmetic, assignment, and comparisons such as `+`, `-`, `:=`, `<=`, `>=`, and `!=`.
- **Delimiters:** parentheses, square brackets, commas, semicolons, and periods.
- **Comments:** rules for `#` line comments and `## ... ##` short comments.
- **Lexical error reporting:** diagnostics that include a line number, column number, and an indication of the problematic position.

The scanner collects recognized tokens in a dynamically resized array before printing them.

## Project Structure

```text
lexical-analyzer-cpp/
├── compiler.cpp       # Entry point for the handwritten C++ scanner
├── Scanner.h          # Token definitions and handwritten scanning logic
├── FileDescriptor.h   # Reads a source file into a buffer
├── scanner.l          # Separate Flex/Lex scanner rules
├── headerforflex.h    # Token declarations used by the Flex version
├── regex.txt          # Notes on token patterns
├── test.txt           # Sample input, including invalid-token cases
├── report.docx        # Coursework report about Lex (optional)
├── run(1).bat          # Windows build-and-run script
└── README.md
```

A precompiled executable (`main.exe`) is not needed in the source repository: build it locally from the `.cpp` file instead.

## Build and Run: Handwritten C++ Scanner

### Requirements

- A C++ compiler such as **G++** (C++17 supported)
- A terminal or command prompt

### Linux / macOS

From the repository directory:

```bash
g++ -std=c++17 compiler.cpp -o scanner
./scanner
```

### Windows (MinGW / G++)

```powershell
g++ -std=c++17 compiler.cpp -o scanner.exe
.\scanner.exe
```

You can also use the supplied `run(1).bat` script on Windows if G++ is on your `PATH`.

**Input:** `compiler.cpp` currently opens a file named `test.txt` from the current working directory. To try another source file, change the filename in `compiler.cpp` and rebuild.

**Output:** The handwritten scanner prints recognized lexemes/values to standard output and reports lexical errors. It does **not yet provide a polished token-type table**, and numeric output formatting needs correction (see Known Limitations).

## Example Input

The included `test.txt` exercises keywords, identifiers, operators, comments, and malformed tokens. For example, the scanner is intended to recognize the individual tokens in:

```text
var x := 12;
while x <= 15
begin
    x := x + 1;
end
```

The included test input also intentionally contains invalid characters and malformed identifiers to exercise error reporting.

## Flex/Lex Version (Separate Experiment)

`scanner.l` defines regular-expression-based rules for similar token categories, and `headerforflex.h` contains associated token declarations. This is a **separate implementation** from the handwritten `Scanner` class.

The Flex version is included as coursework/experimentation. **Its build and end-to-end behavior have not been verified here**. In its current form, the `main()` function calls `yylex()` once; because token rules return immediately, the program may stop after the first recognized token. Further integration and testing are needed before treating it as a complete replacement for the C++ scanner.

## How the Handwritten Scanner Works

1. `FileDescriptor.h` opens the input file and loads its contents into a dynamically growing buffer.
2. `Scanner.h` traverses that buffer character by character.
3. Based on the current character, the scanner identifies keywords, identifiers, literals, comments, operators, or delimiters.
4. Recognized tokens are appended to a dynamically resized token array.
5. The scanner prints the collected results and reports invalid input with source-position information.

## Known Limitations

This is an educational implementation and not a production-ready compiler component.

- **Numeric output formatting:** `printTokens()` uses an integer format specifier for a floating-point value, producing unreliable output.
- **Decimal parsing:** fractional digits are accumulated without proper place-value scaling, so floating-point values may be incorrect.
- **Input edge cases:** unterminated strings/comments and end-of-buffer access need more robust handling.
- **Memory management:** dynamically allocated buffers and token strings need more consistent cleanup.
- **Error handling:** some error paths and unsupported operator cases need refinement.
- **Flex scanner:** the independent Flex version needs additional testing and iteration over returned tokens.
- **Testing:** there is a sample input file, but no automated test suite yet.

## Future Improvements

- Fix numeric parsing and token display.
- Print token types alongside lexemes and source locations.
- Add automated tests for valid input and malformed tokens.
- Improve bounds checking and cleanup of dynamically allocated memory.
- Make input paths configurable through command-line arguments.
- Complete and validate the Flex-based implementation.
- Optionally add the next compiler phase: parsing.

## What I Learned

Working on this project provided practical experience with **C++**, lexical analysis, regular expressions, tokenization, dynamic memory allocation, file handling, and error diagnostics. Comparing a handwritten scanner with a Flex/Lex specification also helped illustrate the trade-off between implementing token recognition manually and generating it from rules.
