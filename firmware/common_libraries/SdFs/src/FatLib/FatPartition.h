/**
 * Copyright (c) 20011-2017 Bill Greiman
 * This file is part of the SdFs library for SD memory cards.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef FatPartition_h
#define FatPartition_h
/**
 * \file
 * \brief FatPartition class
 */
#include <stddef.h>
#include "FatLibConfig.h"
#include "SysCall.h"
#include "BlockDevice.h"
#include "../common/FsStructs.h"

/** Type for FAT12 partition */
const uint8_t FAT_TYPE_FAT12 = 12;

/** Type for FAT12 partition */
const uint8_t FAT_TYPE_FAT16 = 16;

/** Type for FAT12 partition */
const uint8_t FAT_TYPE_FAT32 = 32;

//------------------------------------------------------------------------------
// Forward declaration of FatPartition.
class FatPartition;
//------------------------------------------------------------------------------
/**
 * \brief Cache for an raw data sector.
 */
union cache_t {
  /** Used to access cached file data sectors. */
  uint8_t  data[512];
  /** Used to access cached FAT16 entries. */
  uint16_t fat16[256];
  /** Used to access cached FAT32 entries. */
  uint32_t fat32[128];
  /** Used to access cached directory entries. */
  dir_t    dir[16];
};
//==============================================================================
/**
 * \class FatCache
 * \brief Sector cache.
 */
class FatCache {
 public:
  /** Cached sector is dirty */
  static const uint8_t CACHE_STATUS_DIRTY = 1;
  /** Cashed sector is FAT entry and must be mirrored in second FAT. */
  static const uint8_t CACHE_STATUS_MIRROR_FAT = 2;
  /** Cache sector status bits */
  static const uint8_t CACHE_STATUS_MASK
    = CACHE_STATUS_DIRTY | CACHE_STATUS_MIRROR_FAT;
  /** Sync existing sector but do not read new sector. */
  static const uint8_t CACHE_OPTION_NO_READ = 4;
  /** Cache sector for read. */
  static const uint8_t CACHE_FOR_READ = 0;
  /** Cache sector for write. */
  static const uint8_t CACHE_FOR_WRITE = CACHE_STATUS_DIRTY;
  /** Reserve cache sector for write - do not read from sector device. */
  static const uint8_t CACHE_RESERVE_FOR_WRITE
    = CACHE_STATUS_DIRTY | CACHE_OPTION_NO_READ;
  /** \return Cache sector address. */
  cache_t* buffer() {
    return &m_buffer;
  }
  /** Set current sector dirty. */
  void dirty() {
    m_status |= CACHE_STATUS_DIRTY;
  }
  /** Initialize the cache.
   * \param[in] vol FatPartition that owns this FatCache.
   */
  void init(FatPartition *vol) {
    m_part = vol;
    invalidate();
  }
  /** Invalidate current cache sector. */
  void invalidate() {
    m_status = 0;
    m_lbn = 0XFFFFFFFF;
  }
  /** \return dirty status */
  bool isDirty() {
    return m_status & CACHE_STATUS_DIRTY;
  }
  /** \return Logical sector number for cached sector. */
  uint32_t sector() {
    return m_lbn;
  }
  /** Read a sector into the cache.
   * \param[in] sector Sector to read.
   * \param[in] option mode for cached sector.
   * \return Address of cached sector. */
  cache_t* read(uint32_t sector, uint8_t option);
  /** Write current sector if dirty.
   * \return true for success else false.
   */
  bool sync();

 private:
  uint8_t m_status;
  FatPartition* m_part;
  uint32_t m_lbn;
  cache_t m_buffer;
};
//==============================================================================
/**
 * \class FatPartition
 * \brief Access FAT16 and FAT32 partitions on raw file devices.
 */
class FatPartition {
 public:
  /** Create an instance of FatPartition
   */
  FatPartition() : m_fatType(0) {}

