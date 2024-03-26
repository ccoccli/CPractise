#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <sys_type.h>
#include <sys_time.h>
#include <sys_log.h>
#include <sys_os.h>
#include <sys_string.h>

#include <ds_linked_list.h>


#define INIT_LINEAR_LIST_COUNT 10
sys_void unit_test_print_menu();
sys_void executeCommand(sys_char *command);
#endif //__UNIT_TEST_H__