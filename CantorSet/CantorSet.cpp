// CantorSet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

// Structure to represent a line segment
struct Segment {
    int start;
    int length;
    Segment(int s, int l) : start(s), length(l) {}
};

class CantorSet {
private:
    std::vector<std::vector<Segment>> generations;
    int width;
    int maxDepth;

    // Generate segments for the next generation
    std::vector<Segment> generateNextGen(const std::vector<Segment>& currentGen) {
        std::vector<Segment> nextGen;
        for (const Segment& seg : currentGen) {
            int segLen = seg.length / 3;
            // Add left third
            nextGen.emplace_back(seg.start, segLen);
            // Add right third
            nextGen.emplace_back(seg.start + 2 * segLen, segLen);
        }
        return nextGen;
    }

public:
    CantorSet(int w, int depth) : width(w), maxDepth(depth) {
        // Initialize with full line
        std::vector<Segment> firstGen = { Segment(0, width) };
        generations.push_back(firstGen);

        // Generate subsequent generations
        for (int i = 1; i <= maxDepth; i++) {
            generations.push_back(generateNextGen(generations.back()));
        }
    }

    // Visualize the Cantor set
    void display() const {
        for (size_t i = 0; i < generations.size(); i++) {
            // Print generation number
            std::cout << "Generation " << i << ": ";

            // Create empty line
            std::string line(width, ' ');

            // Fill in segments
            for (const Segment& seg : generations[i]) {
                for (int j = 0; j < seg.length; j++) {
                    line[seg.start + j] = '-'; // "-" is the drawing symbol used to draw the 
                }
            }

            // Print the line
            std::cout << line << std::endl;
        }
    }

    // Get information about a specific generation
    void printInfo(int gen) const {
        if (gen >= 0 && gen < static_cast<int>(generations.size())) {
            double totalLength = 0;
            for (const Segment& seg : generations[gen]) {
                totalLength += seg.length;
            }

            std::cout << "Generation " << gen << " info:" << std::endl;
            std::cout << "Number of segments: " << generations[gen].size() << std::endl;
            std::cout << "Total length: " << totalLength << std::endl;
            std::cout << "Fraction of original length: " << totalLength / width << std::endl;
        }
    }
};

int main() {
    // Create a Cantor set with width 81 and 4 generations
    CantorSet cantor(81, 4);

    // Display the visualization
    std::cout << "Cantor Set Visualization:" << std::endl;
    std::cout << "========================" << std::endl;
    cantor.display();

    // Print information about each generation
    std::cout << "\nGeneration Statistics:" << std::endl;
    std::cout << "=====================" << std::endl;
    for (int i = 0; i <= 4; i++) {
        cantor.printInfo(i);
        std::cout << std::endl;
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
