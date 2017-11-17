#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int aeron_initialize(char *aeron_dir);
void aeron_destroy();

int aeron_add_publication(char *channel, int stream_id);
void aeron_remove_publication(int publication_idx);
int aeron_get_streamId(int publication_idx);

void aeron_publish(int publication_idx, char* msg, int msg_len);
void aeron_poll(char *channel, int stream_id);

#ifdef __cplusplus
}
#endif
