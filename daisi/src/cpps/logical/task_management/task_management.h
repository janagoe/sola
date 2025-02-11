// Copyright 2023 The SOLA authors
//
// This file is part of DAISI.
//
// DAISI is free software: you can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation; version 2.
//
// DAISI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with DAISI. If not, see
// <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-2.0-only

#ifndef DAISI_CPPS_LOGICAL_TASK_MANAGEMENT_TASK_MANAGEMENT_H_
#define DAISI_CPPS_LOGICAL_TASK_MANAGEMENT_TASK_MANAGEMENT_H_

#include <algorithm>
#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "cpps/amr/amr_description.h"
#include "cpps/amr/amr_topology.h"
#include "material_flow/model/task.h"
#include "metrics_composition.h"
#include "task_management_helper.h"
#include "utils/structure_helpers.h"

namespace daisi::cpps::logical {

class TaskManagement {
public:
  explicit TaskManagement(AmrDescription amr_description, Topology topology,
                          const daisi::util::Pose &pose)
      : amr_description_(std::move(amr_description)),
        topology_(std::move(topology)),
        current_pose_(pose) {}

  virtual ~TaskManagement() = default;

  /// @brief check wether the task management has a current task assigned
  virtual bool hasTasks() const = 0;

  /// @brief get the current task
  virtual daisi::material_flow::Task getCurrentTask() const = 0;

  /// @brief replace the current task with the first task stored in the management's queue
  virtual bool setNextTask() = 0;

  /// @brief check wether a new task can be added to the management's queue
  virtual bool canAddTask(const daisi::material_flow::Task &task) = 0;

  /// @brief insert a task into the management's queue.
  /// @return true if the insertion was successful, false otherwise
  virtual bool addTask(const daisi::material_flow::Task &task) = 0;

  void addNotifyTaskAssignmentCallback(std::function<void(void)> callback) {
    task_assignment_callbacks_.push_back(callback);
  }

  void clearNotifyTaskAssignmentCallback() { task_assignment_callbacks_.clear(); }

protected:
  std::vector<std::function<void(void)>> task_assignment_callbacks_;

  AmrDescription amr_description_;
  Topology topology_;
  daisi::util::Pose current_pose_;
};

}  // namespace daisi::cpps::logical

#endif
