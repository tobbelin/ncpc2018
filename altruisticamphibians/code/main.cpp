#include <iostream>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <array>

int32_t num_frogs;
int32_t height;

struct Frog{
    int32_t leap;
    int32_t height;
    int32_t weight;
};

struct Pile{
    int32_t total_height;
    int32_t total_weight;
    int32_t total_frogs;
};

bool inline try_to_escape(Frog& frog, std::vector<Frog>& frogs, Pile& pile, int32_t start){
    if(start >= frogs.size()){
        return false;
    }
    for(auto inner_start = start; inner_start < frogs.size(); ++inner_start){
        auto test_frog = frogs.rbegin()[inner_start];
        if(test_frog.weight > pile.total_weight){
            pile.total_height += test_frog.height;
            pile.total_weight += test_frog.weight;
            ++pile.total_frogs;
            if(pile.total_height + frog.leap > height){
                return true;
            }
            if(try_to_escape(frog, frogs, pile, start + 1)){
                return true;
            }
            pile.total_height -= test_frog.height;
            pile.total_weight -= test_frog.weight;
            --pile.total_frogs;
        }
    }
    return false;
}

bool inline try_to_escape(Frog& frog, std::vector<Frog>& frogs){
    if(frog.leap > height) return true;
    Pile pile = {.total_height = 0, .total_weight = frog.weight};
    return try_to_escape(frog, frogs, pile, 0);
}

int main(void){
    std::string line;
#ifdef USESTDIN
    std::getline(std::cin, line);
#else
    std::fstream fs("../data/secret/09-uniform.in", std::ios_base::in);
    std::getline(fs, line);
#endif
    auto ptr = line.c_str();
    num_frogs = static_cast<int32_t>(strtol(ptr, const_cast<char**>(&ptr), 10));
    height = static_cast<int32_t>(strtol(ptr, const_cast<char**>(&ptr), 10));
    std::vector<Frog> frogs(num_frogs);
    std::cout << "Frogs: " << num_frogs << " height: " << height << "\n";
    for(int i = 0; i < num_frogs; ++i){
#ifdef USESTDIN
        std::getline(std::cin, line);
#else
        std::getline(fs, line);
#endif
        ptr = line.c_str();
        frogs[i].leap = static_cast<int32_t>(strtol(ptr, const_cast<char**>(&ptr), 10));
        frogs[i].weight = static_cast<int32_t>(strtol(ptr, const_cast<char**>(&ptr), 10));
        frogs[i].height = static_cast<int32_t>(strtol(ptr, const_cast<char**>(&ptr), 10));
//        std::cout << "Loaded frog: " << i << ", leap: " << frogs[i].leap << ", weight: " << frogs[i].weight << ", height: " << frogs[i].height << "\n";
    }
    std::sort(std::begin(frogs), std::end(frogs), [](Frog a, Frog b) {
        return a.weight > b.weight ? true : a.weight < b.weight ? false : a.height < b.height ? true : false;   
    });
    std::cout << "Loaded file complete\n";
    int32_t escaped = 0;
    while(frogs.size()){
        auto frog = frogs.back();
        frogs.pop_back();        
        std::cout << "Remaining frogs: " << frogs.size() << ", frog: leap: " << frog.leap << ", weight: " << frog.weight << ", height: " << frog.height << "\n";
        if(try_to_escape(frog, frogs)){
            ++escaped;
            std::cout << "Managed to escape: " << escaped << "\n";
        }
    }
    std::cout << "Total frogs that managed to escape: " << escaped << "\n";
}