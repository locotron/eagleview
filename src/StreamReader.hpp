// MIT License
// Copyright (c) 2019 Pavel Kovalenko

#pragma once

#include <istream>
#include "Fixed32.hpp"

namespace Tebo
{
    class StreamReader
    {
    protected:
        std::istream &is;
        std::streampos rPos;

    public:
        StreamReader(std::istream &s) : is(s)
        {
            rPos = Tell();
        }

        std::streampos Tell() { return is.tellg(); }
        void Seek(size_t pos) { is.seekg(pos); }

        uint8_t ReadU8()
        {
            uint8_t r;
            is.read((char *)&r, 1);
            rPos = Tell();
            return r;
        }

        bool ReadBool8()
        {
            uint8_t v = ReadU8();
            if (v != 0 && v != 1)
                __debugbreak();
            return v;
        }

        template <typename T>
        void Read(T *dst, size_t count)
        {
            std::streamsize itemSize = sizeof(T);
            is.read((char *)dst, itemSize*count);
            rPos = Tell();
        }

        template <>
        void Read(bool *dst, size_t count)
        {
            static_assert(sizeof(bool) == 1);
            for (size_t i = 0; i < count; i++)
                dst[i] = ReadBool8();
        }

        uint16_t ReadU16()
        {
            uint16_t r;
            Read(&r, 1);
            return r;
        }

        uint32_t ReadU32()
        {
            uint32_t r;
            Read(&r, 1);
            return r;
        }

        int32_t ReadS32()
        {
            int32_t r;
            Read(&r, 1);
            return r;
        }

        float ReadFloat()
        {
            float r;
            Read(&r, 1);
            return r;
        }

        Vector2S ReadVec2S()
        { return {ReadS32(), ReadS32()}; }

        std::string ReadString255()
        {
            uint8_t size = ReadU8();
            std::string s;
            s.resize(size);
            Read(s.data(), size);
            return s;
        }
    };
} // namespace Tebo
