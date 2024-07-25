// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_DELETEBLANKOPTIONS_H
#define ASPOSE_CELLS_DELETEBLANKOPTIONS_H

#include "Aspose.Cells/Export.h"
#include "Aspose.Cells/DeleteOptions.h"

namespace Aspose { namespace Cells {

class DeleteBlankOptions_Impl;

/// <summary>
/// Represents the setting of deleting blank cells/rows/columns.
/// </summary>
class DeleteBlankOptions : public DeleteOptions {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    DeleteBlankOptions_Impl* _impl;
    
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    ASPOSE_CELLS_API DeleteBlankOptions();
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API DeleteBlankOptions(DeleteBlankOptions_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API DeleteBlankOptions(const DeleteBlankOptions& src);
    /// <summary>
    /// Constructs from a parent object.
    /// </summary>
    ASPOSE_CELLS_API DeleteBlankOptions(const DeleteOptions& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~DeleteBlankOptions();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API DeleteBlankOptions& operator=(const DeleteBlankOptions& src);
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
    /// Whether one cell will be taken as blank when its value is empty string. Default value is true.
    /// </summary>
    ASPOSE_CELLS_API bool GetEmptyStringAsBlank();
    /// <summary>
    /// Whether one cell will be taken as blank when its value is empty string. Default value is true.
    /// </summary>
    ASPOSE_CELLS_API void SetEmptyStringAsBlank(bool value);
    /// <summary>
    /// Whether one cell will be taken as blank when it is formula and the calculated result is null or empty string. Default value is false.
    /// </summary>
    /// <remarks>
    /// Generally user should make sure the formulas have been calculated before deleting operation with this property as true.
    /// Otherwise all newly cretaed formulas by normal apis such as <see cref="Cell.Formula"/> will be taken as blank and may be deleted
    /// because before calculation their calculated results are all null.
    /// </remarks>
    ASPOSE_CELLS_API bool GetEmptyFormulaValueAsBlank();
    /// <summary>
    /// Whether one cell will be taken as blank when it is formula and the calculated result is null or empty string. Default value is false.
    /// </summary>
    /// <remarks>
    /// Generally user should make sure the formulas have been calculated before deleting operation with this property as true.
    /// Otherwise all newly cretaed formulas by normal apis such as <see cref="Cell.Formula"/> will be taken as blank and may be deleted
    /// because before calculation their calculated results are all null.
    /// </remarks>
    ASPOSE_CELLS_API void SetEmptyFormulaValueAsBlank(bool value);
    
};

} }

#endif
