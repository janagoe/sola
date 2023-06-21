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

#ifndef DAISI_CPPS_LOGICAL_MESSAGE_CENTRAL_ALLOCATION_ASSIGNMENT_NOTIFICATION_H_
#define DAISI_CPPS_LOGICAL_MESSAGE_CENTRAL_ALLOCATION_ASSIGNMENT_NOTIFICATION_H_

#include "material_flow/model/task.h"
#include "solanet/serializer/serialize.h"

namespace daisi::cpps::logical {
class AssignmentNotification {
public:
  AssignmentNotification() = default;
  AssignmentNotification(daisi::material_flow::Task &task) : task_(task){};

  const daisi::material_flow::Task &getTask() const { return task_; }

  SERIALIZE(task_);

private:
  daisi::material_flow::Task task_;
};

}  // namespace daisi::cpps::logical

#endif
