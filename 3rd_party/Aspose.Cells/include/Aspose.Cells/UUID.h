// Copyright (c) 2001-2023 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.

#ifndef ASPOSE_CELLS_UUID_H
#define ASPOSE_CELLS_UUID_H

#ifdef _WIN32
#include <guiddef.h>
#elif __APPLE__
#include <uuid/uuid.h>
#endif

namespace Aspose { namespace Cells {
	/// <summary>
	/// Guid struct.
	/// </summary>
#ifdef _WIN32
	typedef GUID UUID;
#elif __APPLE__
	typedef uuid_t UUID;
#else
	typedef unsigned char UUID[16];
#endif
} }

#endif
