// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_ODS_OPENDOCUMENTFORMATVERSIONTYPE_H
#define ASPOSE_CELLS_ODS_OPENDOCUMENTFORMATVERSIONTYPE_H

namespace Aspose { namespace Cells { namespace Ods {

/// <summary>
/// Open Document Format version type.
/// </summary>
enum class OpenDocumentFormatVersionType {
    /// <summary>
    /// None strict.
    /// </summary>
    /// <remarks>
    /// There are some difference between Excel and ODF.
    /// In order to keep the data of Excel file, we can not follow the strict of ODF.
    /// </remarks>
    None,
    /// <summary>
    /// ODF Version 1.1
    /// </summary>
    Odf11,
    /// <summary>
    /// ODF Version 1.2
    /// </summary>
    Odf12,
    /// <summary>
    /// ODF Version 1.3
    /// </summary>
    Odf13,
};

} } }

#endif
