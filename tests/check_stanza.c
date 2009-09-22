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

#include <stdlib.h>
#include <string.h>

#include <check.h>

#include <strophe.h>

#include "test.h"

static xmpp_ctx_t    *ctx;
static xmpp_stanza_t *stanza;

/* Test support */
/* ************************************************************ */

static void handle_setup(void) {
    xmpp_initialize();
    ctx = xmpp_ctx_new(NULL, NULL);
    fail_if(ctx == NULL, "Failed to set up ctx");
    stanza = xmpp_stanza_new(ctx);
    fail_if(stanza == NULL, "Failed to create a stanza.");
}

static void handle_teardown(void) {
    xmpp_stanza_release(stanza);
    xmpp_ctx_free(ctx);
    ctx = NULL;
    stanza = NULL;
    xmpp_shutdown();
}

/* The actual tests */
/* ************************************************************ */

START_TEST(test_simple_stanza_to_text)
{
    char *buf;
    size_t len;

    xmpp_stanza_set_name(stanza, "something");
    fail_unless(xmpp_stanza_to_text(stanza, &buf, &len) == 0,
                "Failed to serialize stanza.");

    fail_unless(strcmp("<something/>", buf) == 0,
                "Stanza strcmp failure.");

    xmpp_free(ctx, buf);
}
END_TEST

START_TEST(test_stanza_to_text_with_attrs)
{
    char *buf;
    size_t len;

    xmpp_stanza_set_name(stanza, "something");
    xmpp_stanza_set_attribute(stanza, "attr1", "Some value & something.");

    fail_unless(xmpp_stanza_to_text(stanza, &buf, &len) == 0,
                "Failed to serialize stanza.");

    fail_unless(strcmp("<something attr1=\"Some value & something.\"/>",
                       buf)
                == 0,
                "Stanza strcmp failure.");

    xmpp_free(ctx, buf);
}
END_TEST

START_TEST(test_nested_stanza_to_text)
{
    char *buf;
    size_t len;

    xmpp_stanza_set_name(stanza, "something");

    xmpp_stanza_t *child = xmpp_stanza_new(ctx);
    fail_if(child == NULL, "Failed to create child stanza.");

    xmpp_stanza_set_name(child, "child");
    xmpp_stanza_add_child(stanza, child);
    xmpp_stanza_release(child);

    fail_unless(xmpp_stanza_to_text(stanza, &buf, &len) == 0,
                "Failed to serialize stanza.");

    fail_unless(strcmp("<something><child/></something>", buf) == 0,
                "Stanza strcmp failure.");

    xmpp_free(ctx, buf);
}
END_TEST

START_TEST(test_large_stanza_to_text)
{
    char *buf = NULL, *string;
    size_t len = 0;
    int rounds = 1024, i = 0;

    xmpp_stanza_set_name(stanza, "something");

    for (i=0; i<rounds; i++) {
        xmpp_stanza_t *child = xmpp_stanza_new(ctx);
        fail_if(child == NULL, "Failed to create child stanza.");

        xmpp_stanza_set_name(child, "child");
        xmpp_stanza_add_child(stanza, child);
        xmpp_stanza_release(child);
    }

    fail_unless(xmpp_stanza_to_text(stanza, &buf, &len) == 0,
                "Failed to serialize stanza.");

    fail_unless(strlen(buf) == len,
                "Counted length doesn't equal reported length.");

    string = calloc(len+1, sizeof(char));
    fail_if(string == NULL, "Failed to allocate string.");
    strcat(string, "<something>");

    for (i=0; i<rounds; i++) {
        strcat(string, "<child/>");
    }

    strcat(string, "</something>");

    fail_unless(strcmp(string, buf) == 0, "Stanza strcmp failure.");

    xmpp_free(ctx, buf);
}
END_TEST


Suite *parser_suite(void)
{
    Suite *s = suite_create("Stanza");
    TCase *tc = tcase_create("Core");

    tcase_add_checked_fixture(tc, handle_setup, handle_teardown);

    tcase_add_test(tc, test_simple_stanza_to_text);
    tcase_add_test(tc, test_stanza_to_text_with_attrs);
    tcase_add_test(tc, test_nested_stanza_to_text);
    tcase_add_test(tc, test_large_stanza_to_text);

    suite_add_tcase(s, tc);
    return s;
}

TEST_MAIN
