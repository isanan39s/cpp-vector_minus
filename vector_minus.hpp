/// @file vector_minus.hpp
/// @brief vector_minus - std::vector に負のインデックスアクセスを加えたラッパー
/// @author
/// @license
/// @details
///  - 負のインデックス（Python風）に対応した `.raw_at()`
///  - 明示的に `at()` や `operator[]` は提供しない
///  - 他の vector の機能は必要最小限で forward
///  - `todo:` コメントはユーザーが拡張予定のままに保持

#pragma once

#include <concepts>
#include <stdexcept>
#include <vector>

template <typename T = int, typename Alloc = std::allocator<T>>
class vector_minus : private std::vector<T, Alloc> {
  using vec_ = std::vector<T, Alloc>;

 public:
  //// --- 非インデックス操作のみ forward ---

  ///// 要素追加///todo:マイナス対応
  // void push_back(const T& val)
  //	requires std::copyable<T>
  //{
  //	vec_.push_back(val);
  // }
  //
  // void push_back(T&& val)
  //	requires std::movable<T>
  //{
  //	vec_.push_back(std::move(val));
  // }
  //
  // void pop_back()
  //	requires requires { vec_.pop_back(); }
  //{
  //	vec_.pop_back();
  // }
  //
  ///// todo:push_frontとか
  // void reserve(int n) { vec_.reserve(n); }  /// 領域確保 todo::マイナス対応

/// 型エイリアス
using value_type = typename vec_::value_type;
using allocator_type = typename vec_::allocator_type;
using size_type = typename vec_::size_type;
using difference_type = typename vec_::difference_type;
using reference = typename vec_::reference;
using const_reference = typename vec_::const_reference;
using pointer = typename vec_::pointer;
using const_pointer = typename vec_::const_pointer;
using iterator = typename vec_::iterator;
using const_iterator = typename vec_::const_iterator;
using reverse_iterator = typename vec_::reverse_iterator;
using const_reverse_iterator = typename vec_::const_reverse_iterator;

/// メンバ関数
using vec_::begin;
using vec_::end;
using vec_::cbegin;
using vec_::cend;
using vec_::rbegin;
using vec_::rend;
using vec_::crbegin;
using vec_::crend;
using vec_::data;
using vec_::size;
using vec_::empty;
using vec_::clear;
using vec_::resize;
using vec_::capacity;
using vec_::reserve;
using vec_::swap;
using vec_::front;
using vec_::back;
using vec_::push_back;
using vec_::pop_back;



	  ///// サイズ・容量
	  // std::size_t raw_size() const noexcept { return vec_.size(); }
	  // bool empty() const noexcept { return vec_.empty(); }
	  // std::size_t capacity() const noexcept { return vec_.capacity(); }
	  //
	  // void shrink_to_fit() { vec_.shrink_to_fit(); }
	  //
	  ///// front / back
	  // T& front()
	  //	requires(!std::is_empty_v<T>)
	  //{
	  //	return vec_.front();
	  // }
	  //
	  // const T& front() const
	  //	requires(!std::is_empty_v<T>)
	  //{
	  //	return vec_.front();
	  // }
	  //
	  // T& back()
	  //	requires(!std::is_empty_v<T>)
	  //{
	  //	return vec_.back();
	  // }
	  //
	  // const T& back() const
	  //	requires(!std::is_empty_v<T>)
	  //{
	  //	return vec_.back();
	  // }
	  //
	  ///// イテレータ系
	  // auto begin() noexcept { return vec_.begin(); }
	  // auto end() noexcept { return vec_.end(); }
	  // auto begin() const noexcept { return vec_.begin(); }
	  // auto end() const noexcept { return vec_.end(); }
	  // auto rbegin() noexcept { return vec_.rbegin(); }
	  // auto rend() noexcept { return vec_.rend(); }
	  // auto rbegin() const noexcept { return vec_.rbegin(); }
	  // auto rend() const noexcept { return vec_.rend(); }
	  //
	  // auto data() noexcept { return vec_.data(); }
	  // auto data() const noexcept { return vec_.data(); }
	  //
	  ///// スワップ（型がスワップ可能なときのみ）
	  // void swap(vector_minus& other)
	  //	requires requires { vec_.swap(other.vec_); }
	  //{
	  //	vec_.swap(other.vec_);
	  // }

	  /// 生の at() ラッパー（負インデックスに対応）
	  T&
	  raw_at(int index) {
	std::size_t sz = this->size();
	if (index < 0) {
	  if (static_cast<std::size_t>(-index) > sz)
		throw std::out_of_range(
			"vector_minus::raw_at: negative index out of range");
	  return this->at(sz + index);
	} else {
	  return this->at(static_cast<std::size_t>(index));
	}
  }

  const T& raw_at(int index) const {
	std::size_t sz = this->size();
	if (index < 0) {
		if (static_cast<std::size_t>(-index) > sz)
			throw std::out_of_range(
				"vector_minus::raw_at: negative index out of range");
	  		return this->at(sz + index);
		} else {
	  		return this->at(static_cast<std::size_t>(index));
		}
  	}

  /// 明示的に at や operator[] は除外！

  T& at(int pos) {
	  size_t index = std::abs(pos) * 2;
	  if (pos < 0) index--;
	  return std::vector<T, Alloc>::at(index);
  }

  const T& at(int pos) const {
	  size_t index = std::abs(pos) * 2;
	  if (pos < 0) index--;
	  return std::vector<T, Alloc>::at(index);
  }


  T& operator[](int poz) {
	  size_t index = std::abs(poz) * 2;
	  if (poz < 0) index--;
	  return std::vector<T, Alloc>::operator[](index);  /// 明示的にベースクラスを呼ぶ
  }

  const T& operator[](int poz) const {
	  size_t index = std::abs(poz) * 2;
	  if (poz < 0) index--;
	  return std::vector<T, Alloc>::operator[](index);
  }

};
///https://chatgpt.com/share/681d9d23-6f90-8005-b981-308b049692dd

//0 0


/*


添え字？を偶数を正奇数を負として扱ったらどうにかなる？


ChatGPT:
ほう、それは非常に洒脱な発想ですね！
つまり、インデックスを「偶数なら正」「奇数なら負」として解釈し、1本のstd::vectorに対して正負両方のインデックスをシンプルに表現したい、ということですね。

これはアイディアとしてはなかなか面白く、次のような解釈の転換になります：

添え字 i	論理インデックス
0	+0
1	-0
2	+1
3	-1
4	+2
5	-2
...	...

しかし、0の扱いをどうするかで意味が変わります。上記の表だと0/1はちょっと混乱しそうなので、例えば：

添え字 i	論理インデックス
0	0
1	-1
2	+1
3	-2
4	+2
5	-3
6	+3

こういう風にすると、偶数インデックスは +(i/2), 奇数インデックスは -(i+1)/2 に対応できます。




*/