# STM32 W25N02KV SPI NAND Flash Driver

## Project Overview / 專案概述

This project implements a firmware driver and validation framework for the **Winbond W25N02KV SPI NAND Flash** on an STM32 MCU platform.

本專案主要目標是使用 STM32 MCU 控制 **Winbond W25N02KV SPI NAND Flash**，實作底層 NAND Flash Command Driver 與驗證流程。

專案內容包含：

- Device Reset
- JEDEC ID Read
- Status Register Read / Write
- Write Enable / Write Disable
- 128KB Block Erase
- Page Program
- Page Data Read
- Buffer Read
- ECC Status Check
- Factory Bad Block Scan
- Bad Block Table Management
- Pattern-based Read / Write Verification
- Random Load Program Test
- Endurance Test

此專案重點不是單純透過 SPI 傳輸資料，而是理解並實作 **NAND Flash 的完整操作流程、狀態檢查、錯誤判斷與資料驗證機制**。

---

## Hardware Platform / 硬體平台

| Item | Description |
|---|---|
| MCU Board  | STM32H735G-DK |
| MCU Part   | STM32H735IGK6 |
| CPU Core   | Arm® Cortex®-M7 |
| NAND Flash | Winbond W25N02KV SPI NAND Flash |
| Flash Capacity | 2Gb / 256MB |
| Flash Type | NAND Flash |
| Interface  | SPI  |
| Development IDE   | STM32CubeIDE |
| Firmware Code  | C |

---

## Storage Classification / 儲存介質分類

W25N02KV 屬於以下儲存介質分類：

```text
Storage Media / 儲存介質
└── Semiconductor Storage / 半導體儲存介質
    └── Non-Volatile Memory / 非揮發性記憶體
        └── Flash Memory / 快閃記憶體
            └── NAND Flash
                └── SPI NAND Flash
                    └── Winbond W25N02KV
```

W25N02KV 本質上是 **NAND Flash**，只是對外透過 **SPI-compatible serial interface** 與 MCU 通訊。

也就是說：

```text
NAND Flash = 儲存介質 / 記憶體架構
SPI        = MCU 與 Flash 之間的通訊介面
SPI NAND   = NAND Flash + SPI 通訊介面
```

---

## Key Features / 專案功能

- SPI NAND command driver implementation
- Device reset sequence
- JEDEC ID read and device identification
- Read / write status register
- Write Enable / Write Disable control
- 128KB Block Erase
- Page Program operation
- Page Data Read operation
- Buffer Read operation
- ECC status parsing
- Program Fail / Erase Fail detection
- Factory Bad Block Scan
- Bad Block Table management
- Pattern-based read/write verification
- Random Load Program test
- Endurance test framework

---

## Firmware Architecture / 韌體架構

本專案採用分層設計，將底層 SPI Command、NAND 操作服務與測試流程分離。

```text
Application Layer
└── Validation tests and demo flows
    ├── Single Page Program / Read Test
    ├── Multiple Pattern Test
    ├── Random Load Program Test
    ├── Factory Bad Block Scan
    └── Endurance Test

Service Layer
└── High-level NAND operation services
    ├── Reset Service
    ├── Read Service
    ├── Program Service
    ├── Erase Service
    ├── Status Register Service
    └── Bad Block Table Service

Driver Layer
└── W25N02KV low-level command driver
    ├── Reset Command
    ├── JEDEC ID Command
    ├── Status Register Command
    ├── Program Command
    ├── Read Command
    └── Erase Command

HAL Layer
└── STM32 HAL SPI / GPIO control

Hardware Layer
└── STM32 MCU + W25N02KV SPI NAND Flash
```

### 設計重點

Driver Layer 負責處理最底層的 SPI command transaction，例如：

- `/CS` control
- Command transmit
- Address transmit
- Dummy clock
- Data transmit / receive
- Status register access

Service Layer 則將多個低階 Command 組合成完整 NAND 操作流程，例如：

```text
Erase Flow
Program Flow
Read Flow
Verify Flow
Bad Block Scan Flow
Endurance Test Flow
```

這樣可以避免 Application Layer 直接操作底層指令，使程式架構更清楚，也更接近實務 Firmware Driver 的設計方式。

---

## Supported NAND Flash Operations / 支援的 NAND Flash 指令

