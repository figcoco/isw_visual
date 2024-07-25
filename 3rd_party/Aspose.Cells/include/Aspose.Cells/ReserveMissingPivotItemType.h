// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_PIVOT_RESERVEMISSINGPIVOTITEMTYPE_H
#define ASPOSE_CELLS_PIVOT_RESERVEMISSINGPIVOTITEMTYPE_H

namespace Aspose { namespace Cells { namespace Pivot {

/// <summary>
/// Represents how to keep the missing pivot items.
/// </summary>
enum class ReserveMissingPivotItemType {
    /// <summary>
    /// Removes old missint pivot items and reserves visible items which the current data source does not contain as missing items.
    /// </summary>
    Default,
    /// <summary>
    /// Reserves all missing items.
    /// </summary>
    All,
    /// <summary>
    /// Removes all missing pivot items.
    /// </summary>
    None,
};

} } }

#endif
