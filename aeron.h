#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void aeron_initialize(char *aeron_dir);

int64_t aeron_add_publication(char *channel, int32_t stream_id);

void aeron_publish(int64_t publication_idx, char* msg, int msg_len);

#ifdef __cplusplus
}
#endif
