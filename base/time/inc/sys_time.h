#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

#include <time.h>
#include <sys_type.h>

typedef unsigned short base_time_t;

typedef struct _sys_base_time_s
{
  base_time_t year;
  base_time_t month;
  base_time_t day;
  base_time_t hour;
  base_time_t minute;
  base_time_t second;
} baseTime;

/**
 * @brief 获取当前时间，并填充给定的 baseTime 结构体。
 *
 * @param pTime 用于存储当前时间的 baseTime 结构体指针。
 * @return 如果成功获取当前时间则返回 true，否则返回 false。
 */
bool getCurrentTime(baseTime *pTime);

/**
 * @brief 获取当前的UTC时间戳。
 *
 * @return 返回当前的UTC时间戳，即自1970年1月1日以来经过的秒数。
 */
time_t getCurrentUTCTimestamp(void);

/**
 * @brief 获取当前年份。
 *
 * @param pYear 用于存储当前年份的 base_time_t 类型指针。
 * @return 如果成功获取当前年份则返回 true，否则返回 false。
 */
bool getCurrentYear(base_time_t *pYear);

/**
 * @brief 获取当前月份。
 *
 * @param pMonth 用于存储当前月份的 base_time_t 类型指针。
 * @return 如果成功获取当前月份则返回 true，否则返回 false。
 */
bool getCurrentMonth(base_time_t *pMonth);

/**
 * @brief 获取当前日期。
 *
 * @param pDay 用于存储当前日期的 base_time_t 类型指针。
 * @return 如果成功获取当前日期则返回 true，否则返回 false。
 */
bool getCurrentDay(base_time_t *pDay);

/**
 * @brief 获取当前小时。
 *
 * @param pHour 用于存储当前小时的 base_time_t 类型指针。
 * @return 如果成功获取当前小时则返回 true，否则返回 false。
 */
bool getCurrentHour(base_time_t *pHour);

/**
 * @brief 获取当前分钟。
 *
 * @param pMinute 用于存储当前分钟的 base_time_t 类型指针。
 * @return 如果成功获取当前分钟则返回 true，否则返回 false。
 */
bool getCurrentMinute(base_time_t *pMinute);

/**
 * @brief 获取当前秒数。
 *
 * @param pSecond 用于存储当前秒数的 base_time_t 类型指针。
 * @return 如果成功获取当前秒数则返回 true，否则返回 false。
 */
bool getCurrentSecond(base_time_t *pSecond);

/**
 * @brief 比较两个 baseTime 类型的时间。
 *
 * @param t1 第一个要比较的时间。
 * @param t2 第二个要比较的时间。
 * @return 返回值为 '>', '=', 或 '<'，表示 t1 大于、等于或小于 t2。
 */
char compareBaseTime(const baseTime *t1, const baseTime *t2);

/**
 * @brief 获取两个 baseTime 类型的时间中的较大时间。
 *
 * @param t1 第一个要比较的时间。
 * @param t2 第二个要比较的时间。
 * @param result 用于存储结果的 baseTime 结构体指针。
 */
void getMaxTime(const baseTime *t1, const baseTime *t2, baseTime *result);

/**
 * @brief 获取两个 baseTime 类型的时间中的较小时间。
 *
 * @param t1 第一个要比较的时间。
 * @param t2 第二个要比较的时间。
 * @param result 用于存储结果的 baseTime 结构体指针。
 */
void getMinTime(const baseTime *t1, const baseTime *t2, baseTime *result);

/**
 * @brief 将UTC时间戳转换为本地时间。
 *
 * @param utcTimestamp UTC时间戳，即自1970年1月1日以来的秒数。
 * @param baseTime 返回的本地时间
 * @return 返回包含本地时间信息的tm结构体指针。
 */
bool convertUTCToLocalTime(const time_t utcTimestamp, baseTime *pTime);

/**
 * @brief 将本地时间结构体转换为UTC时间戳。
 *
 * @param pTime 包含本地时间信息的baseTime结构体指针。
 * @return 如果转换成功，返回自1970年1月1日以来的秒数（UTC时间戳）；
 *         如果输入的本地时间信息无效，返回特殊值 0xffffff 表示错误。
 */
unsigned long long convertLocalTimeToUTC(const baseTime *pTime);

#endif //__SYS_TIME_H__