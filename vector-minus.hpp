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
	using namespace vec_;

  	using typename value_type;
  	using typename allocator_type;
  	using typename size_type;
  	using typename difference_type;
  	using typename reference;
  	using typename const_reference;
	using typename pointer;
	using typename const_pointer;
  	using typename iterator;
	using typename const_iterator;
	using typename revers_iterator;
	using typename const_revers_iterator;

	using vec_;

	using push_back;
	using pop_back;
	///+-気を付けないといけなそう

	using size;
	using empty;
	using clear;

	///ちょっと扱いずらそう
	using resize;
	using capacity;
	using front;
	using back;
	using reserve;
	using swap;

///いてれーた

	using begin;
	using end;

	///constなbegin cbegin
	using cbegin;
	using cend;
	///逆順
	using rbegin;
	using rend;

	using crbegin;
	using crend;

	using data;
	








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
	std::size_t sz = vec_.size();
	if (index < 0) {
	  if (static_cast<std::size_t>(-index) > sz)
		throw std::out_of_range(
			"vector_minus::raw_at: negative index out of range");
	  return vec_.at(sz + index);
	} else {
	  return vec_.at(static_cast<std::size_t>(index));
	}
  }

  const T& raw_at(int index) const {
	std::size_t sz = vec_.size();
	if (index < 0) {
		if (static_cast<std::size_t>(-index) > sz)
			throw std::out_of_range(
				"vector_minus::raw_at: negative index out of range");
	  		return vec_.at(sz + index);
		} else {
	  		return vec_.at(static_cast<std::size_t>(index));
		}
  	}

  /// 明示的に at や operator[] は除外！

  T& at(int pos) {

	size_t index=0;
	return this->at(index);
  }

  const T& at(int pos) const {}
};