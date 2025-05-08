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

template <typename T>
class vector_minus {
 private:
  std::vector<T> vec_;

 public:
  // --- 非インデックス操作のみ forward ---

  /// 要素追加///todo:マイナス対応
  void push_back(const T& val)
    requires std::copyable<T>
  {
    vec_.push_back(val);
  }

  void push_back(T&& val)
    requires std::movable<T>
  {
    vec_.push_back(std::move(val));
  }

  void pop_back()
    requires requires { vec_.pop_back(); }
  {
    vec_.pop_back();
  }

  /// todo:push_frontとか

  /// サイズ・容量
  std::size_t size() const noexcept { return vec_.size(); }
  bool empty() const noexcept { return vec_.empty(); }
  std::size_t capacity() const noexcept { return vec_.capacity(); }

  void reserve(int n) { vec_.reserve(n); }  /// 領域確保 todo::マイナス対応
  void shrink_to_fit() { vec_.shrink_to_fit(); }

  /// front / back
  T& front()
    requires(!std::is_empty_v<T>)
  {
    return vec_.front();
  }

  const T& front() const
    requires(!std::is_empty_v<T>)
  {
    return vec_.front();
  }

  T& back()
    requires(!std::is_empty_v<T>)
  {
    return vec_.back();
  }

  const T& back() const
    requires(!std::is_empty_v<T>)
  {
    return vec_.back();
  }

  /// イテレータ系
  auto begin() noexcept { return vec_.begin(); }
  auto end() noexcept { return vec_.end(); }
  auto begin() const noexcept { return vec_.begin(); }
  auto end() const noexcept { return vec_.end(); }
  auto rbegin() noexcept { return vec_.rbegin(); }
  auto rend() noexcept { return vec_.rend(); }
  auto rbegin() const noexcept { return vec_.rbegin(); }
  auto rend() const noexcept { return vec_.rend(); }

  auto data() noexcept { return vec_.data(); }
  auto data() const noexcept { return vec_.data(); }

  /// スワップ（型がスワップ可能なときのみ）
  void swap(vector_minus& other)
    requires requires { vec_.swap(other.vec_); }
  {
    vec_.swap(other.vec_);
  }

  /// 生の at() ラッパー（負インデックスに対応）
  T& raw_at(int index) {
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
};