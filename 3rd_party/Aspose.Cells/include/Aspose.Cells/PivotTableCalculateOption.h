// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_PIVOT_PIVOTTABLECALCULATEOPTION_H
#define ASPOSE_CELLS_PIVOT_PIVOTTABLECALCULATEOPTION_H

#include "Aspose.Cells/Export.h"

#include "Aspose.Cells/ReserveMissingPivotItemType.h"

namespace Aspose { namespace Cells { namespace Pivot {

class PivotTableCalculateOption_Impl;

/// <summary>
/// Rerepsents the options of calcuating the pivot table.
/// </summary>
class PivotTableCalculateOption {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    PivotTableCalculateOption_Impl* _impl;
    
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    ASPOSE_CELLS_API PivotTableCalculateOption();
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API PivotTableCalculateOption(PivotTableCalculateOption_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API PivotTableCalculateOption(const PivotTableCalculateOption& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~PivotTableCalculateOption();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API PivotTableCalculateOption& operator=(const PivotTableCalculateOption& src);
    /// <summary>
    /// operator bool()
    /// </summary>
    /// <returns>Returns true if the implementation object is not nullptr. Otherwise, returns false</returns>
    ASPOSE_CELLS_API explicit operator bool() const { return _impl != nullptr; }
    /// <summary>
    /// Checks whether the implementation object is nullptr.
    /// </summary>
    /// <returns>Returns true if the implementation object is nullptr. Otherwise, returns false</returns>
    ASPOSE_CELLS_API bool IsNull() const { return _impl == nullptr; }
    
public:
    /// <summary>
    /// Indicates whether refreshing data source of the pivottable.
    /// </summary>
    ASPOSE_CELLS_API bool GetRefreshData();
    /// <summary>
    /// Indicates whether refreshing data source of the pivottable.
    /// </summary>
    ASPOSE_CELLS_API void SetRefreshData(bool value);
    /// <summary>
    /// Indicates whether refreshing charts are based on this pivot table.
    /// </summary>
    ASPOSE_CELLS_API bool GetRefreshCharts();
    /// <summary>
    /// Indicates whether refreshing charts are based on this pivot table.
    /// </summary>
    ASPOSE_CELLS_API void SetRefreshCharts(bool value);
    /// <summary>
    /// Represents how to reserve missing pivot items.
    /// </summary>
    /// <remarks>
    /// Only works when <see cref="RefreshData"/> is true.
    /// </remarks>
    ASPOSE_CELLS_API ReserveMissingPivotItemType GetReserveMissingPivotItemType();
    /// <summary>
    /// Represents how to reserve missing pivot items.
    /// </summary>
    /// <remarks>
    /// Only works when <see cref="RefreshData"/> is true.
    /// </remarks>
    ASPOSE_CELLS_API void SetReserveMissingPivotItemType(ReserveMissingPivotItemType value);
    
};

} } }

#endif
