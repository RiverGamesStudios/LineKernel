/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "LineFilesystem.h"

const char* filesystem_name(filesystemformat_t fs)
{
    switch (fs) {
        case fat12:
            return "FAT12";
        default:
            return "(none)";
    }
}

int check_filesystem(drivesformat_t drive, filesystemformat_t fs)
{
    switch (fs) {
#ifdef CONFIG_FAT12
        case fat12:
            return detect_fat12(drive);
#endif
        default:
            return -1;
    }
}
