#include <iostream>
#include "vector_minus.hpp"  // 先ほどの vector_minus クラスのヘッダをインクルード

int main() {
	vector_minus<int> v;

	// 値を追加（0〜9）
	for (int i = 0; i < 10; ++i) {
		std::cout << "push_back: " << i * 10 << '\n';
		v.push_back(i * 10);  // 0, 10, 20, ..., 90
	}

	std::cout << "+Accsess\n";
	for (int i = 0; i < 5; ++i) {
		std::cout << "gsjgs" << i << '\n';
		std::cout << "v[" << i << "] = " << v[i] << '\n';
	}

	std::cout << "\n-Accsess\n";
	for (int i = -1; i >= -5; --i) {
		std::cout << "v[" << i << "] = " << v[i] << '\n';
	}

	std::cout << "\nraw_atによる例外テスト:\n";
	try {
		v.raw_at(-11);  // サイズ10なので -11 は out_of_range
	} catch (const std::out_of_range& e) {
		std::cout << "例外捕捉: " << e.what() << '\n';
	}

	vector_minus<int> v2;
	std::cout << "[]big" << std::endl;
	for (int i = 0; i < 10; ++i) {
		v2[i] = i * 10;  // 0, 10, 20, ..., 90
		std::cout << "returned" << v2[i] << std::endl;	
	}


	return 0;
}
