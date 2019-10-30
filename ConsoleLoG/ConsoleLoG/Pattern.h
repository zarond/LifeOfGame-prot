#pragma once
#include <string>
#include <vector>
typedef std::vector<std::vector<bool>> boolXbool;

namespace Custom{

    class Pattern
    {
    private:
        size_t id = 0;
        std::string name = "";
        boolXbool pattern;
        size_t height = 0;
        size_t width = 0;

        static boolXbool PreparePatrernArr(const std::string&, size_t, size_t);

        bool IsCorrectInput(const std::string&);
    public:
        Pattern(std::string&);
        Pattern(int);
        
        size_t Height()const;
        size_t Width()const;
        size_t ID()const;
        boolXbool GetPattern() const;
        std::string Name() const;
        void Rotate();
    };

}
