// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_UTILITY_CONVERSIONUTILITY_H
#define ASPOSE_CELLS_UTILITY_CONVERSIONUTILITY_H

#include "Aspose.Cells/Export.h"
#include "Aspose.Cells/U16String.h"

namespace Aspose { namespace Cells {
    class LoadOptions;
    class SaveOptions;
} }

namespace Aspose { namespace Cells { namespace Utility {

using namespace Aspose::Cells;

class ConversionUtility_Impl;

/// <summary>
/// Represents converting files other formats.
/// </summary>
class ConversionUtility {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    ConversionUtility_Impl* _impl;
    
public:
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API ConversionUtility(ConversionUtility_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API ConversionUtility(const ConversionUtility& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~ConversionUtility();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API ConversionUtility& operator=(const ConversionUtility& src);
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
    /// Converts Excel files to other formats.
    /// </summary>
    /// <param name="source">The source file name.</param>
    /// <param name="saveAs">The file name of expected file.</param>
    ASPOSE_CELLS_API static void Convert(const U16String& source, const U16String& saveAs);
    /// <summary>
    /// Converts Excel files to other formats.
    /// </summary>
    /// <param name="source">The source file name.</param>
    /// <param name="saveAs">The file name of expected file.</param>
    ASPOSE_CELLS_API static void Convert(const char16_t* source, const char16_t* saveAs);
    /// <summary>
    /// Converts Excel files to other formats.
    /// </summary>
    /// <param name="source">The source file name.</param>
    /// <param name="loadOptions">The options of loading the source file.</param>
    /// <param name="saveAs">The file name of expected file.</param>
    /// <param name="saveOptions">The options of saving the file.</param>
    ASPOSE_CELLS_API static void Convert(const U16String& source, const LoadOptions& loadOptions, const U16String& saveAs, const SaveOptions& saveOptions);
    /// <summary>
    /// Converts Excel files to other formats.
    /// </summary>
    /// <param name="source">The source file name.</param>
    /// <param name="loadOptions">The options of loading the source file.</param>
    /// <param name="saveAs">The file name of expected file.</param>
    /// <param name="saveOptions">The options of saving the file.</param>
    ASPOSE_CELLS_API static void Convert(const char16_t* source, const LoadOptions& loadOptions, const char16_t* saveAs, const SaveOptions& saveOptions);
    
};

} } }

#endif
