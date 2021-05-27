#pragma once
#include <string>
#include <tuple>
#include <vector>

typedef std::vector<std::tuple<int, int, int, int>> fxf; // four-by-four

class chord
{
        std::string symbol;
        int root;
        std::tuple<int, int, int, int> tones;
        fxf voicings;
        std::string quality;
    public:
        std::vector<chord*> precedes;
        std::vector<chord*> follows;
        chord();
        chord(std::string, int,std::tuple<int, int, int, int>, fxf, std::vector<chord*>, std::vector<chord*>, std::string);
        std::string get_symbol();
        int get_root();
        std::tuple<int, int, int, int> get_tones();
        fxf get_voicings();
        std::string get_quality();
};

std::vector<chord> get_prog(int);