/******************************************************************************************************//**
 * @file    typedefs.h
 * @brief   类型定义, 机器无关变量大小
 * @author  coolweedman
 * @date    2015-10-10 22:00:46
 * @version V1.00
 *********************************************************************************************************/

#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H



/**********************************************************************************************************
  宏定义
**********************************************************************************************************/

#define UINT8_MAX	0xFF                                                /**< 无符号8位最大               */
#define	UINT16_MAX	0xFFFF                                              /**< 无符号16位最大              */
#define	UINT32_MAX	0xFFFFFFFF                                          /**< 无符号32位最大              */

#define	INT8_MAX	0x7F                                                /**< 有符号8位最大               */
#define	INT16_MAX	0x7FFF                                              /**< 有符号16位最大              */
#define INT32_MAX	0x7FFFFFFF                                          /**< 有符号32位最大              */



/**********************************************************************************************************
  类型定义
**********************************************************************************************************/

typedef	unsigned	char	uint8_t;                                    /**< 无符号8位                   */
typedef	unsigned	short	uint16_t;                                   /**< 无符号16位                  */
typedef	unsigned	int 	uint32_t;                                   /**< 无符号32位                  */

typedef	signed		char	int8_t;	                                    /**< 符号8位                     */
typedef	signed		short	int16_t;                                    /**< 符号16位                    */
typedef	signed		int 	int32_t;                                    /**< 符号32位                    */
typedef signed long int     int64_t;                                    /**< 符号64位                    */

typedef unsigned    char    INT8U;                                      /**< 无符号8位                   */
typedef unsigned    short   INT16U;                                     /**< 无符号16位                  */
typedef unsigned    int     INT32U;                                     /**< 无符号32位                  */

typedef signed      char    INT8S;	                                    /**< 符号8位                     */
typedef signed      short   INT16S;	                                    /**< 符号16位                    */
typedef signed      int     INT32S;	                                    /**< 符号32位                    */


#endif                                                                  /* __TYPEDEFS_H                  */

/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
