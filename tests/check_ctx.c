/* check_stanza.h
** strophe XMPP client library -- stanza tests
**
** Copyright (C) 2005-2009 Collecta, Inc. 
**
**  This software is provided AS-IS with no warranty, either express or
**  implied.
**
**  This software is distributed under license and may not be copied,
**  modified or distributed except as expressly authorized under the
**  terms of the license contained in the file LICENSE.txt in this
**  distribution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <check.h>

#include <strophe.h>

#include "test.h"

static xmpp_ctx_t *ctx          = NULL;
static char       *last_message = NULL;

void xmpp_warn(const xmpp_ctx_t * const ctx,
               const char * const area,
               const char * const fmt,
               ...);

/* Test support */
/* ************************************************************ */

static void capturing_logger(void *const userdata,
                             const xmpp_log_level_t level,
                             const char *const area,
                             const char *const msg) {
    if (last_message) {
        free(last_message);
        last_message = NULL;
    }
    last_message = strdup(msg);
}

static xmpp_log_t xmpp_logger_thing = { &capturing_logger, NULL };

static void handle_setup(void) {
    xmpp_initialize();

    ctx = xmpp_ctx_new(NULL, &xmpp_logger_thing);
    fail_if(ctx == NULL, "Failed to set up ctx");
}

static void handle_teardown(void) {
    free(last_message);
    xmpp_ctx_free(ctx);
    ctx = NULL;
    xmpp_shutdown();
}

/* The actual tests */
/* ************************************************************ */

START_TEST(test_large_logger)
{
    int num_bytes = 16 * 1024;
    char *big_ass_string = calloc(num_bytes + 1, sizeof(char));

    memset((void*)big_ass_string, 'a', num_bytes);
    fail_unless(strlen(big_ass_string) == num_bytes,
                "The string isn't long enough.");

    xmpp_warn(ctx, "conn", "Big ass string:  %s", big_ass_string);

    char *output = calloc(num_bytes + 32, sizeof(char));
    snprintf(output, num_bytes + 32, "Big ass string:  %s", big_ass_string);
    fail_unless(strcmp(output, last_message) == 0,
                "Logged message was different.");
    free(output);
}
END_TEST

Suite *parser_suite(void)
{
    Suite *s = suite_create("Stanza");
    TCase *tc = tcase_create("Core");

    tcase_add_checked_fixture(tc, handle_setup, handle_teardown);

    tcase_add_test(tc, test_large_logger);

    suite_add_tcase(s, tc);
    return s;
}

TEST_MAIN