  /** \return The shift count required to multiply by bytesPerCluster. */
  uint8_t bytesPerClusterShift() {
    return m_sectorsPerClusterShift + m_bytesPerSectorShift;
  }
  /** \return Number of bytes in a cluster. */
  uint16_t bytesPerCluster() {
    return m_bytesPerSector << m_sectorsPerClusterShift;
  }
  /** \return Number of bytes per sector. */
  uint16_t bytesPerSector() {
    return m_bytesPerSector;
  }
  /** \return The shift count required to multiply by bytesPerCluster. */
  uint8_t bytesPerSectorShift() {
    return m_bytesPerSectorShift;
  }
  /** \return Mask for sector offset. */
  uint16_t sectorMask() {
    return m_sectorMask;
  }
  /** \return The volume's cluster size in sectors. */
  uint8_t sectorsPerCluster() const {
    return m_sectorsPerCluster;
  }
  /** \return The number of sectors in one FAT. */
  uint32_t sectorsPerFat()  const {
    return m_sectorsPerFat;
  }
  /** Clear the cache and returns a pointer to the cache.  Not for normal apps.
   * \return A pointer to the cache buffer or zero if an error occurs.
   */
  cache_t* cacheClear() {
    if (!cacheSync()) {
      return nullptr;
    }
    m_cache.invalidate();
    return m_cache.buffer();
  }
  /** \return The total number of clusters in the volume. */
  uint32_t clusterCount() const {
    return m_lastCluster - 1;
  }
  /** \return The shift count required to multiply by sectorsPerCluster. */
  uint8_t sectorsPerClusterShift() const {
    return m_sectorsPerClusterShift;
  }
  /** \return The logical sector number for the start of file data. */
  uint32_t dataStartSector() const {
    return m_dataStartSector;
  }
  /** \return The number of File Allocation Tables. */
  uint8_t fatCount() {
    return 2;
  }
  /** \return The logical sector number for the start of the first FAT. */
  uint32_t fatStartSector() const {
    return m_fatStartSector;
  }
  /** \return The FAT type of the volume. Values are 12, 16 or 32. */
  uint8_t fatType() const {
    return m_fatType;
  }
  /** Volume free space in clusters.
   *
   * \return Count of free clusters for success or -1 if an error occurs.
   */
  int32_t freeClusterCount();
  /** Initialize a FAT partition.
   *
   * \param[in] dev BlockDevice for this partition.
   * \param[in] part The partition to be used.  Legal values for \a part are
   * 1-4 to use the corresponding partition on a device formatted with
   * a MBR, Master Boot Record, or zero if the device is formatted as
   * a super floppy with the FAT boot sector in sector zero.
   *
   * \return The value true is returned for success and
   * the value false is returned for failure.
   */
  bool init(BlockDevice* dev, uint8_t part);
  /** \return The number of entries in the root directory for FAT16 volumes. */
  uint16_t rootDirEntryCount() const {
    return m_rootDirEntryCount;
  }
  /** \return The logical sector number for the start of the root directory
       on FAT16 volumes or the first cluster number on FAT32 volumes. */
  uint32_t rootDirStart() const {
    return m_rootDirStart;
  }
  /** \return The number of sectors in the volume */
  uint32_t volumeSectorCount() const {
    return sectorsPerCluster()*clusterCount();
  }
  /** Wipe all data from the volume.
   * \param[in] pr print stream for status dots.
   * \return true for success else false.
   */
  bool wipe(print_t* pr = nullptr);
  /** Debug access to FAT table
   *
   * \param[in] n cluster number.
   * \param[out] v value of entry
   * \return true for success or false for failure
   */
  int8_t dbgFat(uint32_t n, uint32_t* v) {
    return fatGet(n, v);
  }
//------------------------------------------------------------------------------
 private:
  // Allow FatFile and FatCache access to FatPartition private functions.
  friend class FatCache;
  friend class FatFile;
//------------------------------------------------------------------------------
  static const uint8_t  m_bytesPerSectorShift = 9;
  static const uint16_t m_bytesPerSector = 512;
  static const uint16_t m_sectorMask = 0x1FF;
//------------------------------------------------------------------------------
  BlockDevice* m_blockDev;            // sector device
  uint8_t  m_sectorsPerCluster;       // Cluster size in sectors.
  uint8_t  m_clusterSectorMask;       // Mask to extract sector of cluster.
  uint8_t  m_sectorsPerClusterShift;  // Cluster count to sector count shift.
  uint8_t  m_fatType;                 // Volume type (12, 16, OR 32).
  uint16_t m_rootDirEntryCount;       // Number of entries in FAT16 root dir.
  uint32_t m_allocSearchStart;        // Start cluster for alloc search.
  uint32_t m_sectorsPerFat;           // FAT size in sectors
  uint32_t m_dataStartSector;         // First data sector number.
  uint32_t m_fatStartSector;          // Start sector for first FAT.
  uint32_t m_lastCluster;             // Last cluster number in FAT.
  uint32_t m_rootDirStart;            // Start sector FAT16, cluster FAT32.
//------------------------------------------------------------------------------
  // sector I/O functions.
  bool readSector(uint32_t sector, uint8_t* dst) {
    return m_blockDev->readSector(sector, dst);
  }
  bool syncDevice() {
    return m_blockDev->syncDevice();
  }
  bool writeSector(uint32_t sector, const uint8_t* src) {
    return m_blockDev->writeSector(sector, src);
  }
#if USE_MULTI_SECTOR_IO
  bool readSectors(uint32_t sector, uint8_t* dst, size_t ns) {
    return m_blockDev->readSectors(sector, dst, ns);
  }
  bool writeSectors(uint32_t sector, const uint8_t* src, size_t ns) {
    return m_blockDev->writeSectors(sector, src, ns);
  }
#endif  // USE_MULTI_SECTOR_IO
#if MAINTAIN_FREE_CLUSTER_COUNT
  int32_t  m_freeClusterCount;     // Count of free clusters in volume.
  void setFreeClusterCount(int32_t value) {
    m_freeClusterCount = value;
  }
  void updateFreeClusterCount(int32_t change) {
    if (m_freeClusterCount >= 0) {
      m_freeClusterCount += change;
    }
  }
#else  // MAINTAIN_FREE_CLUSTER_COUNT
  void setFreeClusterCount(int32_t value) {
    (void)value;
  }
  void updateFreeClusterCount(int32_t change) {
    (void)change;
  }
#endif  // MAINTAIN_FREE_CLUSTER_COUNT

// sector caches
  FatCache m_cache;
#if USE_SEPARATE_FAT_CACHE
  FatCache m_fatCache;
  cache_t* cacheFetchFat(uint32_t sector, uint8_t options) {
    return m_fatCache.read(sector,
                           options | FatCache::CACHE_STATUS_MIRROR_FAT);
  }
  bool cacheSync() {
    return m_cache.sync() && m_fatCache.sync() && syncDevice();
  }
#else  //
  cache_t* cacheFetchFat(uint32_t sector, uint8_t options) {
    return cacheFetchData(sector,
                          options | FatCache::CACHE_STATUS_MIRROR_FAT);
  }
  bool cacheSync() {
    return m_cache.sync() && syncDevice();
  }
#endif  // USE_SEPARATE_FAT_CACHE
  cache_t* cacheFetchData(uint32_t sector, uint8_t options) {
    return m_cache.read(sector, options);
  }
  void cacheInvalidate() {
    m_cache.invalidate();
  }
  bool cacheSyncData() {
    return m_cache.sync();
  }
  cache_t *cacheAddress() {
    return m_cache.buffer();
  }
  uint32_t cacheSectorNumber() {
    return m_cache.sector();
  }
  void cacheDirty() {
    m_cache.dirty();
  }
//------------------------------------------------------------------------------
  bool allocateCluster(uint32_t current, uint32_t* next);
  bool allocContiguous(uint32_t count, uint32_t* firstCluster);
  uint8_t sectorOfCluster(uint32_t position) const {
    return (position >> 9) & m_clusterSectorMask;
  }
  uint32_t clusterStartSector(uint32_t cluster) const;
  int8_t fatGet(uint32_t cluster, uint32_t* value);
  bool fatPut(uint32_t cluster, uint32_t value);
  bool fatPutEOC(uint32_t cluster) {
    return fatPut(cluster, 0x0FFFFFFF);
  }
  bool freeChain(uint32_t cluster);
  bool isEOC(uint32_t cluster) const {
    return cluster > m_lastCluster;
  }
};
#endif  // FatPartition
