#pragma once

typedef struct Range
{
    int min;
    int max;

    struct iterator {
        int current;
        explicit iterator(int current) : current(current) {}
        int operator*() const { return current; }
        iterator& operator++() { ++current; return *this; }
        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
    };
    iterator begin() const { return iterator(min); }
    iterator end() const { return iterator(max + 1); }
}Range;



/*

        // float minX = -2.0 / scale;
        // float maxX = 1.0 / scale;
        // float minY = -1.5 / scale;
        // float maxY = 1.5 / scale;

        float minX = -2.0;
        float maxX =  2.0;
        float minY = -2.0;
        float maxY =  2.0;


*/