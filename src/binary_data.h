#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <type_traits>

namespace unimess {

class BinaryData {
private:
    std::vector<unsigned char> data;
    size_t pos;

public:
    BinaryData() {
        reset();
    }

    BinaryData(std::vector<unsigned char>&& raw_data) {
        reset();
        data = std::move(raw_data);
    }

    BinaryData(const std::vector<unsigned char>& raw_data) {
        reset();
        data = raw_data;
    }

    void reset() {
        pos = 0;
    }

    bool at_end() {
        return pos >= data.size();
    }

    const std::vector<unsigned char>& get_data() const {
        return data;
    }

    template<class T> T read_primitive() {
        static_assert(std::is_arithmetic<T>::value, "T must be a primitive type");

        size_t T_size = sizeof(T);
        if(pos + T_size > data.size()) {
            throw std::runtime_error("read out of bound");
        }

        T value = *reinterpret_cast<const T *>(&data[pos]);
        pos += T_size;
        return value;
    }

    template<class T> void write_primitive(const T& value) {
        static_assert(std::is_arithmetic<T>::value, "T must be a primitive type");

        const size_t T_size = sizeof(T);
        const unsigned char *target_value = reinterpret_cast<const unsigned char *>(&value);

        while(pos + T_size > data.size()) {
            data.push_back(0);
        }
        for(int i = 0; i < T_size; i++) {
            data[pos + i] = target_value[i];
        }

        pos += T_size;
    }

    std::string read_string() {
        auto len = read_primitive<unsigned int>();

        if(len == 0) {
            return std::string("");
        }

        if(pos + len > data.size()) {
            throw std::runtime_error("string read out of bound");
        }

        std::string ret(reinterpret_cast<const char *>(&data[pos]), len);
        pos += len;
        return ret;
    }

    void write_string(const std::string& s) {
        unsigned int len = s.size();
        write_primitive(len);

        while(pos + len > data.size()) {
            data.push_back(0);
        }

        for(int i = 0; i < len; i++) {
            data[pos + i] = s[i];
        }

        pos += len;
    }

    std::string read_short_string() {
        unsigned int len = read_primitive<unsigned char>();

        if(len == 0) {
            return std::string("");
        }

        if(pos + len > data.size()) {
            throw std::runtime_error("short string read out of bound");
        }

        std::string ret(reinterpret_cast<const char *>(&data[pos]), len);
        pos += len;
        return ret;
    }

    void write_short_string(const std::string& s) {
        unsigned int len = s.size();
        if(len > 255) {
            throw std::runtime_error("string too long for short type");
        }

        write_primitive((unsigned char) len);

        while(pos + len > data.size()) {
            data.push_back(0);
        }

        for(int i = 0; i < len; i++) {
            data[pos + i] = s[i];
        }

        pos += len;
    }
};

} // namespace unimess
