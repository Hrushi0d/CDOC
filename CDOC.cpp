#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

// Store ignore paths
std::unordered_set<std::string> ignore_set;
fs::path root_dir;

struct FileInfo {
    std::string commenttype;
    std::string filename;
};

FileInfo get_file_info(const fs::path& filepath) {
    std::string ext = filepath.extension().string();
    std::string filename = filepath.filename().string();

    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    std::string commenttype;
    if (ext == ".py")              commenttype = "# ";
    else if (ext == ".sql")        commenttype = "-- ";
    else if (ext == ".cpp" || ext == ".cc" || ext == ".cxx" ||
             ext == ".hpp" || ext == ".h" || ext == ".c" ||
             ext == ".rs"  || ext == ".go" || ext == ".js")
        commenttype = "// ";
    else                           commenttype = "Unknown";

    return {commenttype, filename};
}

void generate_markdown_doc(const fs::path& filepath) {
    FileInfo info = get_file_info(filepath);
    if (info.commenttype == "Unknown") {
        std::cerr << "[Skip] Unsupported file: " << filepath << "\n";
        return;
    }

    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "[Error] Could not open file: " << filepath << "\n";
        return;
    }

    fs::path output_path = filepath;
    output_path.replace_extension(".md");
    std::ofstream output(output_path);
    if (!output) {
        std::cerr << "[Error] Could not create output: " << output_path << "\n";
        return;
    }

    std::cout << "[✓] " << filepath << " → " << output_path << "\n";

    bool in_doc_block = false;
    bool in_code_block = false;
    std::string line;
    while (std::getline(input, line)) {
        std::string trimmed = line;
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));

        if (trimmed.rfind(info.commenttype + "@CDOC ", 0) == 0) {
            std::string header = trimmed.substr(trimmed.find("@CDOC") + 6);
            output << "## " << header << "\n\n";
            in_doc_block = true;
            continue;
        }

        if (trimmed.find(info.commenttype + "@CDOC_F") == 0) {
            output << "```" << "\n";
            in_code_block = true;
            continue;
        }

        if (trimmed.find(info.commenttype + "@CDOC_E") == 0) {
            output << "```" << "\n\n";
            in_code_block = false;
            continue;
        }

        if (in_doc_block) {
            if (trimmed.find(info.commenttype) == 0) {
                output << trimmed.substr(info.commenttype.size()) << "\n";
            } else {
                output << "\n";
                in_doc_block = false;
            }
        } else if (in_code_block) {
            output << line << "\n";
        }
    }
}

std::vector<std::regex> ignore_patterns;

std::string glob_to_regex(const std::string& pattern) {
    std::string regex = "^";
    for (size_t i = 0; i < pattern.size(); ++i) {
        char c = pattern[i];
        switch (c) {
            case '*': regex += ".*"; break;
            case '?': regex += "."; break;
            case '.': regex += "\\."; break;
            case '/': regex += "/"; break;
            default:  regex += c; break;
        }
    }
    regex += "$";
    return regex;
}

void load_ignore_file(const fs::path& base) {
    fs::path ignore_file = base / ".CDOCignore";
    if (!fs::exists(ignore_file)) return;

    std::ifstream file(ignore_file);
    std::string line;
    while (std::getline(file, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (!line.empty() && line[0] != '#') {
            try {
                ignore_patterns.emplace_back(glob_to_regex(line));
            } catch (const std::regex_error& e) {
                std::cerr << "[Warning] Invalid ignore pattern: " << line << "\n";
            }
        }
    }
}

bool is_ignored(const fs::path& path) {
    fs::path rel_path = fs::relative(path, root_dir);
    std::string norm = rel_path.generic_string();

    for (const auto& pattern : ignore_patterns) {
        if (std::regex_match(norm, pattern)) {
            return true;
        }
    }
    return false;
}

void process_path(const fs::path& input_path) {
    if (fs::is_regular_file(input_path)) {
        if (!is_ignored(input_path))
            generate_markdown_doc(input_path);
    } else if (fs::is_directory(input_path)) {
        for (const auto& entry : fs::recursive_directory_iterator(input_path)) {
            if (fs::is_regular_file(entry) && !is_ignored(entry.path())) {
                generate_markdown_doc(entry.path());
            }
        }
    } else {
        std::cerr << "[Skip] Invalid path: " << input_path << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file or directory>\n";
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        fs::path input_path(argv[i]);

        if (!fs::exists(input_path)) {
            std::cerr << "[Error] Path doesn't exist: " << input_path << "\n";
            continue;
        }

        if (fs::is_directory(input_path)) {
            root_dir = fs::absolute(input_path);
            load_ignore_file(root_dir);
        } else {
            root_dir = fs::absolute(input_path).parent_path();
            load_ignore_file(root_dir);
        }

        process_path(input_path);
    }

    return 0;
}
