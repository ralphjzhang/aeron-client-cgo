#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int aeron_initialize(char *aeron_dir);
void aeron_destroy();

int aeron_add_publication(char *channel, int stream_id);
void aeron_remove_publication(int publication_idx);
int aeron_get_streamId(int publication_idx);
int64_t aeron_publish(int publication_idx, char* msg, int msg_len);

int aeron_add_subscription(char *channel, int stream_id);
typedef int (*poll_handler_t)(char*, int);
int aeron_poll(int subscription_idx, poll_handler_t handler);

#ifdef __cplusplus
}
#endif
