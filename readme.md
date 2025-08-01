# CDOC

**CDOC** is a lightweight documentation generator for code files. It extracts structured comments and optional code blocks to produce Markdown documentation from your source files.

---

## Building CDOC

CDOC requires **C++20** and **CMake ≥ 3.16**.

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/CDOC.git
cd CDOC
````

### 2. Build with CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The resulting executable will be located at:

```
./build/CDOC       # Linux/macOS
.\build\CDOC.exe   # Windows
```

---

## Usage

### Run CDOC on a file or directory

```bash
./CDOC path/to/file.cpp
./CDOC path/to/directory/
```

CDOC will recursively scan the directory, parse all supported files, and generate `.md` documentation files next to each source file.

---

## CDOC Syntax

CDOC uses special comment annotations to extract documentation.

### 1. `@CDOC <Section Title>`

This marks the beginning of a documentation section. The text after `@CDOC` becomes a section heading in the output `.md` file.

**Example (in C++):**

```cpp
// @CDOC Vector Initialization
// This section explains how vectors are initialized in C++.
```

Produces:

```markdown
## Vector Initialization

This section explains how vectors are initialized in C++.
```

---

### 2. `@CDOC_F`

Marks the beginning of a code block.

### 3. `@CDOC_E`

Marks the end of a code block.

**Example:**

```cpp
// @CDOC_F
std::vector<int> nums = {1, 2, 3};
// @CDOC_E
```

Produces:

```markdown
    ```
    std::vector<int> nums = {1, 2, 3};
    
    ```
```
---

## 🧾 .CDOCignore

You can exclude files and directories from processing using a `.CDOCignore` file. Place it at the root of the directory you’re scanning.

- Supports glob-like patterns:
  - `*.cpp` → ignores all `.cpp` files
  - `test/` → ignores the entire `test/` folder
  - `build/*` → ignores everything inside the `build` directory

**Example `.CDOCignore`:**

```

# Ignore test files

test/
*.tmp
build/*

```

---

## ✅ Supported Languages

CDOC detects comment styles based on file extension:

| Extension         | Comment Style |
|------------------|---------------|
| `.cpp`, `.h`, `.c`, `.hpp`, `.cc`, `.cxx`, `.rs`, `.go`, `.js` | `//` |
| `.py`             | `#`           |
| `.sql`            | `--`          |

Files with unknown extensions are skipped.

---

## 📄 Output

For every supported source file, CDOC creates a corresponding `.md` file in the same directory with the same name.

Example:
```

src/main.cpp  →  src/main.md

```

---

## Why CDOC?

CDOC helps you embed your documentation **next to your code**, without needing to maintain separate `.md` files. It's ideal for small projects, snippets, or educational materials.

---

## Known Limitations

- No syntax highlighting in code blocks
- Does not support multiline comment styles (`/* */`)
- Limited glob support in `.CDOCignore`

---

## Contributing

Pull requests are welcome! For major changes, please open an issue first.

---

## License

MIT License

