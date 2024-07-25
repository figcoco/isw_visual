// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_PIVOT_PIVOTTABLEREFRESHOPTION_H
#define ASPOSE_CELLS_PIVOT_PIVOTTABLEREFRESHOPTION_H

#include "Aspose.Cells/Export.h"

#include "Aspose.Cells/ReserveMissingPivotItemType.h"

namespace Aspose { namespace Cells { namespace Pivot {

class PivotTableRefreshOption_Impl;

/// <summary>
/// Represents the options of refreshing data source of the pivot table.
/// </summary>
class PivotTableRefreshOption {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    PivotTableRefreshOption_Impl* _impl;
    
public:
    /// <summary>
    /// Represents the options of refreshing data source of the pivot table.
    /// </summary>
    ASPOSE_CELLS_API PivotTableRefreshOption();
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API PivotTableRefreshOption(PivotTableRefreshOption_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API PivotTableRefreshOption(const PivotTableRefreshOption& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~PivotTableRefreshOption();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API PivotTableRefreshOption& operator=(const PivotTableRefreshOption& src);
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
    /// Represents how to reserve missing pivot items.
    /// </summary>
    ASPOSE_CELLS_API ReserveMissingPivotItemType GetReserveMissingPivotItemType();
    /// <summary>
    /// Represents how to reserve missing pivot items.
    /// </summary>
    ASPOSE_CELLS_API void SetReserveMissingPivotItemType(ReserveMissingPivotItemType value);
    
};

} } }

#endif
