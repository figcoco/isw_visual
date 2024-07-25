/*! \file netcdf_meta.h
 *
 * Meta information for libnetcdf which can be used by other packages which
 * depend on libnetcdf.
 *
 * This file is automatically generated by the build system
 * at configure time, and contains information related to
 * how libnetcdf was built.  It will not be required to
 * include this file unless you want to probe the capabilities
 * of libnetcdf. This should ideally only happen when configuring
 * a project which depends on libnetcdf.  At configure time,
 * the dependent project can set its own macros which can be used
 * in conditionals.
 *
 * Copyright 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
 * 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014,
 * 2015, 2016, 2017, 2018
 * University Corporation for Atmospheric Research/Unidata.
 *
 * See \ref copyright file for more info.
 */

#ifndef NETCDF_META_H
#define NETCDF_META_H

#define NC_VERSION_MAJOR 4 /*!< netcdf-c major version. */
#define NC_VERSION_MINOR 9 /*!< netcdf-c minor version. */
#define NC_VERSION_PATCH 2 /*!< netcdf-c patch version. */
#define NC_VERSION_NOTE  "" /*!< netcdf-c note. May be blank. */

/*! netcdf-c version string.
 *
 * The format of the netcdf-c version string is as follows:
 * \code
 * NC_VERSION_MAJOR.NC_VERSION_MINOR.NC_VERSION_PATCH.NC_VERSION_NOTE
 * \endcode
 * Note that the trailing NC_VERSION_NOTE may be empty. It serves for
 * identifiers such as '-rc1', etc.
 */
#define NC_VERSION       "4.9.2"

#define NC_HAS_NC2       1 /*!< API version 2 support. */
#define NC_HAS_NC4       1 /*!< API version 4 support. */
#define NC_HAS_HDF4      0 /*!< HDF4 support. */
#define NC_HAS_HDF5      1 /*!< HDF5 support. */
#define NC_HAS_SZIP      0 /*!< szip support */
#define NC_HAS_SZIP_WRITE 0 /*!< szip write support */
#define NC_HAS_DAP2      0 /*!< DAP2 support. */
#define NC_HAS_DAP4      0 /*!< DAP4 support. */
#define NC_HAS_BYTERANGE 1 /*!< Byterange support. */
#define NC_HAS_DISKLESS  1 /*!< diskless support. */
#define NC_HAS_MMAP      0 /*!< mmap support. */
#define NC_HAS_JNA       0 /*!< jna support. */
#define NC_HAS_PNETCDF   0 /*!< PnetCDF support. */
#define NC_HAS_PARALLEL4 0 /*!< parallel IO support via HDF5 */
#define NC_HAS_PARALLEL  0 /*!< parallel IO support via HDF5 and/or PnetCDF. */

#define NC_HAS_CDF5          1 /*!< CDF5 support. */
#define NC_HAS_ERANGE_FILL   1 /*!< ERANGE_FILL Support. */
#define NC_RELAX_COORD_BOUND 1 /*!< Always allow 0 counts in parallel I/O. */
#define NC_DISPATCH_VERSION  5 /*!< Dispatch table version. */
#define NC_HAS_PAR_FILTERS   1 /* Parallel I/O with filter support. */
#define NC_HAS_NCZARR        1 /*!< Parallel I/O with filter support. */
#define NC_HAS_MULTIFILTERS  1 /*!< Nczarr support. */
#define NC_HAS_LOGGING       0 /*!< Logging support. */
#define NC_HAS_QUANTIZE      1 /*!< Quantization support. */
#define NC_HAS_ZSTD          0 /*!< Zstd support. */
#define NC_HAS_BENCHMARKS    0 /*!< Benchmarks. */
#define NC_HAS_S3            0 /*!< Amazon S3 Support. */
#define NC_HAS_BLOSC         0 /*!< Blosc Support. */
#define NC_HAS_BZ2           1 /*!< bzip2 support */

#endif