#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>

inline std::string UCharToHex(const unsigned char c) {
    const char subs[17] = "0123456789abcdef";
    std::string ret = "0x00";
    ret[2] = subs[(c>>4)&15];
    ret[3] = subs[c&15];
    return ret;
}

inline std::string_view GetDelimiter(const int pos, const int len, const int per_line = 16) {
    return pos == len - 1 ? "};\n" :
                pos % (per_line+1) == per_line ? ",\n" : ",";
}

int main(int argc, char **argv) {
    std::ofstream out(argv[1]);
    std::ifstream in(argv[2], std::ios::binary);

    std::string file_name = argv[2];
    size_t pos = 0;
    while ((pos = file_name.find("/", pos)) != file_name.npos) {
        file_name.replace(pos, 1, "_");
    }
    pos = 0;
    while ((pos = file_name.find(".", pos)) != file_name.npos) {
        file_name.replace(pos, 1, "_");
    }

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(in), {});


    out << "#ifndef " << file_name << "_h" << std::endl;
    out << "#define " << file_name << "_h" << std::endl;
    out << "#include <vector>" << std::endl;
    out << "namespace " << file_name << " {" << std::endl;
    out << "namespace " << " {" << std::endl;
    out << "    const std::vector<unsigned char> content = { " << std::endl;
    for (size_t i = 0; i < buffer.size(); i++) {
        out << UCharToHex(buffer[i]) << GetDelimiter(i, buffer.size());
    }
    out << "} // namespace" << std::endl;
    out << "    std::string GetContentString() { return std::string(content.begin(), content.end()); }" << std::endl;
    out << "    const std::vector<unsigned char> GetContent() { return content; }" << std::endl;
    out << "} // namespace " << file_name << std::endl;
    out << "#endif" << std::endl;
    return 0;
}