#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void aeron_initialize(char *aeron_dir);

int aeron_add_publication(char *channel, int stream_id);

void aeron_publish(int publication_idx, char* msg, int msg_len);

#ifdef __cplusplus
}
#endif
