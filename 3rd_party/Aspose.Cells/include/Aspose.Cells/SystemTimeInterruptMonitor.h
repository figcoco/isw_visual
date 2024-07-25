// Copyright (c) 2001-2024 Aspose Pty Ltd. All Rights Reserved.
// Powered by Aspose.Cells.
#ifndef ASPOSE_CELLS_SYSTEMTIMEINTERRUPTMONITOR_H
#define ASPOSE_CELLS_SYSTEMTIMEINTERRUPTMONITOR_H

#include "Aspose.Cells/Export.h"

namespace Aspose { namespace Cells {

class SystemTimeInterruptMonitor_Impl;

/// <summary>
/// Simple implementation of <see cref="AbstractInterruptMonitor"/> by checking and comparing current system time with user specified limit.
/// </summary>
/// <remarks>This implementation is just a simple solution for simple scenarios.
/// It needs to frequently retrieve and check the system time so itself may have a negative impact on performance to some extent.
/// </remarks>
class SystemTimeInterruptMonitor {
public:
    /// <summary>
    /// The implementation object.
    /// </summary>
    SystemTimeInterruptMonitor_Impl* _impl;
    
public:
    /// <summary>
    /// Constructs one interruption monitor.
    /// </summary>
    /// <param name="terminateWithoutException"><see cref="AbstractInterruptMonitor.TerminateWithoutException"/></param>
    ASPOSE_CELLS_API explicit SystemTimeInterruptMonitor(bool terminateWithoutException);
    /// <summary>
    /// Constructs from an implementation object.
    /// </summary>
    ASPOSE_CELLS_API SystemTimeInterruptMonitor(SystemTimeInterruptMonitor_Impl* impl);
    /// <summary>
    /// Copy constructor.
    /// </summary>
    ASPOSE_CELLS_API SystemTimeInterruptMonitor(const SystemTimeInterruptMonitor& src);
    /// <summary>
    /// Destructor.
    /// </summary>
    ASPOSE_CELLS_API ~SystemTimeInterruptMonitor();
    /// <summary>
    /// operator=
    /// </summary>
    ASPOSE_CELLS_API SystemTimeInterruptMonitor& operator=(const SystemTimeInterruptMonitor& src);
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
    /// Starts the monitor with the specified time limit. The start time to calculate time cost is just when this method is called,
    /// so the procedure which needs to be monitored should be started just after this call.
    /// </summary>
    /// <param name="msLimit">time limit(ms) to require the interruption.</param>
    ASPOSE_CELLS_API void StartMonitor(int32_t msLimit);
    /// <summary>
    /// This implementation just checks whether the time cost(from the time when starting this monitor to now) is greater than user specified limit.
    /// </summary>
    ASPOSE_CELLS_API bool IsInterruptionRequested();
    /// <summary>
    /// See <see cref="AbstractInterruptMonitor.TerminateWithoutException"/>.
    /// This property is specified by user when constructing this monitor instance.
    /// </summary>
    ASPOSE_CELLS_API bool GetTerminateWithoutException();
    
};

} }

#endif
