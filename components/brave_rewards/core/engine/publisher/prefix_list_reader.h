/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_PUBLISHER_PREFIX_LIST_READER_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_PUBLISHER_PREFIX_LIST_READER_H_

#include <string>

#include "brave/components/brave_rewards/core/engine/hash_prefix_iterator.h"

namespace brave_rewards::internal {
namespace publisher {

// Parses publisher prefix list files and exposes iterators
// over the prefixes stored in the list
class PrefixListReader {
 public:
  enum class ParseError {
    kNone = 0,
    kInvalidProtobufMessage,
    kInvalidPrefixSize,
    kInvalidUncompressedSize,
    kUnknownCompressionType,
    kUnableToDecompress,
    kPrefixesNotSorted,
  };

  PrefixListReader();

  PrefixListReader(const PrefixListReader&) = delete;
  PrefixListReader& operator=(const PrefixListReader&) = delete;

  PrefixListReader(PrefixListReader&& other);
  PrefixListReader& operator=(PrefixListReader&& other);

  ~PrefixListReader();

  // Parses a publisher list message and returns a value indicating
  // whether the message was valid
  ParseError Parse(const std::string& contents);

  // Returns an iterator pointing to the first prefix in the list
  HashPrefixIterator begin() const {
    return HashPrefixIterator(prefixes_, 0, prefix_size_);
  }

  // Returns an iterator pointing to the past-the-end element in the list
  HashPrefixIterator end() const {
    return HashPrefixIterator(prefixes_, size(), prefix_size_);
  }

  // Returns the hash prefix size.
  size_t prefix_size() const { return prefix_size_; }

  // Returns the entire raw prefix list.
  const std::string& prefixes() const { return prefixes_; }

  // Returns the number of prefixes in the list
  size_t size() const { return prefixes_.size() / prefix_size_; }

  // Returns true if the prefix list is empty
  bool empty() const { return size() == 0; }

 private:
  size_t prefix_size_;
  std::string prefixes_;
};

}  // namespace publisher
}  // namespace brave_rewards::internal

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_CORE_ENGINE_PUBLISHER_PREFIX_LIST_READER_H_
