// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_PIVOT_PIVOTITEMPOSITION_H
#define ASPOSE_CELLS_PIVOT_PIVOTITEMPOSITION_H

namespace Aspose { namespace Cells { namespace Pivot {

/// <summary>
/// Represents base item Next/Previous/All position in the base field .
/// </summary>
/// <remarks>
/// NOTE: This enum is now obsolete. Instead,
/// please use PivotItemPositionType enum instead.
/// This method will be removed 12 months later since June 2024.
/// Aspose apologizes for any inconvenience you may have experienced.
/// </remarks>
/// @deprecated Use PivotItemPositionType enum instead.
enum class PivotItemPosition {
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
