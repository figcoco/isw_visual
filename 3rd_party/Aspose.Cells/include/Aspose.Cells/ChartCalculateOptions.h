// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_CHARTS_CHARTCALCULATEOPTIONS_H
#define ASPOSE_CELLS_CHARTS_CHARTCALCULATEOPTIONS_H

#include "Aspose.Cells/Export.h"

namespace Aspose { namespace Cells { namespace Charts {

class ChartCalculateOptions_Impl;

/// <summary>
/// Represents the options for calculating chart.
/// </summary>
class ChartCalculateOptions {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    ChartCalculateOptions_Impl* _impl;
    
public:
    /// <summary>
    /// Creates the options for calculating chart.
    /// </summary>
    ASPOSE_CELLS_API ChartCalculateOptions();
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API ChartCalculateOptions(ChartCalculateOptions_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API ChartCalculateOptions(const ChartCalculateOptions& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~ChartCalculateOptions();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API ChartCalculateOptions& operator=(const ChartCalculateOptions& src);
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
    /// Whether update all data points when performing the chart calculation. Default: False.
    /// When you want to get the value for each data point in the chart specifically, set it to true.
    /// If this parameter is set to True, the new data points may be generated when chart is calculated. This could make the Excel file larger.
    /// </summary>
    ASPOSE_CELLS_API bool GetUpdateAllPoints();
    /// <summary>
    /// Whether update all data points when performing the chart calculation. Default: False.
    /// When you want to get the value for each data point in the chart specifically, set it to true.
    /// If this parameter is set to True, the new data points may be generated when chart is calculated. This could make the Excel file larger.
    /// </summary>
    ASPOSE_CELLS_API void SetUpdateAllPoints(bool value);
    
};

} } }

#endif
