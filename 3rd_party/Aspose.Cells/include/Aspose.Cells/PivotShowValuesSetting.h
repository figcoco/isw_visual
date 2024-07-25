// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_PIVOT_PIVOTSHOWVALUESSETTING_H
#define ASPOSE_CELLS_PIVOT_PIVOTSHOWVALUESSETTING_H

#include "Aspose.Cells/Export.h"

#include "Aspose.Cells/PivotFieldDataDisplayFormat.h"
#include "Aspose.Cells/PivotItemPositionType.h"

namespace Aspose { namespace Cells { namespace Pivot {

class PivotShowValuesSetting_Impl;

/// <summary>
/// Represents the settings about showing values as when the ShowDataAs calculation is in use.
/// </summary>
class PivotShowValuesSetting {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    PivotShowValuesSetting_Impl* _impl;
    
public:
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API PivotShowValuesSetting(PivotShowValuesSetting_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API PivotShowValuesSetting(const PivotShowValuesSetting& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~PivotShowValuesSetting();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API PivotShowValuesSetting& operator=(const PivotShowValuesSetting& src);
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
    /// Represents how to show values of a data field in the pivot report.
    /// </summary>
    /// <see cref= "PivotFieldDataDisplayFormat"/>
    ASPOSE_CELLS_API PivotFieldDataDisplayFormat GetCalculationType();
    /// <summary>
    /// Represents how to show values of a data field in the pivot report.
    /// </summary>
    /// <see cref= "PivotFieldDataDisplayFormat"/>
    ASPOSE_CELLS_API void SetCalculationType(PivotFieldDataDisplayFormat value);
    /// <summary>
    /// Represents the base field for a ShowDataAs calculation when the ShowDataAs calculation is in use.
    /// </summary>
    ASPOSE_CELLS_API int32_t GetBaseFieldIndex();
    /// <summary>
    /// Represents the base field for a ShowDataAs calculation when the ShowDataAs calculation is in use.
    /// </summary>
    ASPOSE_CELLS_API void SetBaseFieldIndex(int32_t value);
    /// <summary>
    /// Represents type of the base pivot item in the base field when the ShowDataAs calculation is in use.
    /// Valid only for data fields.
    /// Because PivotItemPosition.Custom is only for read,if you need to set PivotItemPosition.Custom,
    /// please set PivotField.BaseItemIndex attribute.
    /// </summary>
    /// <see cref="PivotItemPositionType"/>
    ASPOSE_CELLS_API PivotItemPositionType GetBaseItemPositionType();
    /// <summary>
    /// Represents type of the base pivot item in the base field when the ShowDataAs calculation is in use.
    /// Valid only for data fields.
    /// Because PivotItemPosition.Custom is only for read,if you need to set PivotItemPosition.Custom,
    /// please set PivotField.BaseItemIndex attribute.
    /// </summary>
    /// <see cref="PivotItemPositionType"/>
    ASPOSE_CELLS_API void SetBaseItemPositionType(PivotItemPositionType value);
    /// <summary>
    /// Represents the custom index of the pivot item in the base field when the ShowDataAs calculation is in use.
    /// Valid only for data fields.
    /// </summary>
    ASPOSE_CELLS_API int32_t GetBaseItemIndex();
    /// <summary>
    /// Represents the custom index of the pivot item in the base field when the ShowDataAs calculation is in use.
    /// Valid only for data fields.
    /// </summary>
    ASPOSE_CELLS_API void SetBaseItemIndex(int32_t value);
    
};

} } }

#endif
