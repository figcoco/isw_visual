// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_ADVANCEDFILTER_H
#define ASPOSE_CELLS_ADVANCEDFILTER_H

#include "Aspose.Cells/Export.h"
#include "Aspose.Cells/U16String.h"

namespace Aspose { namespace Cells {

class AdvancedFilter_Impl;

/// <summary>
/// Represents the settings of advanced filter.
/// </summary>
class AdvancedFilter {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    AdvancedFilter_Impl* _impl;
    
public:
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API AdvancedFilter(AdvancedFilter_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API AdvancedFilter(const AdvancedFilter& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~AdvancedFilter();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API AdvancedFilter& operator=(const AdvancedFilter& src);
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
    /// Gets the list range of this advanced filter.
    /// </summary>
    ASPOSE_CELLS_API U16String GetListRange();
    /// <summary>
    /// Gets the criteria range of this advanced filter.
    /// </summary>
    ASPOSE_CELLS_API U16String GetCriteriaRange();
    /// <summary>
    /// Gets the range where copying the resut of this advanced filter to.
    /// </summary>
    ASPOSE_CELLS_API U16String GetCopyToRange();
    
};

} }

#endif
