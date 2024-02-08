#include <iostream>
#include <vector>

template <typename T>
class ArrayList {
private:
    std::vector<T> internalVector;

public:
    void add(const T& element) {
        internalVector.push_back(element);
    }

    void remove(const T& element) {
        auto it = std::find(internalVector.begin(), internalVector.end(), element);
        if (it != internalVector.end()) {
            internalVector.erase(it);
        }
    }

    bool contains(const T& element) const {
        return std::find(internalVector.begin(), internalVector.end(), element) != internalVector.end();
    }
};

