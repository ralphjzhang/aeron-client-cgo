#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int aeron_initialize(char *aeron_dir);
void aeron_destroy();

int aeron_add_publication(char *channel, int stream_id);
void aeron_remove_publication(int publication_idx);

int aeron_add_subscription(char *channel, int stream_id);

void aeron_publish(int publication_idx, char* msg, int msg_len);
void aeron_poll(int subscription_idx);

#ifdef __cplusplus
}
#endif
