// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_MERGEEMPTYTDTYPE_H
#define ASPOSE_CELLS_MERGEEMPTYTDTYPE_H

namespace Aspose { namespace Cells {

/// <summary>
/// Represents the merge type for empty TD element when exporting file to html.
/// </summary>
enum class MergeEmptyTdType {
    /// <summary>
    /// Display like MS Excel.
    /// </summary>
    Default,
    /// <summary>
    /// Empty TD elements will not be merged when exporting file to html.
    /// This will generate a significantly larger html file.
    /// </summary>
    None,
    /// <summary>
    /// Merging empty TD element forcedly when exporting file to html.
    /// The size of html file will be reduced significantly after setting value to true.
    /// If you want to import the html file to excel or export perfect grid lines when saving file to html,
    /// please keep the default value.
    /// </summary>
    MergeForcely,
};

} }

#endif
