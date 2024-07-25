// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_PIVOT_PIVOTITEMPOSITIONTYPE_H
#define ASPOSE_CELLS_PIVOT_PIVOTITEMPOSITIONTYPE_H

namespace Aspose { namespace Cells { namespace Pivot {

/// <summary>
/// Represents the position type of the pivot base item in the base field when the ShowDataAs calculation is in use.
/// </summary>
enum class PivotItemPositionType {
    /// <summary>
    /// Represents the previous pivot item in the PivotField.
    /// </summary>
    Previous = 0,
    /// <summary>
    /// Represents the next pivot item in the PivotField.
    /// </summary>
    Next = 1,
    /// <summary>
    /// Shows values as the different format based the index of pivot item in the PivotField.
    /// </summary>
    /// <remarks>Only for getting.</remarks>
    Custom = 2,
};

} } }

#endif
