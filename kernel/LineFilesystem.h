/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#ifndef __LINEFILESYSTEM_H__
#define __LINEFILESYSTEM_H__

#include "LineDrive.h"
#include "fat12.h"
#include "kconfig.h"

enum filesystemformat {
    nofilesystem,
    fat12,
};

typedef enum filesystemformat filesystemformat_t;

const char* filesystem_name(filesystemformat_t fs);
int check_filesystem(drivesformat_t drive, filesystemformat_t fs);

#endif
