// Copyright The SOLA Contributors
//
// Licensed under the MIT License.
// For details on the licensing terms, see the LICENSE file.
// SPDX-License-Identifier: MIT

#ifndef MINHTON_MESSAGE_FIND_REPLACEMENT_H_
#define MINHTON_MESSAGE_FIND_REPLACEMENT_H_

#include "minhton/message/find_end.h"
#include "minhton/message/message.h"
#include "solanet/serializer/serialize.h"

namespace minhton {
/// @brief * **Usage:** A node wants to leave the network, but cannot leave the position directly
/// because it would violate the trees balancing conditions. Another node that can leave the
/// position has to be found to replace the position of the leaving node. For this, the
/// MessageFindReplacement gets forwarded (similar to Join messages) until a fitting node to replace
/// is found.
/// * **Algorithm Association:** Leave.
class MessageFindReplacement : public MinhtonMessage<MessageFindReplacement> {
public:
  /// @param node_to_replace The node that wants to leave the network.
  /// @param search_progress Represents the procedure progress for differentiating the phases.
  /// @param hop_count How often a MessageFindReplacement has been sent during this leave
  /// procedure so far.
  MessageFindReplacement(MinhtonMessageHeader header, NodeInfo node_to_replace,
                         SearchProgress search_progress = SearchProgress::kNone,
                         uint16_t hop_count = 0);

  NodeInfo getNodeToReplace() const;
  SearchProgress getSearchProgress() const;
  uint16_t getHopCount() const;

  SERIALIZE(header_, node_to_replace_, search_progress_, hop_count_)

  MessageFindReplacement() = default;

protected:
  friend MinhtonMessage;

  /// The header contains always required fields like the sender and target
  MinhtonMessageHeader header_;

  /// Checks if the message was constructed with all of the necessary information
  bool validateImpl() const;

private:
  /// The node that wants to leave the network
  NodeInfo node_to_replace_;

  /// Stores information about what steps were already done
  SearchProgress search_progress_ = SearchProgress::kNone;

  /// Keeps track of how many times a MessageFindReplacement has been sent during this leave
  /// procedure
  uint16_t hop_count_ = 0;
};
}  // namespace minhton

#endif
