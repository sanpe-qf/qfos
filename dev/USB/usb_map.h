#ifndef _USB_MAP_H_
#define _USB_MAP_H_
typedef struct
{
  __IO uint16_t EP0R;                 /*!< USB Endpoint 0 register,                   Address offset: 0x00 */ 
  __IO uint16_t RESERVED0;            /*!< Reserved */     
  __IO uint16_t EP1R;                 /*!< USB Endpoint 1 register,                   Address offset: 0x04 */
  __IO uint16_t RESERVED1;            /*!< Reserved */       
  __IO uint16_t EP2R;                 /*!< USB Endpoint 2 register,                   Address offset: 0x08 */
  __IO uint16_t RESERVED2;            /*!< Reserved */       
  __IO uint16_t EP3R;                 /*!< USB Endpoint 3 register,                   Address offset: 0x0C */ 
  __IO uint16_t RESERVED3;            /*!< Reserved */       
  __IO uint16_t EP4R;                 /*!< USB Endpoint 4 register,                   Address offset: 0x10 */
  __IO uint16_t RESERVED4;            /*!< Reserved */       
  __IO uint16_t EP5R;                 /*!< USB Endpoint 5 register,                   Address offset: 0x14 */
  __IO uint16_t RESERVED5;            /*!< Reserved */       
  __IO uint16_t EP6R;                 /*!< USB Endpoint 6 register,                   Address offset: 0x18 */
  __IO uint16_t RESERVED6;            /*!< Reserved */       
  __IO uint16_t EP7R;                 /*!< USB Endpoint 7 register,                   Address offset: 0x1C */
  __IO uint16_t RESERVED7[17];        /*!< Reserved */     
  __IO uint16_t CNTR;                 /*!< Control register,                          Address offset: 0x40 */
  __IO uint16_t RESERVED8;            /*!< Reserved */       
  __IO uint16_t ISTR;                 /*!< Interrupt status register,                 Address offset: 0x44 */
  __IO uint16_t RESERVED9;            /*!< Reserved */       
  __IO uint16_t FNR;                  /*!< Frame number register,                     Address offset: 0x48 */
  __IO uint16_t RESERVEDA;            /*!< Reserved */       
  __IO uint16_t DADDR;                /*!< Device address register,                   Address offset: 0x4C */
  __IO uint16_t RESERVEDB;            /*!< Reserved */       
  __IO uint16_t BTABLE;               /*!< Buffer Table address register,             Address offset: 0x50 */
  __IO uint16_t RESERVEDC;            /*!< Reserved */       
} USB_TypeDef;

/* USB device FS */
#define USB_BASE              (APB1PERIPH_BASE + 0x00005C00U) /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR           (APB1PERIPH_BASE + 0x00006000U) /*!< USB_IP Packet Memory Area base address */
#define USB                 ((USB_TypeDef *)USB_BASE)

// 对于单向双缓冲型的发送端点, 寄存器名称后缀都是TX; 单向双缓冲接收端点则都是RX
typedef struct
{
  __IO uint16_t ADDR_TX;
  __IO uint16_t RESERVED0;
  __IO uint16_t COUNT_TX;
  __IO uint16_t RESERVED1;
  __IO uint16_t ADDR_RX;
  __IO uint16_t RESERVED2;
  __IO uint16_t COUNT_RX;
  __IO uint16_t RESERVED3;
} USB_BufferDescriptor;
#define USB_BufDesc ((USB_BufferDescriptor *)(USB_PMAADDR + USB->BTABLE))
#define USB_ISTR_MASK 0x7f00
#define USB_EPnR_MASK_T 0x8f8f // 防止翻转位发生翻转用的掩码
#define USB_EPnR_MASK_CW0 0x8080 // 防止rc_w0型的位被清零
#define USB_EPnR(reg) ((reg & USB_EPnR_MASK_T) | USB_EPnR_MASK_CW0)
#endif
