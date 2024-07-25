// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_HTMLTABLELOADOPTIONCOLLECTION_H
#define ASPOSE_CELLS_HTMLTABLELOADOPTIONCOLLECTION_H

#include "Aspose.Cells/Export.h"
#include "Aspose.Cells/U16String.h"

namespace Aspose { namespace Cells {
    class HtmlTableLoadOption;
} }

namespace Aspose { namespace Cells {

class HtmlTableLoadOptionCollection_Impl;

/// <summary>
/// Represents the table options when importing html.
/// </summary>
class HtmlTableLoadOptionCollection {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    HtmlTableLoadOptionCollection_Impl* _impl;
    
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    ASPOSE_CELLS_API HtmlTableLoadOptionCollection();
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API HtmlTableLoadOptionCollection(HtmlTableLoadOptionCollection_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API HtmlTableLoadOptionCollection(const HtmlTableLoadOptionCollection& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~HtmlTableLoadOptionCollection();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API HtmlTableLoadOptionCollection& operator=(const HtmlTableLoadOptionCollection& src);
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
    /// Indicates whether generate list objects from imported tables.
    /// The default value is false.
    /// </summary>
    ASPOSE_CELLS_API bool GetTableToListObject();
    /// <summary>
    /// Indicates whether generate list objects from imported tables.
    /// The default value is false.
    /// </summary>
    ASPOSE_CELLS_API void SetTableToListObject(bool value);
    /// <summary>
    /// Gets the <see cref="HtmlTableLoadOption"/> element at the specified index.
    /// </summary>
    /// <param name="index">The zero based index of the element.</param>
    /// <returns>The element at the specified index.</returns>
    ASPOSE_CELLS_API HtmlTableLoadOption Get(int32_t index);
    /// <summary>
    /// Adds one HtmlTableLoadOption into this collection.
    /// </summary>
    /// <param name="item">one HtmlTableLoadOption</param>
    /// <returns>the index of the added item</returns>
    ASPOSE_CELLS_API int32_t Add(const HtmlTableLoadOption& item);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableIndex">Table index</param>
    /// <returns></returns>
    ASPOSE_CELLS_API int32_t Add(int32_t tableIndex);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableId">Table ID</param>
    /// <returns></returns>
    ASPOSE_CELLS_API int32_t Add(const U16String& tableId);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableId">Table ID</param>
    /// <returns></returns>
    ASPOSE_CELLS_API int32_t Add(const char16_t* tableId);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableIndex">Table index</param>
    /// <param name="targetSheetIndex">The target index of worksheet in Excel</param>
    ASPOSE_CELLS_API int32_t Add(int32_t tableIndex, int32_t targetSheetIndex);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableId">Table ID</param>
    /// <param name="targetSheetIndex">The target index of worksheet in Excel</param>
    /// <returns></returns>
    ASPOSE_CELLS_API int32_t Add(const U16String& tableId, int32_t targetSheetIndex);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableId">Table ID</param>
    /// <param name="targetSheetIndex">The target index of worksheet in Excel</param>
    /// <returns></returns>
    ASPOSE_CELLS_API int32_t Add(const char16_t* tableId, int32_t targetSheetIndex);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableIndex">Table index</param>
    /// <param name="targetSheetIndex">The target index of worksheet in Excel</param>
    /// <param name="originalSheetIndex">The original index of worksheet in the html</param>
    ASPOSE_CELLS_API int32_t Add(int32_t tableIndex, int32_t targetSheetIndex, int32_t originalSheetIndex);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableId">Table ID</param>
    /// <param name="targetSheetIndex">The target index of worksheet in Excel</param>
    /// <param name="originalSheetIndex">The original index of worksheet in the html</param>
    /// <returns></returns>
    ASPOSE_CELLS_API int32_t Add(const U16String& tableId, int32_t targetSheetIndex, int32_t originalSheetIndex);
    /// <summary>
    /// Add a HtmlTableLoadOption to the list.
    /// </summary>
    /// <param name="tableId">Table ID</param>
    /// <param name="targetSheetIndex">The target index of worksheet in Excel</param>
    /// <param name="originalSheetIndex">The original index of worksheet in the html</param>
    /// <returns></returns>
    ASPOSE_CELLS_API int32_t Add(const char16_t* tableId, int32_t targetSheetIndex, int32_t originalSheetIndex);
    
    ASPOSE_CELLS_API int32_t GetCount();
};

} }

#endif
