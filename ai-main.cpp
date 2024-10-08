#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
#include <functional>

// Drawing the state of the array on the screen
void draw_state(const std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue) {
    unsigned int index = 0;
    for(int i : v) {
        if(index == red) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red element
        } else if(index == blue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue element
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Default white
        }
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index += 1;
    }
}

// General sorting function with visual feedback
void visual_sort(std::vector<int>& v, SDL_Renderer* renderer, std::function<void(std::vector<int>&, SDL_Renderer*)> sort_func) {
    sort_func(v, renderer);
}

// Bubble Sort (for example)
void bubble_sort(std::vector<int>& v, SDL_Renderer* renderer) {
    for (unsigned int i = 0; i < v.size(); i++) {
        for (unsigned int j = 0; j < v.size() - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(v, renderer, j, j + 1); // Highlight comparison
            SDL_RenderPresent(renderer);
            SDL_Delay(5);
        }
    }
}

// Insertion Sort (another example)
void insertion_sort(std::vector<int>& v, SDL_Renderer* renderer) {
    for (unsigned int i = 1; i < v.size(); i++) {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(v, renderer, j, j + 1); // Highlight the current and swapped element
            SDL_RenderPresent(renderer);
            SDL_Delay(5);
        }
        v[j + 1] = key;
    }
}

int main() {
    std::random_device rd;
    std::uniform_int_distribution d(1, 99);
    std::vector<int> v;

    for (int i = 0; i < 100; i++) {
        v.push_back(d(rd));
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(100 * 10, 100 * 10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    // Use visual_sort with a specific algorithm
    visual_sort(v, renderer, bubble_sort); // Can replace with insertion_sort or other algorithms

    // Output the sorted array
    for (int i : v) {
        std::cout << i << " ";
    }

    if (std::ranges::is_sorted(v)) {
        std::cout << "\nsorted" << std::endl;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
