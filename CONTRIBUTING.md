## 📚 Contributing to CDOC

Welcome! 👋 I'm glad you're interested in contributing to **CDOC**, a lightweight tool that extracts documentation from code comments and generates clean, readable Markdown files.

Whether you're fixing bugs, adding features, or improving docs — **every contribution matters**.

---

## 🛠️ How to Contribute

### 1. Fork and Clone

```bash
git clone https://github.com/YOUR_USERNAME/CDOC.git
cd CDOC
```

### 2. Build and Run

```bash
mkdir build && cd build
cmake ..
make
./cdoc path/to/your/code
```

Ensure your changes work by running CDOC on sample files.

### 3. Make Changes

* Follow existing code style.
* Add clear, concise comments.
* Keep PRs focused on a single change/feature.

### 4. Test Your Contribution

We don’t have a full test suite yet, but **please test your changes manually** on:

* A single file
* A directory with multiple files
* A directory with a `.CDOCignore` file

If you’re adding a major feature, feel free to add sample files under `examples/`.

### 5. Submit a Pull Request

* Name your branch clearly (e.g., `add-ignore-support` or `fix-markdown-headers`)
* Add a short but descriptive PR title.
* Explain **why** your change is useful.

---

## 📋 Contributor Guidelines

* **No breaking changes** unless necessary — backward compatibility is preferred.
* Respect the purpose: CDOC is meant to be minimal, fast, and dependency-free.
* New features should be optional (e.g., CLI flags or config files).
* All platforms (Linux/Windows/macOS) should be supported unless otherwise discussed.

---

## 🤝 Code of Conduct

We follow a simple rule: **Be respectful.**
We're all here to learn and build something useful.

---

## 🙌 Acknowledgements

Thanks for helping make CDOC better.

---

Let me know if you’d like me to auto-fill links, contributor credits, or match this to a specific license like MIT.