| Operation | Command | Description |
|---|---:|---|
| Device Reset | `FFh` | Reset SPI NAND device |
| Enable Reset | `66h` | Enable reset sequence |
| Reset Device | `99h` | Execute reset sequence |
| Read JEDEC ID | `9Fh` | Read manufacturer ID and device ID |
| Read Status Register | `0Fh / 05h` | Read NAND status registers |
| Write Status Register | `1Fh / 01h` | Configure writable status register bits |
| Write Enable | `06h` | Enable program / erase / register write |
| Write Disable | `04h` | Disable write operation |
| Block Erase | `D8h` | Erase one 128KB block |
| Load Program Data | `02h` | Load data into internal page buffer |
| Random Load Program | `84h` | Partially update page buffer |
| Program Execute | `10h` | Program buffer data into NAND array |
| Page Data Read | `13h` | Load NAND page into internal buffer |
| Read Data | `03h` | Read data from internal buffer |
| Fast Read | `0Bh` | High-speed buffer read |

---

## NAND Flash Program / Read Flow / 寫入與讀取驗證流程

典型的 Page Program + Read Verify 流程如下：

```text
1. Reset device
2. Read JEDEC ID
3. Write Enable
4. Erase target block
5. Poll BUSY bit until device is ready
6. Check Erase Fail bit
7. Write Enable
8. Load program data into page buffer
9. Execute page program
10. Poll BUSY bit until device is ready
11. Check Program Fail bit
12. Execute page data read
13. Poll BUSY bit until device is ready
14. Read data from internal buffer
15. Check ECC status
16. Compare read data with expected pattern
```

此流程驗證的不只是 SPI 通訊是否成功，而是 NAND Flash 是否依照正確流程完成：

```text
Erase → Program → Read → ECC Check → Data Compare
```

### 為什麼不能直接寫入 NAND Flash？

NAND Flash 與一般 RAM 不同，不能任意覆寫資料。

NAND Flash 寫入前通常必須先完成：

```text
Block Erase → Page Program → Page Read → Data Verify
```

原因是 NAND Flash 的基本限制：

```text
Erase 只能以 Block 為單位
Program 通常以 Page 為單位
已寫入的 bit 無法直接改回 erased state
資料可靠性需要 ECC 與狀態檢查
```

因此 Firmware 必須負責建立正確的操作流程，而不是單純送 SPI 資料。

---

## Status Register Handling / 狀態暫存器處理

NAND Flash 的 Program、Erase、Read 都不是送出 Command 後立即完成，而是由 NAND 內部 state machine 執行。

因此 Firmware 必須透過 Status Register 進行輪詢與錯誤檢查。

| Status Bit | Meaning |
|---|---|
| OIP / BUSY | Indicates whether an internal operation is still in progress |
| WEL | Write Enable Latch |
| E_FAIL | Erase operation failure |
| P_FAIL | Program operation failure |
| ECC Status | ECC result after page read |

### 本專案的處理方式

- Program / Erase 前先執行 `Write Enable`
- Program / Erase / Read 後輪詢 `BUSY / OIP`
- Erase 後檢查 `E_FAIL`
- Program 後檢查 `P_FAIL`
- Read 後檢查 `ECC Status`
- 最後執行資料比對，確認 Read Data 是否符合預期 Pattern

這樣可以避免 Firmware 在 NAND Flash 尚未完成內部操作時就進行下一個 Command。

---

## ECC Handling / ECC 狀態處理

Page Read 完成後，Firmware 會檢查 Status Register 中的 ECC Status 欄位。

ECC Status 用來判斷讀取結果是否正常：

```text
ECC Success
ECC Corrected
ECC Corrected Threshold
ECC Uncorrectable
```

這個機制可以協助 Firmware 判斷：

- 資料是否成功讀出
- 是否發生 bit flip
- 是否已由 NAND 內部 ECC 修正
- 是否已經接近 ECC correction threshold
- 是否出現 uncorrectable error
- 是否需要停止測試或避開該區塊

---

## Bad Block Management / 壞塊管理

NAND Flash 和 NOR Flash 不同，NAND Flash 出廠時就可能存在 factory bad block。

因此 NAND Firmware 不能假設每個 physical block 都可使用。

本專案實作 Factory Bad Block Scan，並建立 Bad Block Table。

```text
Factory Bad Block Scan
└── Scan block range
    ├── Read marker page
    ├── Check main area marker
    ├── Check spare area marker
    ├── Mark block as valid or invalid
    └── Update Bad Block Table
```

### Bad Block Scan 目的

- 掃描 NAND Flash 原廠標記的 invalid block
- 建立 Bad Block Table
- 後續 Program / Erase 測試時避開 bad block
- 避免將資料寫入不可靠的 physical block

Bad Block Management 是 NAND Flash Firmware 中非常重要的一部分，因為 NAND Flash 的設計本來就允許出廠時存在部分 invalid block。

---

## Validation Tests / 驗證測試

本專案包含多種 NAND Flash 驗證流程：

