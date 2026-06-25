/*
 *  W25N02KV_Config.h
 *
 *  Created on: Dec 26, 2025
 *  Author: Henry
 */

#ifndef HAL_W25N02KV_CONFIG_H_
#define HAL_W25N02KV_CONFIG_H_

/// ---------------------------------------------------------------------------
/// Device Information (From FEATURES)
/// ---------------------------------------------------------------------------
#define W25N02KV_CAPACITY_BITS     (2UL * 1024UL * 1024UL * 1024UL) /// 2G-bit
#define W25N02KV_CAPACITY_BYTES    (256UL * 1024UL * 1024UL)        /// 256MB (Main area)
#define W25N02KV_CAPACITY_MB       (W25N02KV_CAPACITY_BYTES / (1024UL * 1024UL))

/// ---------------------------------------------------------------------------
/** W25N02KV NAND FLASH Organization (記憶體組織結構)
 *
 *  Page 結構
 *  - Main  Area  : 2048 Bytes (實際資料區)
 *  - Spare Area  : 128  Bytes (OOB / ECC / Metadata)
 *  - Page  Total : 2176 Bytes (Main + Spare)
 *
 *  Block 結構:
 *  - Pages per Block : 64 Pages
 *  - Erase Unit      : Block (依照 Main Area = 128KB)
 *
 *  備註:
 *  - Block Erase 時 "不包含" Spare Area
 *  - 100000 Program / Erase Endurance Cycles (Block)
 */
/// ---------------------------------------------------------------------------
#define PAGE_MAIN_SIZE             2048    							   /// Main Area page (2KB 資料區)
#define PAGE_SPARE_SIZE            128     							   /// Spare / OOB area per page (ECC / Metadata)
#define PAGE_TOTAL_SIZE            (PAGE_MAIN_SIZE + PAGE_SPARE_SIZE)  /// 2,176B (Main + Spare)

#define PAGES_PER_BLOCK            64      							   /// 每個 Block 含 64 Pages
#define BLOCK_TOTAL_SIZE_BYTES     (PAGES_PER_BLOCK * PAGE_TOTAL_SIZE) /// 136KB (Block 總大小)
#define BLOCK_ERASE_SIZE_BYTES     (PAGES_PER_BLOCK * PAGE_MAIN_SIZE)  /// 128KB (Erase 單位大小)

#define TOTAL_BLOCKS               2048    							   /// 2048 blocks
#define TOTAL_PAGES                (TOTAL_BLOCKS * PAGES_PER_BLOCK)    /// 2048 * 64 Bytes = 128KB

#define BLOCK_PE_CYCLES            100000							   /// Block 最大刪寫次數 100000 Cycles

/// ---------------------------------------------------------------------------
/// Performance & Endurance
/// ---------------------------------------------------------------------------
#define W25N02KV_MAX_SPI_FREQ      104000000   /// 104MHz Standard/Dual/Quad
#define W25N02KV_EQUIV_DUAL_IO     (208000000) /// 104MHz x 2
#define W25N02KV_EQUIV_QUAD_IO     (416000000) /// 104MHz x 4

#define W25N02KV_SEQ_TRANSFER_MBPS 50          /// 50 MB/s sequential data rate

#define W25N02KV_ENDURANCE         100000      /// 100k P/E cycles
#define W25N02KV_DATA_RETENTION    10          /// 10 years

/// ---------------------------------------------------------------------------
/// Power
/// ---------------------------------------------------------------------------
#define W25N02KV_VCC_MIN           2.7f
#define W25N02KV_VCC_MAX           3.6f

#define W25N02KV_ACTIVE_CURRENT    25000   /// 25 mA
#define W25N02KV_STANDBY_CURRENT   10      /// 10 uA
#define W25N02KV_DEEP_POWERDOWN    1       /// 1 uA

#define W25N02KV_TEMP_MIN          (-40)
#define W25N02KV_TEMP_MAX          (85)    /// up to 105°C for industrial plus grade

/// ---------------------------------------------------------------------------
/// Special Features
/// ---------------------------------------------------------------------------
/// Built-in ECC: On-chip 8-bit ECC
#define W25N02KV_ECC_ENABLE        1

/// ECC-Protected Factory Invalid block info: Block 0-7 and Block 2044-2047
#define W25N02KV_FACTORY_BADBLOCK_PROTECTED 1
#define FACTORY_INFO_BLOCK_START   0
#define FACTORY_INFO_BLOCK_END     8
#define FACTORY_INFO_BLOCK2_START  2043
#define FACTORY_INFO_BLOCK2_END    2047

/// OTP pages
#define W25N02KV_OTP_PAGES         2

/// ---------------------------------------------------------------------------
/// Address Calculation Macros
/// ---------------------------------------------------------------------------
#define PAGE_ADDR(block, page)     ((block) * PAGES_PER_BLOCK + (page))
#define BLOCK_ADDR(page_addr)      ((page_addr) / PAGES_PER_BLOCK)

/// ---------------------------------------------------------------------------
/// Data Pattern
/// ---------------------------------------------------------------------------

/// Status after erase block
#define NAND_ERASED_STATE          0xFF

#endif /* HAL_W25N02KV_CONFIG_H_ */
