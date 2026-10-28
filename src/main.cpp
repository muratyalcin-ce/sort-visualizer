#include <functional>
#include <iostream>
#include <random>
#include <raylib.h>
#include <vector>
#include <set>

namespace SortingAlgorithms {
	void insertion_sort_step(std::vector<float>& vec, std::set<size_t>& compared) {
		static size_t right {0};
		static bool done = false;
		
		if(right >= vec.size()) {
			done = true;
			return;
		}
		
		size_t min_idx { right };

		for(size_t i{right}; i < vec.size(); i++) {
			if(vec[i] < vec[min_idx]) {
				min_idx = i;
			}
		}

		float temp { vec[right] };
		vec[right] = vec[min_idx];
		vec[min_idx] = temp;
		compared.emplace(min_idx);
		compared.emplace(right);
		right++;
		
	}
}

class SortingVisualizer {
public:
	SortingVisualizer() {
		InitWindow(WIDTH, HEIGHT, "Sorting Visualizer");
		SetTargetFPS(60);

		std::mt19937 generator {};
		std::uniform_real_distribution<float> range {0., 1.};
		for (size_t i {0}; i < MAX_AMOUNT; i++) {
			m_to_sort.push_back(range(generator));
		}
	}

	void main(){
		while(!WindowShouldClose()) {
			BeginDrawing();

			if(IsKeyDown(KEY_Q)) {
				break;
			}
			
			draw_vec();
			m_compared.clear();
			sort_step(SortingAlgorithms::insertion_sort_step);
			EndDrawing();
			ClearBackground(BLACK);
		}
 	}

	void draw_vec() {
		float x_step {static_cast<float>(WIDTH) / static_cast<float>(MAX_AMOUNT)};
		for(size_t i {0}; i < MAX_AMOUNT; i++) {
			float rect_height { m_to_sort[i] * HEIGHT * 0.9f};
			Color color { m_done ? GREEN : m_compared.contains(i) ? RED : WHITE};
			DrawRectangle(x_step*i, HEIGHT-rect_height, x_step, rect_height, color);
		}
	}

	
	void sort_step(std::function<void(std::vector<float>&, std::set<size_t>&)> f) {
		f(m_to_sort, m_compared);
	}

private:
	const int WIDTH { 800 };
	const int HEIGHT { 600 };
	const int MAX_AMOUNT { 200 };

	bool m_done { false };

	std::vector<float> m_to_sort {};
	std::set<size_t> m_compared{};
};

int main() {
	SortingVisualizer instance {};
	instance.main();
    return 0;
}
