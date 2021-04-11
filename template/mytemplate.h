/**
  * @file       mytemplate.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @brief      This file is general header file of mytemplate.c.
  * @details
  */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __MYTEMPLATE_H__
#define __MYTEMPLATE_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "stdio.h"

/* Exported types -----------------------------------------------------------*/

/**
  * @brief    mystruct typedef
  * @details
  */
typedef struct mystruct
{
  int version;  /**< version member */
  int hello;    /**< hello member */
} mystruct_t;

/* Exported constants -------------------------------------------------------*/

#define MYCONSTANT  0x01 /**< MYCONSTANT value */

/* Exported macro -----------------------------------------------------------*/

/**
  * @brief  check whether you are cool.
  * @param  COOL the input value
  * @retval 0x01 you are coo
  * @retval 0x02 you are not cool
  */
#define CHECK_COOL(COOL)  (COOL ? 0x01 : 0x02)

/* Exported variables -------------------------------------------------------*/

/**
 * @defgroup HelloGroup hello group
 * @brief    This is hello group.
 * @{
 */

/** @brief a membef of hello group*/
extern int helloworld;

/** @} */ // end of hello group

/**
 * @defgroup coding Coding Group
 * @brief    coding group
*/

/**
 * @ingroup coding
 * @brief do you have bugs, can I help you?
 */
extern int bug_coding;

/** @addtogroup HelloGroup
 *
 *  More documentation for the hello group.
 *  @{
 */
/** @brief another function in coding group */
void func1() {}
/** @brief yet another function in coding group */
void func2() {}
/** @} */ // end of hello group


/* Exported functions -------------------------------------------------------*/
/**
  * @brief  check whether you are cool.
  * @param  [in]  ID      the input ID
  * @param  [out] result  the output result
  * @return None
  */
void check_cool(int ID, char *result);

/**
 * @brief retrun bool
 *
 * @return
 *          - true state true
 *          - false state false
 */
bool return_bool(void);

/* Private types ------------------------------------------------------------*/
/* Private constants --------------------------------------------------------*/
/* Private macros -----------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MYTEMPLATE_H__ */

/* ========================================================================= */
/* ================   Device Specific Peripheral Section    ================ */
/* ========================================================================= */


/**
  * @file       board_output.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.1
  * @brief      This file is general header file of board_output.c.
  * @details
  */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __BOARD_OUTPUT_H__
#define __BOARD_OUTPUT_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "stdio.h"

/* Exported types -----------------------------------------------------------*/
/* Exported constants -------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/
/* Exported variables -------------------------------------------------------*/
/* Exported functions -------------------------------------------------------*/
/* Private types ------------------------------------------------------------*/
/* Private constants --------------------------------------------------------*/
/* Private macros -----------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_OUTPUT_H__ */

/**********END OF FILE**********/