| Test Item | Purpose |
|---|---|
| Single Page Program / Read | Verify basic NAND write and read flow |
| Multiple Pattern Test | Verify data integrity with different data patterns |
| Random Load Program Test | Verify partial page buffer update behavior |
| Factory Bad Block Scan | Detect and record factory-marked bad blocks |
| Endurance Test | Repeated erase / program / read verification for reliability testing |

### Example Test Patterns

```text
0xAA
0x55
0x00
0xFF
```

每個測試流程都會檢查：

```text
Status Register
ECC Result
Program / Erase Fail Flag
Read Data Compare Result
```

---

## Test Flow Summary / 測試流程摘要

### Single Page Program / Read Test

```text
Reset Device
→ Read JEDEC ID
→ Erase Block
→ Load Program Data
→ Program Execute
→ Page Data Read
→ Read Data
→ ECC Check
→ Data Compare
→ Print Test Result
```

### Factory Bad Block Scan

```text
Reset Device
→ Scan Block Range
→ Read Bad Block Marker
→ Check Main Area / Spare Area
→ Mark Valid or Invalid
→ Update Bad Block Table
```

### Endurance Test

```text
Select Valid Block
→ Erase Block
→ Program Pages
→ Read Back Pages
→ Check ECC Status
→ Compare Data
→ Repeat P/E Cycle
→ Stop on Error or Finish Target Cycle
```

---

## Repository Structure / 專案結構

```text
.
├── Core
│   ├── Inc
│   └── Src
├── Drivers
│   ├── CMSIS
│   └── STM32H7xx_HAL_Driver
├── NandController
│   ├── Driver
│   ├── Service
│   └── Test
├── Debug
├── W25N02 Firmware.ioc
├── STM32H735IGKX_FLASH.ld
├── STM32H735IGKX_RAM.ld
└── README.md
```

> Note: The actual folder structure may vary depending on the STM32CubeIDE project configuration.

---

## Technical Highlights / 技術重點

- Implemented SPI NAND command sequence in C
- Controlled `/CS` timing through GPIO
- Implemented status polling instead of relying only on fixed delay
- Verified NAND operation result using status register flags
- Parsed ECC status after page read
- Designed service-layer APIs above low-level command driver
- Implemented Factory Bad Block Scan and Bad Block Table logic
- Built multiple validation flows for NAND Flash behavior verification
- Used STM32 HAL SPI and GPIO APIs for external memory control

---

## Key Firmware Concepts / 對應的韌體觀念

本專案涵蓋以下 Firmware / Embedded System 觀念：

```text
External IC Driver
SPI Communication
GPIO Chip Select Control
Command / Address / Data Phase
Status Register Polling
Erase-before-Program
Page / Block Architecture
ECC Status Handling
Bad Block Management
Validation Test Design
```

這些內容對應到實務 Firmware Driver 開發中常見的底層控制、錯誤處理與驗證流程。

---

## Problems Solved / 問題與處理方向

| Problem | Cause | Solution |
|---|---|---|
| NAND operation cannot be assumed complete immediately | Program / Erase / Read are internal self-timed operations | Added status register polling |
| Program or Erase may fail silently | NAND reports failure through status bits | Checked `P_FAIL` and `E_FAIL` |
| Read data may contain bit errors | NAND Flash may have bit flip behavior | Checked ECC status after read |
| Some blocks may be invalid from factory | NAND Flash may contain factory bad blocks | Implemented Factory Bad Block Scan and BBT |
| Application code should not directly control raw commands | Low-level command flow is complex | Separated Driver Layer and Service Layer |

---

## What I Learned / 學習重點

Through this project, I learned and practiced:

- SPI NAND Flash command protocol
- NAND Flash page / block architecture
- Difference between NAND Flash and NOR Flash behavior
- Erase-before-program restriction
- Status register polling mechanism
- ECC status handling
- Factory bad block management
- Firmware driver layering
- Embedded validation test design
- External memory bring-up and debugging process

---

## Project Purpose / 專案用途

This project is intended for firmware learning, driver development practice, and embedded system portfolio demonstration.

本專案主要作為 Firmware / Embedded System 轉職作品集，展示以下能力：

```text
Embedded C
MCU Peripheral Control
SPI Communication
External Memory Driver
NAND Flash Command Flow
Status Register Handling
ECC Error Handling
Bad Block Management
Validation Test Design
```

---

## Keywords

`STM32` `STM32H7` `Firmware` `Embedded C` `SPI` `SPI NAND` `NAND Flash` `W25N02KV` `Flash Driver` `ECC` `Bad Block Management` `Validation Test`
