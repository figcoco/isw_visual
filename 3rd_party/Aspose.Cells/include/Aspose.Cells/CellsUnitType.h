// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_CELLSUNITTYPE_H
#define ASPOSE_CELLS_CELLSUNITTYPE_H

namespace Aspose { namespace Cells {

/// <summary>
/// Specifies the unit of measurement.
/// </summary>
enum class CellsUnitType {
    /// <summary>
    /// Measurement is in pixels.
    /// </summary>
    Pixel = 1,
    /// <summary>
    /// Measurement is in points. A point represents 1/72 of an inch.
    /// </summary>
    Point = 2,
    /// <summary>
    /// Measurement is in inches.
    /// </summary>
    Inch = 4,
    /// <summary>
    /// Measurement is in centimeters.
    /// </summary>
    Cm = 6,
    /// <summary>
    /// In unit of characters.
    /// </summary>
    /// <remarks>
    /// Only for width.
    /// </remarks>
    Character = 7,
};

} }

#endif
